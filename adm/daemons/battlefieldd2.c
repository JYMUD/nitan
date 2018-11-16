// This program is a part of NT MudLIB
// battelfieldd.c

#include <ansi.h>

#define BATTLE_AREA             "battlefield"
#define BATTLE_NPC              ([ "/maze/battle/npc/berserker" : range_random(100, 120), "/maze/battle/npc/mars" : 10, ])
#define BATTLE_TIME             1800
#define BATTLE_JOIN_TIME        180
#define BATTLE_X_START          0
#define BATTLE_Y_START          0
#define BATTLE_X_END            9
#define BATTLE_Y_END            9
#define BATTLE_ROOM             "/maze/battle/"
#define ENTRY_ROOM              "/d/city/wumiao"

//string battle_name = HIY"��ҫ"NOR YEL"֮ս"HIR;
string battle_name = HIY"����"NOR YEL"��ҫ"HIR;
object *battle_npc = allocate(0);
mapping battle_player = allocate_mapping(0);
object *total = allocate(0);

int battle_open_flag = 0;
int battle_start_flag = 0;
int battle_time_countdown = 0;
int battle_start_time = 0;
nosave int max_level = 200;

int check_out(object me);
private void restore_status(object me);
void add_damage_score(object me, int score);
void add_killplayer_score(object me, int score);
void add_killnpc_score(object me, int score);
void add_bouns_score(object me, int score);
void calculate_score();
void refresh_battlefield();

int clean_up()
{
        return 1;
}

int in_battle(object me)
{
        return battle_start_flag && !undefinedp(battle_player[me->query_id(1)]);
}

int inside_battlefield(object me)
{
        string room;
        object env = environment(me);

        if( !objectp(env) )
                return 0;

        room = base_name(env);
        if( !sscanf(room, BATTLE_ROOM "%*s") )
                return 0;

        return 1;
}

int query_battle_time()
{
        return battle_time_countdown;

}

int query_player_number(object player)
{
        return member_array(player->query_id(1), keys(battle_player)) + 1;
}

object query_random_site(int xstart, int xend, int ystart, int yend)
{
        object where;

        where = get_object(sprintf("/maze/battle/maze/%d/%d", range_random(xstart, xend), range_random(ystart, yend)));
        return where;
}

void move_to_random_site(object me)
{
        object site = query_random_site(BATTLE_X_START, BATTLE_X_END, BATTLE_Y_START, BATTLE_Y_END);

        me->move(site);
}

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

void init_player(object me)
{
        tell_object(me, HIY "����ǰ��Ȼһ��...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        tell_object(me, HIR "�㱻���͵�ս����...��\n");
        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });

        move_to_random_site(me);
}

