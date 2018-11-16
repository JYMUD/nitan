// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// battlefieldd.c

#include <ansi.h>

#define LEAVE_ROOM              "/d/city/guangchang"
#define BATTLE_FIELD_DIR        "/adm/daemons/battle/"
#define BATTLE_TIME             1800
#define BATTLE_JOIN_TIME        180

nosave mapping battle_player = allocate_mapping(0);
nosave object *total = allocate(0);
nosave string *ip_number = allocate(0);

nosave int bunch_flag = 0;
nosave int battle_open_flag = 0;
nosave int battle_start_flag = 0;
nosave int battle_time_countdown = 0;
nosave int battle_start_time = 0;
nosave int percent = 100;
nosave int max_level = 200;
nosave string battle_name;
nosave string entry1;
nosave string entry2;

int check_out(object me);
private void restore_status(object me);
void add_damage_score(object me, int score);
void add_killplayer_score(object me, int score);
void add_killnpc_score(object me, int score);
void add_bouns_score(object me, int score);
void stop_battle();
void calculate_score();

int sort_user(object ob1, object ob2)
{
        return (query("level", ob2) - query("level", ob1));
}

class team
{
        int score;      // ����
        int win;        // ��ʤ
        int lose;       // ʧ��
        string name;    // ��������
        string *member; // �����Ա
        string leader;  // �ӳ�
}
nosave class team *all = ({});
nosave class team team1, team2;

int clean_up()
{
        return 1;
}

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

int in_battle(object me)
{
        return battle_start_flag && !undefinedp(battle_player[me->query_id(1)]);
}

int inside_battlefield(object me)
{
        object env = environment(me);

        if( !objectp(env) )
                return 0;

        if( !sscanf(base_name(env), "/maze/battle%*s") )
                return 0;

        return 1;
}

int query_battle_time()
{
        return battle_time_countdown;

}

mapping query_battle_player()
{
        return battle_player;
}

int query_player_number(object player)
{
        return member_array(player->query_id(1), keys(battle_player)) + 1;
}

// ����ս������
void set_battle_name(string name)
{
        battle_name = name;
}

// ���ö�������
void set_team_name(string name1, string name2)
{
        team1->name = name1;
        team2->name = name2;
}

// ���ö������
void set_entry_room(string where1, string where2)
{
        entry1 = where1;
        entry2 = where2;
}

// ���ñ�������
void set_max_level(int level)
{
        max_level = level;
}

// ���ý�������%
void set_bonus_percent(int per)
{
        percent = per;
}

// ������֧����
void set_bunch_team(string name1, string name2)
{
        bunch_flag = 1;
        team1->name = name1;
        team2->name = name2;
}

void move_to_battle(object me)
{
        string where;
        object entry;

        where = query_temp("battle/entrance", me);
        entry = get_object(where);
        me->move(entry);
}

void init_player(object me)
{
        int i;
        object *obs;
        
        tell_object(me, HIY "����ǰ��Ȼһ��...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        //set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        set("backup/condition", me->query_condition(), me);
        me->clear_condition();
        
        obs = all_inventory(me);
        for( i=0; i<sizeof(obs); i++ )
        {
                if( query("id", obs[i]) == "mian ju" )
                        obs[i]->move();
        }
                
        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });
       
        move_to_battle(me);
        tell_object(me, HIY "�㱻���͵�ս����...��\n");
}

// ����ս��
void join_battle(object me)
{
        string where;
        mapping cnd;
        string id = me->query_id(1);

        if( battle_start_flag )
                return tell_object(me, "ս���Ѿ�������������ֹ��\n");

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "��Ŀǰ����ս���У������ȴ���Ŀǰ�Ķ�����˵�ɡ�\n");

        if( me->query_condition("killer") )
                return tell_object(me, "�ٸ�����ͨ���㣬�㻹���������ͷ¶�棿\n");

        if( !battle_open_flag )
                return tell_object(me, "ս��û�з������ᣬĿǰ�޷�������\n");

        if( me->is_ghost() )
                return tell_object(me, "���㻹�����ٱ����ɡ�\n");

        if (me->is_in_prison()) 
                return tell_object(me, "�����������أ������ʲô����\n"); 

        if( query("level", me) < 5 )
                return tell_object(me, "���������Ͳ�Ҫ�μӸ��Ѷȵ�ս���ɡ�\n");

        if( query("level", me) > max_level )
                return tell_object(me, "��ͱ��ȥ�۸���Щ����ɡ�\n");
        
        if( bunch_flag )
        {
                if( !bunchp(me) )
                        return tell_object(me, "����ս��ֻ���ǰ�����ұ����μӡ�\n");
                
                if( me->query_bunch() != team1->name && 
                    me->query_bunch() != team2->name )
                        return tell_object(me, "����ս�������ڵİ��ɲ��ܱ����μӡ�\n");
        }
        
        where = base_name(environment(me));
        if( sscanf(where, "/d/newbie/%s") )
                return tell_object(me, "�㻹û����ʽ���������أ����ܲμӱ�����\n");

        if( !undefinedp(battle_player[id]) )
        {
                if( !battle_start_flag )
                        return tell_object(me, "���Ѿ�����������ε�ս���������ĵȺ��ټ���\n");

                if( inside_battlefield(me) )
                        return tell_object(me, "���Ѿ���ս���У����ɱ�аɡ�\n");

                if( !query_temp("battle_rejoin", me) )
                        return tell_object(me, "�����ʹ��ս��ѫ�·������½���ս����\n");

                delete_temp("battle_rejoin", me);
                set_temp("battle/leave_room", where, me);
                init_player(me);
                return;
        }

        if( member_array(query_ip_number(me), ip_number) != -1 )
                return tell_object(me, "�����ڵ�IP�Ѿ���������!\n");

        ip_number += ({ query_ip_number(me) });
        battle_player[id] = allocate_mapping(0);

        CHANNEL_D->channel_broadcast("war", "Ŀǰ���� "+sizeof(battle_player)+
                                            " λ��ұ������롸"+battle_name+HIR"��");
}

// ȡ������ս��
void cancel_battle(object me)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
                return tell_object(me, "��ԭ����û�б���������ε�ս����\n");

        if( battle_start_flag )
                return tell_object(me, "��ε�ս���Ѿ���ʼ�����޷�ȡ��������quitָ������ս����\n");

        map_delete(battle_player, id);
        ip_number -= ({ query_ip_number(me) });

        addn("honors", -100, me); // �ۼ�����
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        CHANNEL_D->channel_broadcast("war", "Ŀǰ���� "+sizeof(battle_player)+
                                            " λ��ұ������롸"+battle_name+HIR"��");
}

int check_quit(object me)
{
        CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"�����" + me->name(1) +"�ڡ�"+battle_name+HIR"�����������ӣ������ˡ�"NOR);

        addn("honors", -500, me); // �ۼ�����
        if( query("honors", me)<0);
                set("honors", 0, me);

        if( arrayp(total) )
                total -= ({ me });
        if( arrayp(ip_number) )
                ip_number -= ({ query_ip_number(me) });

        tell_object(me, "��һ�����ӳ���ս����\n");
        restore_status(me);
        message("vision", "ֻ��" + me->name() + "������ŵ����˹�����\n",
                environment(me), ({ me }));

        return 1;
}

varargs int receive_damage(object me, string type, int damage, object who)
{
        if( !who ) who = me->query_last_damage_from();
        if( !who ) return 0;

        if( type != "qi" || damage < 1 ) return 0;

        if( userp(me) )
                add_damage_score(who, damage);
        else
                add_damage_score(who, damage/2);

        return 0;
}

void auto_check()
{
        object ob;
        string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, "/maze/battle%*s") )
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        room = base_name(environment(me));
        if( !sscanf(room, "/maze/battle%*s") )
        {
                // not in battle room
                total -= ({ me });
                return 0;
        }

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = 1;
        my["jing"] = 1;

        tell_object(me, HIR "\n�������ǰһ��ģ��...�������ˣ�\n" NOR);
        if( ob = me->query_last_damage_from() )
        {
                msg = me->name(1) + "����" + ob->name(1) + "�Ķ��֣�������Уˡ�";
                if( userp(ob) )
                {
                        if( userp(me) )
                        {
                                if( query_temp("battle/team_name", ob) == query_temp("battle/team_name", me) )
                                        add_killplayer_score(ob, -5);
                                else {
                                        if( query_temp("battle/leader", me) )
                                                add_killplayer_score(ob, 5);
                                        else
                                                add_killplayer_score(ob, 1);
                                }
                        }
                        else
                        {
                                if( query_temp("battle/team_name", ob) == query_temp("battle/team_name", me) )
                                        add_killnpc_score(ob, -5);
                                else
                                        add_killnpc_score(ob, 1);
                                return 0;
                        }
                }
        } else
                 msg = me->name(1) + "�������ѣ��������ޡ��Ѿ�����Уˡ�";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });

        message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����"
                "һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������"
                "������ӡ�\n", environment(me), ({ me }));
        tell_object(me, "�������У�����ñ���������������"
                "���ص�ˤ���˵��ϡ�\n");

        if( !living(me) )
                me->revive();

        return 1;
}