// ����ս��
void join_battle(object me)
{
        mapping cnd;
        string id = me->query_id(1);

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "��Ŀǰ����ս���У������ȴ���Ŀǰ�Ķ�����˵�ɡ�\n");

        if (me->is_in_prison()) 
                return tell_object(me, "�����������أ������ʲô����\n"); 

        if (me->is_ghost()) 
                return tell_object(me, "�㻹�ǵȻ�������˵�ɣ�\n"); 

        if( !battle_open_flag )
                return tell_object(me, battle_name+"Ŀǰ�޷�������\n");

        if( query("combat_exp", me) < 1000000 )
                return tell_object(me, "����㱾�¾ͱ��ȥ����\n");

        if( max_level && query("level", me) > max_level )
                return tell_object(me, "��ͱ��ȥ�۸���Щ����ɡ�\n");

        if( mapp(cnd = me->query_condition()) && sizeof(cnd))
        {
               if( !undefinedp(cnd["hunger"]) )
                        return tell_object(me, "�㻹�����ҵ�ԵĶ�����˵�ɡ�\n");

               if( !undefinedp(cnd["killer"]) )
                        return tell_object(me, "�ٸ�����ͨ���㣬�㻹���������ͷ¶�棿\n");

               if( !undefinedp(cnd["bandage"]) )
                        return tell_object(me, "�㻹�ǵȰ������˿�ֹס��Ѫ��˵�ɣ�\n");

               if( !undefinedp(cnd["putizi_drug"]) )
                        return tell_object(me, "��շ��������Ӳ��ã��ú��˹������ɰɣ�\n");

               if( !undefinedp(cnd["vote_clear"]) )
                        return tell_object(me, "����������ڶ�����б������𵽴����ߡ�\n");

                return tell_object(me, "������״̬���ѣ����Ǳ��ȥ�ˡ�\n");
        }

        if( !undefinedp(battle_player[id]) )
        {
                if( !battle_start_flag )
                        return tell_object(me, "���Ѿ�����������ε�ս���������ĵȺ������\n");

                if( inside_battlefield(me) )
                        return tell_object(me, "���Ѿ���ս���У����ɱ�аɡ�\n");

                if( !query_temp("battle_rejoin", me) )
                        return tell_object(me, "�����ʹ��ս��ѫ�·������½���ս����\n");

                delete_temp("battle_rejoin", me);
                init_player(me);
                return;
        }

        battle_player[id] = allocate_mapping(0);
        battle_player[id]["jointime"] = time();

        CHANNEL_D->channel_broadcast("war", "Ŀǰ���� "+sizeof(battle_player)+
                                            " λ��ұ������롸"+battle_name+"��");

        if( battle_start_flag )
        {
                init_player(me);
        }
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

        addn("honors", -100, me);
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        CHANNEL_D->channel_broadcast("war", "Ŀǰ���� "+sizeof(battle_player)+
                                            " λ��ұ������롸"+battle_name+"��");
}

int check_quit(object me)
{
        CHANNEL_D->channel_broadcast("war", "���" + me->name(1) +"�ڡ�"+battle_name+"�����������ӣ������ˡ�"NOR);
        restore_status(me);

        addn("honors", -500, me);
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        if( arrayp(total) )
                total -= ({ me });

        tell_object(me, HIC "��һ�����ӳ���ս����������������㳡��\n" NOR);

        // continue run quit function
        me->move("/d/city/guangchang");
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
                add_damage_score(who, damage/3);

        return 0;
}

// check all the players who join the competition
private void auto_check()
{
        object ob;
        string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]) )
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, BATTLE_ROOM "%*s"))
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0; // ���������μ�ս���ļ�¼
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        // kickout the players who lost competition
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
        if( !sscanf(room, BATTLE_ROOM "%*s") )
        {
                // not in pk room
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
                msg = me->name(1) + "����" + ob->name(1) + "�Ķ��֣�������Уˡ�\n";
                if( userp(ob) )
                {
                        if( userp(me) )
                        {
                                if( !query("doing", me) && query_ip_number(ob) != query_ip_number(me) )
                                if( me->query_family() != ob->query_family() )
                                        add_killplayer_score(ob, 1);
                        }
                        else
                        {
                                add_killnpc_score(ob, 1);
                                return 0;
                        }
                }
        } else
                 msg = me->name(1) + "�������ѣ��������ޡ��Ѿ�����Уˡ�\n";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });
        me->move(ENTRY_ROOM);
        message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����"
                "һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������"
                "������ӡ�\n", environment(me), ({ me }));
        tell_object(me, "�������У�����ñ���������������"
                "���ص�ˤ���˵��ϡ�\n");

        if( !living(me) )
                me->revive();

        return 1;
}

void add_npc(string file)
{
        object site = query_random_site(BATTLE_X_START, BATTLE_X_END, BATTLE_Y_START, BATTLE_Y_END);
        object npc = new(file);

        npc->set_override("die", (: call_other, __FILE__, "check_out" :));
        set_temp("battle_npc", 1, npc);
        battle_npc += ({ npc });
        npc->move(site);
        tell_room(site, HIY+npc->query_idname()+HIY"ͻȻ�ӽ�����˳�����\n"NOR);
}