void start_battle()
{
        object *all_player = ({});
        object *obs, *obn, ob;
        object *unavailable_players = allocate(0);
        object player;
        string where;
        int i;

        if( sizeof(battle_player) < 5 )
        {
                set_heart_beat(0);
                ip_number = allocate(0);
                total = allocate(0);
                all = allocate(0);
                battle_player = allocate_mapping(0);
                max_level = 200;
                bunch_flag = 0;
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "�������롸"+battle_name+HIR"��ս�۵���Ҳ��� 5 �ˣ�ȡ������ս�ۡ�");
                return;
        }

        CHANNEL_D->channel_broadcast("war", "��"+battle_name+HIR"����ʼ���������� "+sizeof(battle_player)+
                                            " λ��Ҳ��롸"+battle_name+HIR"������ʱ "+(BATTLE_TIME/60)+" ���ӽ���");

        foreach(string id, mapping data in battle_player)
        {
                reset_eval_cost();

                if( !objectp(player = find_player(id)) )
                        continue;

                if( query_temp("running", player)  )
                {
                        tell(player, pnoun(2, player)+"���ڷ����У��޷�����ս����\n");
                        unavailable_players |= ({ player });
                        continue;
                }
                all_player += ({ player });
        }

        foreach(player in unavailable_players)
                cancel_battle(player);
        
        team1->member = ({});
        team2->member = ({});
        
        // �������֧������ս���򰴰��ɷ�����Ӫ
        if( bunch_flag )
        {
                obs = filter_array(all_player, (: query("bunch/bunch_name", $1) == team1->name :));
                foreach( ob in obs )
                {
                        team1->member += ({ ob->query_id(1) });
                        set_temp("battle/team_name", team1->name, ob);
                        set_temp("battle/entrance", entry1, ob);
                        where = base_name(environment(ob)); // ��¼�������λ��
                        set_temp("battle/leave_room", where, ob);
                        init_player(ob);
                }
                obn = all_player - obs;
                foreach( ob in obs )
                {
                        team2->member += ({ ob->query_id(1) });
                        set_temp("battle/team_name", team2->name, ob);
                        set_temp("battle/entrance", entry2, ob);
                        where = base_name(environment(ob)); // ��¼�������λ��
                        set_temp("battle/leave_room", where, ob);
                        init_player(ob);
                }
        }
        else
        {
                // ��ʼ���������Ӫ        
                all_player = sort_array(all_player, (: sort_user :));

                for( i=0; i<sizeof(all_player); i++ )
                {
                        if( i % 2 == 0 ) {
                                if( i == 0 )
                                {
                                        team1->leader = all_player[i]->query_id(1);
                                        set_temp("battle/leader", 1, all_player[i]);
                                }
                                team1->member += ({ all_player[i]->query_id(1) });
                                set_temp("title", team1->name, all_player[i]);
                                set_temp("battle/team_name", team1->name, all_player[i]);
                                set_temp("battle/entrance", entry1, all_player[i]);
                        } else {
                                if( i == 1 )
                                {
                                        team2->leader = all_player[i]->query_id(1);
                                        set_temp("battle/leader", 1, all_player[i]);
                                }
                                team2->member += ({ all_player[i]->query_id(1) });
                                set_temp("title", team2->name, all_player[i]);
                                set_temp("battle/team_name", team2->name, all_player[i]);
                                set_temp("battle/entrance", entry2, all_player[i]);
                        }

                        where = base_name(environment(all_player[i])); // ��¼�������λ��
                        set_temp("battle/leave_room", where, all_player[i]);

                        init_player(all_player[i]);
                }
        }
        all += ({ team1, team2 });
        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

// ĳս����ʼ���ܱ��� TIME_D ����
void start_join(string name)
{
        object ob;

        name = BATTLE_FIELD_DIR + name;
        if( ob = find_object(name) )
                destruct(ob);

        catch(ob = load_object(name));

        if( !objectp(ob) ) return;

        team1 = new(class team);
        team2 = new(class team);
        ob->init_battle(); // ���ö�������ƣ��������ڣ�ս���������Լ���ʼ��ս���������õ�
        CHANNEL_D->channel_broadcast("war", HIY"��ҫ"NOR YEL"֮ս"HIR"����ս�����ᣬ������ "+(BATTLE_JOIN_TIME/60)+
                                            " ���Ӻ󷢶���"+battle_name+HIR"������ʹ�� battle ָ�����ս�ۡ�");

        ip_number = allocate(0);
        total = allocate(0);
        all = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

int get_player_score(string id)
{
        if( undefinedp(battle_player[id]) ) return 0;

        return battle_player[id]["killplayer"]*10 + /*battle_player[id]["killnpc"] + battle_player[id]["damage"]/50000 +*/ battle_player[id]["bonus"];
}

string *get_sorted_players()
{
        return sort_array(keys(battle_player), (: get_player_score($2) - get_player_score($1) :));
}

void add_damage_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["damage"] += score;
}

void add_killnpc_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killnpc"] += score;
}

void add_killplayer_score(object me, int score)
{
        string id = me->query_id(1);
        string name;

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killplayer"] += score;

        name = query_temp("battle/team_name", me);
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
                team1->score += score;
        else
                team2->score += score;

        return;
}

void add_bonus_score(object me, int score)
{
        string id = me->query_id(1);
        string name;

        if( undefinedp(battle_player[id]) )

            return;

        battle_player[id]["bonus"] += score;
        //addn("honors", score, me);

        name = query_temp("battle/team_name", me);
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
                team1->score += score;
        else
                team2->score += score;

        return;
}

void win_battle(string name)
{
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
        {
                team1->win = 1;
                team1->lose = 0;
                team2->win = 0;
                team2->lose = 1;
        } else
        {
                team2->win = 1;
                team2->lose = 0;
                team1->win = 0;
                team1->lose = 1;
        }

        stop_battle();
}

void stop_battle()
{
        object ob;
        object player;

        set_heart_beat(0);

        foreach( ob in total )
        {
                if( !objectp(ob) )
                        continue;

                //ob->remove_all_killer();
                ob->remove_all_enemy(1);
                restore_status(ob);
                tell_object(ob, "��"+battle_name+"���������㱻����ս��...\n");
        }

        ip_number = allocate(0);
        total = allocate(0);
        max_level = 200;
        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;        

        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);
        CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"����"+battle_name+HIR"�����ڽ���ƽϢ..."NOR);
        CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"������ͳ��ս��..."NOR);
        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);


        if( ob = find_object(BATTLE_FIELD_DIR + battle_name) )
        {
                ob->refresh_map();
        }

        if( objectp(ob) && function_exists("calculate_score", ob) )
        {
                ob->calculate_score();
                
                bunch_flag = 0;
                all = allocate(0);
                battle_player = allocate_mapping(0);
                destruct(ob);
        }
        else
                call_out((: calculate_score :), 3);
}

void calculate_score()
{
        int score;
        string name;
        string msg;
        int rank;
        object home, player;
        string file;
        object insigne;
        int insigne_count;
        string *member;
        object ob;
        int i;

        map_delete(battle_player, 0);

        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);

        rank = 0;
        foreach(string id in get_sorted_players())
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                name=query_temp("battle/team_name", player);

                score = get_player_score(id);

                CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"��"+(++rank)+"."+name+HIR"��"+player->query_idname()+HIR"����ɱ "+battle_player[id]["killplayer"]+" λ��ң�ս������Ϊ "+NUMBER_D->number_symbol(score)+(battle_player[id]["bonus"]>0 ? "("NOR CYN"+"HIC+battle_player[id]["bonus"]+HIR")":"")+" ��"NOR);

                //addn("battle/score", score, player);
                addn("honors", score, player);

                if( score > 1000 ) score = 1000;
                if( score < 10 ) score = 10;
                GIFT_D->battle_bonus(player, ([ "exp" : score*500, "pot" : score*60, "mar" : score*2, "score" : score, "percent" : percent ]));

                insigne_count = 0;

                if( score >= 25 )
                switch(rank)
                {
                        case 1:
                                insigne_count = 4;
                                break;
                        //case 2..3:
                        case 2:
                                insigne_count = 3;
                                break;
                        //case 4..6:
                        case 3:
                                insigne_count = 2;
                                break;
                        //case 7..9:
                        case 4:
                                insigne_count = 1;
                                break;
                }

                if( insigne_count > 0 )
                {
                        if( random(2) )
                                insigne = new("/clone/tongren/tongren1");
                        else
                                insigne = new("/clone/tongren/tongren2");
                        tell_object(player, "���� "+insigne_count+" ��"+insigne->name()+"��\n");
                        insigne->set_amount(insigne_count);
                        insigne->move(player);
                }

                player->save();
        }

        if( team1->win )
        {
                msg = team1->name + "ʤ" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 300000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team1->name, 1000);
        }
        else if( team2->win )
        {
                msg = team1->name + "��" + team2->name;
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 300000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team2->name, 1000);
        }
        else if( team1->score > team2->score )
        {
                msg = team1->name + "ʤ" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 300000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team1->name, 800);
        }
        else if( team1->score < team2->score )
        {
                msg = team1->name + "��" + team2->name;
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 300000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team2->name, 800);
        }
        else
        {
                msg = team1->name + "ƽ" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 500, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 150000, "pot" : 15000, "mar" : 1500, "score" : 15, "percent" : percent ]));
                }
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 500, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 150000, "pot" : 15000, "mar" : 1500, "score" : 15, "percent" : percent ]));
                }
                if( bunch_flag )
                {
                        BUNCH_D->add_bunch_honors(team1->name, 200);
                        BUNCH_D->add_bunch_honors(team2->name, 200);
                }
        }

        msg += "\n";

        CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"��"+msg+NOR);

        bunch_flag = 0;
        all = allocate(0);
        battle_player = allocate_mapping(0);
}