// ����ս��
void start_battle()
{
        object player;
        object* unavailable_players = allocate(0);

        if( sizeof(battle_player) < 5 )
        {
                set_heart_beat(0);
                total = allocate(0);
                battle_player = allocate_mapping(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "�������롸"+battle_name+"��ս�۵���Ҳ��� 5 �ˣ�ȡ������ս�ۡ�");
                return;
        }

        foreach(string file, int count in BATTLE_NPC)
        {

                while(count--)
                        add_npc(file);
        }

        CHANNEL_D->channel_broadcast("war", "��"+battle_name+"����ʼ���������� "+sizeof(battle_player)+
                                            " λ��Ҳ��롸"+battle_name+"������ʱ "+(BATTLE_TIME/60)+" ���ӽ���");


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

                init_player(player);
                //tell_object(player, "\a��"+battle_name+"����ʼ���㱻���͵�ս����...\n");
        }

        foreach(player in unavailable_players)
                cancel_battle(player);

        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

// ��ʼ���ܱ��� TIME_D ����
varargs void start_join(string level)
{
        CHANNEL_D->channel_broadcast("war", HIY"��ҫ"NOR YEL"֮ս"HIR"����ս�����ᣬ������ "+(BATTLE_JOIN_TIME/60)+
                                            " ���Ӻ󷢶���"+battle_name+"��("+level+"��)����ʹ�� fbattle ָ�����ս�ۡ�");

        total = allocate(0);
        battle_npc = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;
        if( level ) max_level = to_int(level);

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

int get_player_score(string id)
{
        if( undefinedp(battle_player[id]) ) return 0;

        return battle_player[id]["killplayer"]*100 + battle_player[id]["killnpc"]*3 + (battle_player[id]["damage"]/500000>500?500:battle_player[id]["damage"]/500000) + battle_player[id]["bonus"];
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

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killplayer"] += score;

        return;
}

void add_dead_score(object me, int score)
{
        string id = me->query_id(1);
        string *sorted_players = get_sorted_players();

        if( undefinedp(battle_player[id]) )
                return;

        if( sizeof(sorted_players) > 0 && sorted_players[0] == id )

                battle_player[id]["bonus"] -= 40;

        battle_player[id]["dead"] += score;
}


void add_bonus_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )

            return;

        battle_player[id]["bonus"] += score;
        //addn("honors", score, me);

        return;
}

/*
void remove_battlefield_condition(object player)
{
        player->clear_condition(BATTLEFIELD_EXPERIENCE);
        player->clear_condition(BATTLEFIELD_GLORY);
        player->clear_condition(BATTLEFIELD_FEAR);
}
*/
void stop_battle()
{
        object player;

        set_heart_beat(0);

        foreach(string id in keys(battle_player))
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                //player->remove_all_killer();
                player->remove_all_enemy(1);
        }

        foreach(object npc in battle_npc)
        {
                if( !objectp(npc) )
                        continue;

                destruct(npc);
        }

        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;

        call_out((: calculate_score :), 5);

        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);
        CHANNEL_D->channel_broadcast("war", "��"+battle_name+HIR"�����ڽ���ƽϢ..."NOR);
        CHANNEL_D->channel_broadcast("war", "��"+battle_name+HIR"������ͳ��ս��..."NOR);
        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);
}