string do_score()
{
        string desc, desc_temp;
        object player;
        int i, j, n;
        string *member;
        object ob;

        desc = HIY"
������������������������������������ǰս���ɼ�����������������������������������
________________________________________________________________________________
�ӱ�  ����     ����  ��Ա                                \n" NOR;

        n = sizeof(all);
        if( n > 1 )
        {
                for( i=0; i<n; i++ )
                {
                        desc_temp = "";
                        desc_temp += sprintf("%-6d%-9s%-6d ",
                                             i+1,
                                             (string)all[i]->name,
                                             (int)all[i]->score);

                        member = all[i]->member;
                        for( j=0; j<sizeof(member); j++ ) {
                                if( (j-1)%4==3 )
                                        desc_temp += "\n              ";

                                ob = find_player(member[j]);
                                if( objectp(ob) )
                                        desc_temp += sprintf("%-8s(%5d)",
                                                     ob->name(),
                                                     get_player_score(query("id", ob)));
                                else
                                {
                                        ob = UPDATE_D->global_find_player(member[j]);
                                        desc_temp += sprintf("%-8s(�� ��)",
                                                     ob->name());
                                        UPDATE_D->global_destruct_player(ob, 1);
                                }
                        }
                        desc_temp += "\n";
                        desc += desc_temp;
                }
        }

        desc += "
________________________________________________________________________________\n"NOR;

        return desc;
}

void heart_beat()
{
        if( battle_start_time > 0 )
        {
                switch(--battle_start_time)
                {
                        case 0:
                                start_battle();
                                break;
                        case 60:
                        case 120:
                        case 180:
                        case 300:
                        case 600:
                        case 900:
                        case 1200:
                                CHANNEL_D->channel_broadcast("war", HIY"��ҫ"NOR YEL"֮ս"HIR"����ս�����ᣬ������ "+(battle_start_time/60)+
                                                                    " ���Ӻ󷢶���"+battle_name+HIR"������ʹ�� battle ָ�����ս�ۡ�");
                                break;
                }

                return;
        }

        if( !battle_start_flag )
                return;

        if( --battle_time_countdown <= 0 )
        {
                stop_battle();
                return;
        }

        if( sizeof(total) )
                auto_check();

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"����"+battle_name+HIR"�������� "+(battle_time_countdown/60)+" ���Ӻ����..."NOR);
}

void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
        string where;
        int i;

        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        delete_temp("override/receive_damage", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_condition();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        delete_temp("in_pkd", me);
        delete_temp("title", me);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;

        if( stringp(where = query_temp("battle/leave_room", me)) )
        {
                if( where == "/inherit/room/chatroom" )
                        where = LEAVE_ROOM;
                me->move(where);
        }
        else
                me->move(LEAVE_ROOM);

        //delete_temp("battle", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);
}

int remove()
{
        if( sizeof(battle_player) )
        {
                object player;

                CHANNEL_D->channel_broadcast("war", HIR"ս"NOR RED"��"HIR"��ϵͳ���£����á�"+battle_name+HIR"��"NOR);

                foreach(string id in keys(battle_player))
                {
                        if( !objectp(player = find_player(id)) )
                                continue;

                        restore_status(player);
                        //player->move(LEAVE_ROOM);
                }
        }
        set_heart_beat(0);
}

void create()
{
        object ob;
        string *names;

        seteuid(ROOT_UID);

        names = get_dir(BATTLE_FIELD_DIR+ "*.c");
        names = map_array(names, (: $1[0..<3] :));

        // �������е�ս��
        foreach (string name in names)
        {
                if (objectp(ob = find_object(BATTLE_FIELD_DIR + name)))
                {
                        ob->refresh_map();
                        destruct(ob);
                }
        }
}

string query_name()
{
        return "ս��ϵͳ(BATTLEFIELD_D)";
}