void calculate_score()
{
        int score;
        int rank;
        mapping famscore = allocate_mapping(0);
        string family;
        object player;
        string file;
        object insigne;
        int insigne_count;
        string *sorted_players = get_sorted_players();
        int lv1,lv2,lv3,lv4;
        int players_count = sizeof(sorted_players);

        map_delete(battle_player, 0);

        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);

        lv2 = players_count/4;
        if( lv2 < lv1+2 ) lv2 = lv1+2;

        lv3 = to_int(players_count/1.5);
        if( lv3 < lv2+3 ) lv3 = lv2+3;

        lv4 = to_int(players_count/1.2);
        if( lv4 < lv3+5 ) lv4 = lv3+5;

        rank = 0;
        foreach(string id in sorted_players)
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                family = player->query_family();
                score = get_player_score(id);

                CHANNEL_D->channel_broadcast("war", (++rank)+"."+(family||"��ͨ����")+"��"+player->query_idname()+HIR"����ɱ "+battle_player[id]["killplayer"]+" λ��ҡ�"+battle_player[id]["killnpc"]+" ��NPC���ܼ���ɵ��� "+NUMBER_D->number_symbol(battle_player[id]["damage"])+" ���˺���ս������Ϊ "+NUMBER_D->number_symbol(score)+(battle_player[id]["bonus"]>=0 ? "("NOR CYN"+"HIC+battle_player[id]["bonus"]+HIR")":"("NOR RED"-"HIR+(-battle_player[id]["bonus"])+HIR")")+" ��");

                if( undefinedp(famscore[family]) )
                        famscore[family] = allocate_mapping(0);

                if( famscore[family]["score"] < score )
                        famscore[family]["score"] = score;

                famscore[family]["player"] += 1;
                
                addn("battle/score", score, player);
                addn("honors", score, player);
                
                if( score > 1000 ) score = 1000;
                        GIFT_D->delay_battle_bonus(player, ([ "exp" : score*3000, "pot" : score*300, "mar" : score/10, "score" : score ]));

                if( score < 25 || battle_player[id]["jointime"] > time() - 600 ) continue;

                insigne_count = 0;

                if( rank <= lv1 )
                {
                        insigne_count = 8;
                }
                else if( rank <= lv2 )
                {
                        insigne_count = 7;
                }
                else if( rank <= lv3 )
                {
                        insigne_count = 7;
                }
                else if( rank <= lv4 )
                {
                        insigne_count = 6;
                }
                else
                {
                        insigne_count = 2;
                }

                if( insigne_count > 0 )
                {
                        insigne = new("/clone/battle/battle_insigne");
                        insigne->set_amount(insigne_count);
                        tell_object(player, "���� "+insigne_count+" ö"+insigne->name(1)+"��\n");
                        insigne->move(player, 1);
                }
        }

        CHANNEL_D->channel_broadcast("war", WHT"����������������������������������������������������������������"NOR);
        rank = 0;
        foreach(family in sort_array(keys(famscore), (: $(famscore)[$2]["score"] - $(famscore)[$1]["score"] :)))
        {
                CHANNEL_D->channel_broadcast("war", (family||"��ͨ����")+"��ս��������Ϊ "+NUMBER_D->number_symbol(famscore[family]["score"])+"��������������� "+(++rank)+" ����\n");    
                
                switch(rank)
                {
                        case 1:
                                switch(random(3))
                                {
                                        case 0:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ���������������齱������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "exp", 14400);
                                                break;
                                        case 1:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ��������������Ǳ�ܽ�������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "pot", 14400);
                                                break;
                                        case 2:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ�ڵ�����������ɣ�\n");
                                                FAMILY_D->set_family_efficient(family, "mf", 14400);
                                                break;
                                        case 3:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ���о�Ч������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "yanjiu", 14400);
                                                break;
                                }                               
                                CHANNEL_D->channel_broadcast("news", family+"����������߰˰ٵ㡣��\n");
                                FAMILY_D->add_family_fame(family, 800);
                                break;
                        case 2:
                                switch(random(3))
                                {
                                        case 0:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ���������������齱������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "exp", 7200);
                                                break;
                                        case 1:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ��������������Ǳ�ܽ�������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "pot", 7200);
                                                break;
                                        case 2:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ�ڵ�����������ɣ�\n");
                                                FAMILY_D->set_family_efficient(family, "mf", 7200);
                                                break;
                                        case 3:
                                                CHANNEL_D->channel_broadcast("news", family+"���е����ڽ�������Сʱ���о�Ч������һ����\n");
                                                FAMILY_D->set_family_efficient(family, "yanjiu", 7200);
                                                break;
                                }                               
                                CHANNEL_D->channel_broadcast("news", family+"�������������ٵ㡣��\n");
                                FAMILY_D->add_family_fame(family, 500);
                                break;
                        default:
                                break;
                }
        }
        
        CHANNEL_D->channel_broadcast("combat", WHT"����������������������������������������������������������������"NOR);

        //foreach(string id in keys(battle_player))
        foreach(player in total)
        {
                //if( !objectp(player = find_player(id)) )
                if( !objectp(player) )
                        continue;

                restore_status(player);
                player->move(ENTRY_ROOM);

                tell_object(player, "��"+battle_name+"���������㱻����ս��...\n");

        }

        total = allocate(0);
        battle_npc = allocate(0);
        battle_player = allocate_mapping(0);
        refresh_battlefield(); 
}


mapping query_battle_player()
{
        return battle_player;
}

void refresh_battlefield()
{
        object maze;

        if( maze = find_object("/maze/battle/maze.c") )
                destruct(maze);
}

int remove()
{
        if( sizeof(battle_player) )
        {
                object player;

                CHANNEL_D->channel_broadcast("war", "ϵͳ���£����á�"+battle_name+HIR"��"NOR);

                foreach(string id in keys(battle_player))
                {
                        if( !objectp(player = find_player(id)) )
                                continue;

                        restore_status(player);
                        player->move(ENTRY_ROOM);
                }
        }

        if( sizeof(battle_npc) )
        {
                foreach(object npc in battle_npc)
                {
                        if( !objectp(npc) )
                                continue;

                        destruct(npc);
                }
        }

        refresh_battlefield();
        return 1;
}

void heart_beat()
{
        string *directions = ({ "north", "south", "east", "west" });
        object where;

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
                                                                    " ���Ӻ󷢶���"+battle_name+"������ʹ�� fbattle ָ�����ս�ۡ�");
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

        auto_check();

        if( battle_time_countdown == 1200 || battle_time_countdown == 600 )
        {
                foreach(string file, int count in BATTLE_NPC)
                {
                        while(count--)
                                add_npc(file);
                }
        }

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", "��"+battle_name+"�������� "+(battle_time_countdown/60)+" ���Ӻ����...");

        if( !(battle_time_countdown%90) )
        {
                object statue;

                if( !random(2) )
                        statue = new("/clone/battle/battlefield_glory_statue");
                else
                        statue = new("/clone/battle/battlefield_fear_statue");

                where = query_random_site(BATTLE_X_START+4, BATTLE_X_END-4, BATTLE_Y_START+4, BATTLE_Y_END-4);

                statue->move(where);

                CHANNEL_D->channel_broadcast("war", "����ǿ������������ʯ��������"+where->short()+"����...");
        }

        if( !(battle_time_countdown%60) )
        {
                object player;
                string* sorted_players = get_sorted_players();
                int size = sizeof(sorted_players);

                for(int i=size*2/3;i<size;++i)
                {
                        if( objectp(player = find_player(sorted_players[i])) )
                        {
                                if( !inside_battlefield(player) ) continue;
                                tell_object(player, "��Ŀǰ��ս����󣬻�ö��������ӳ֡�\n");

                                //player->apply_condition(BATTLEFIELD_EXPERIENCE);

                                //if( i > size*4/5 )
                                        //player->apply_condition(BATTLEFIELD_EXPERIENCE);
                        }
                }
        }
        foreach(object npc in battle_npc)
        {
                if( !objectp(npc) )
                        continue;

                if( !random(10) )
                {

                        if( npc->is_fighting() )
                                continue;

                        if( sizeof(directions) )
                                npc->do_command("go "+directions[random(sizeof(directions))]);
                }
        }

        battle_npc -= ({ 0 });
}

private void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
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
        delete_temp("apply/short", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;
}

void create()
{
        seteuid(ROOT_UID);
}

string query_name()
{
        return "ս��ϵͳ(BATTLEFIELD_D)";
}
