// Ward.c ����ս�������Ƴ���
// Created by Lonely 2000.7.20
// Rewrite by Lonely@nitan3 2007/11/28


#include <ansi.h>
#include <room.h>
#include <combat.h>
#include <command.h>

#define END_TIME        1800
#define MENG_TIME       150
#define SONG_TIME       300
#define MOVE_TIME       3
#define COST_TIME       60
#define TRAIN_TIME      3
#define ASSI_TIME       180
#define RIDE_CMD        "/cmds/std/ride"
#define UNRIDE_CMD      "/cmds/std/unride"

inherit F_DBASE;

class ward_info
{
        int economy;     /* ���ù��� */
        int horses;      /* ս������ */
        int weapons;     /* �������� */
        int stones;      /* ʯľ���� */
        int arrows;      /* ������� */
        int soilders;    /* ��Դ���� */
        int moneys;      /* �������� */
        int forages;     /* �������� */
        int count;       /* �������� */
        object marshal;  /* ��    ˧ */
        object *generals;/* �� �� �� */
}

class ward_info song_info;
class ward_info meng_info;
nosave int have1;
nosave int have2;
nosave int start_time;
nosave int valid_check;
nosave int mg_event_id;
nosave int sc_event_id;
nosave int xl_event_id;
nosave int yd_event_id;
nosave int xh_event_id;
nosave int wc_event_id;
nosave int ap_event_id;
nosave int xt_event_id;
nosave string *ip_numbers;
public string ask_kingwar(object me);
public string join_kingwar(object ob);
public int start_kingwar(object me);
protected int check_out(object me);
protected int check_quit(object me);
protected void init_general(object me);
protected void init_player(object me);
protected void init_marshal(object me);
protected void auto_check();
protected void auto_fight();
public void auto_beat();
public void auto_move();
public void auto_cost();
public void auto_train();
varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room);
public void attack_over(object me);
protected void remove_enemy();
protected void give_bouns();
public void fail_kingwar();
public void win_kingwar();
public void finish_kingwar();
protected void restore_status(object me);
protected void restore_kingwar();
protected void message_ward(string msg);
public int query_stones(object me);
public int query_arrows(object me);
public int expend_stones(object me, int count);
public object query_marshal() { return song_info->marshal; }
public object *query_generals() { return song_info->generals; }
public string query_continue_time() { return time_period(time() - start_time); }
public string *query_ip_numbers() { return ip_numbers; }
#include <war.h>

string *zhen1 = ({ "��ͨ��","������","��ʸ��","������","������","��Բ��","������","������","������" });
mapping zhen2 = ([
        "��ͨ��" : ({  0,  -5,   5,  -5,   5,  -5,   5,  -5,   5 }),
        "������" : ({  5,   0,  10,  10,  -5,  10,  -5,   5, -10 }),
        "��ʸ��" : ({ -5, -10,   0,  10,   5,  -5,  10, -10,   5 }),
        "������" : ({  5,  10, -10,   0,  -5,  -5, -10,  10,   5 }),
        "������" : ({ -5,   5,  -5,   5,   0, -10, -10,  10,  10 }),
        "��Բ��" : ({  5, -10,   5,   5,  10,   0,  -5,  -5,  -5 }),
        "������" : ({ -5,   5, -10,  10,  10,   5,   0, -10,  -5 }),
        "������" : ({  5,  -5,  10, -10, -10,   5,  10,   0,  -5 }),
        "������" : ({ -5,  10,  -5,  -5, -10,   5,   5,   5,   0 }),
]);
int zhen_power(string type1, string type2)
{
        int i, type2_i = 0;

        for (i = 0; i < sizeof(zhen1); i++)
        {
                if (type2 == zhen1[i])
                {
                        type2_i = i;
                        break;
                }
        }

        if (! type2_i) return 0;
        if (undefinedp(zhen2[type1])) return 0;
        if (type2_i > sizeof(zhen2[type1][type2_i]))
                return 0;

        return zhen2[type1][type2_i];
}

int clean_up() { return 1; }

/*
void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(song_info->generals))
                error("ս�����飺Ŀǰ����������ڲ�������ս�����㲻�ܴݻ�ս�����顣\n");
}
*/
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "ս������");
        CHANNEL_D->do_channel(this_object(), "sys", "����ս���Ѿ�������");

        song_info = new(class ward_info);
        meng_info = new(class ward_info);

        meng_info->marshal = 0;
        song_info->marshal = 0;
        have1 = 0;
        have2 = 0;
        valid_check = 0;
}

void valid_inquiry()
{
        valid_check = 1;
        return;
}

int do_inquiry(object me, string arg)
{
        object ob;
        object *total;
        mixed *info;
        string str, quest;
        int i, group;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                tell_object(me, "����ǰ��û���κ�ս�£�\n");
                return 0;
        }

        valid_inquiry();

        if (stringp(arg) && arg == "meng")
        {
                if (! valid_check && ! wizardp(me))
                {
                        tell_object(me, "��ľ���Ŀǰ��û������̽���ɹž��ӵ��鱨��\n");
                        return 0;
                }

                total = meng_info->generals;
                info = ({ meng_info->forages, meng_info->moneys,
                           meng_info->weapons, meng_info->horses,
                          meng_info->stones,  meng_info->arrows,
                          meng_info->soilders,meng_info->economy,
                          meng_info->count });
        }
        else
        {
                total = song_info->generals;
                info = ({ song_info->forages, song_info->moneys,
                          song_info->weapons, song_info->horses,
                          song_info->stones,  song_info->arrows,
                          song_info->soilders,song_info->economy,
                          song_info->count });
        }

        group = 0;
        for (i = 0; i < sizeof(total); i++)
                if (objectp(total[i]))
                        group+=query_temp("warquest/group", total[i]);

        str = (arg == "meng" ? "�ɹ�" : "����") + "Ŀǰ����������״��";
        str += "\n\n";
        str += HIC "��" HIY "����������������������������������������������������" HIC "��\n" NOR;

        str += sprintf(WHT "���ݣ�%-10d��\t\t    ������%-10d��\n" NOR, info[0], info[1]);
        str += sprintf(WHT "���ף�%-10d��\t\t    ս��%-10dƥ\n" NOR, info[2], info[3]);
        str += sprintf(WHT "ʯľ��%-10d��\t\t    �����%-10d֧\n" NOR, info[4], info[5]);
        str += sprintf(WHT "��Դ��%-10d��\t\t    ������%-10d��\n" NOR, info[6], info[7]);
        str += sprintf(WHT "���죺%-10d��\t\t    ʿ����%-10dӪ\n" NOR, sizeof(total), group);

        str += HIC "\nĿǰ�пɵ��ȵĽ����������£�\n" NOR;

        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                        continue;

                ob = total[i];

                quest=query_temp("warquest/quest", ob);
                if (! quest) quest = "������Ӫ��δ��ǲ��";

                str += sprintf("%s%-" + (35+color_len(ob->short(1))) + "s ͳ����%-10dӪ\n" NOR,
                                (ob == me ? HIC : WHT), ob->short(1),
                                query_temp("warquest/group", ob));
                str += sprintf("%s����%-29s λ�ã�%s\n", (ob == me ? NOR : NOR), quest, environment(ob)->short(1));
        }
        str += "\n\n";
        str += "ս���Ѿ�����ʱ�� " + query_continue_time() + " \n";
        str += HIB "����������" + chinese_number(info[8] - sizeof(total)) + "��\n" NOR;
        str += HIC "��" HIY "����������������������������������������������������" HIC "��\n" NOR;
        write(str);
        return 1;
}

int query_moneys()
{
        return song_info->moneys;
}

int change_moneys(int count)
{
        song_info->moneys += count;
        return 1;
}

int query_economy(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->economy;
        else
                return meng_info->economy;
}
        
int query_horses(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->horses;
        else
                return meng_info->horses;
}
      
int query_weapons(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->weapons;
        else
                return meng_info->weapons;
}
  
int query_stones(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->stones;
        else
                return meng_info->stones;
}

int query_arrows(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->arrows;
        else
                return meng_info->arrows;
}

int expend_stones(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->stones -= count;
        else
                meng_info->stones -= count;

        return 1;
}

int query_soilders(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->soilders;
        else
                return meng_info->soilders;
}

int expend_soilders(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->soilders -= count;
        else
                meng_info->soilders -= count;

        return 1;
}

int query_forages(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->forages;
        else
                return meng_info->forages;
}

void init_marshal(object me)
{
        object bingfu, kaijia;

        set_temp("title", HIW"���α����Ԫ˧"NOR, me);
        set_temp("warquest/party", "song", me);
        set("eff_qi",query("max_qi",  me)+1000*query("degree_jungong", me), me);
        set("qi",query("eff_qi",  me), me);
        set_temp("warquest/train", "infantry", me);
        me->set_override("quit", (: call_other, __FILE__, "fail_kingwar" :));
        me->set_override("die", (: call_other, __FILE__, "marshal_die" :));

        if (! objectp(kaijia = present("kai jia", me)))
        {
                kaijia = new("/d/city2/song/obj/tiejia");
                kaijia->move(me);
        }

        if (! objectp(bingfu = present("bing fu", me)))
        {
                bingfu = new("/adm/npc/obj/bingfu");
                set("owner",query("id",  me), bingfu);
                bingfu->move(me);
        }

        tell_object(me, HIC "\n���ˣ����п���֮���Ѿ���ʣ�޼���������Ӫ�������п�һս���˴�\n" +
                        "���������ص�Զ�������¹��Ҵ��ι��ˣ��������˾�����Ϊ��������\n" +
                        "���յ�ʤ�������س����������Ϊ��������ǧ�����������˽�����\n\n" NOR);

        song_info->count = 1;
        song_info->marshal = me;
        song_info->generals = ({ me });
#ifdef DB_SAVE
        if( !MEMBER_D->is_valid_member(query("id", me)) )
#endif
        ip_numbers += ({ query_ip_number(me) });
        set("kingwar_time", time(), me);
}

// set player's override functions
void init_player(object me)
{
        set_temp("warquest/party", "song", me);
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "general_die" :));
        // me->set_temp("override/exert", (: call_other, __FILE__, "exert" :));

        set_temp("warquest/time", time(), me);
        me->move("/d/city2/sying1");
        tell_object(me, HIY "�㶨��һ������ŷ����Լ��Ѿ�����" +
                            environment(me)->short() + HIY "��\n");

        song_info->count++;
        song_info->generals += ({ me });
#ifdef DB_SAVE
        if( !MEMBER_D->is_valid_member(query("id", me)) )
#endif
        ip_numbers += ({ query_ip_number(me) });
}

void init_general(object me)
{
        string array1, array2, party;
        int degree, flag = 0;
        object ling, horse;

        if (me == meng_info->marshal)
                flag = 1;

        party=query_temp("warquest/party", me);
        degree=4+random(query("combat_exp", me)/5000000+1);

        if (! flag)
        {
                if (degree > 12) degree = 12;
        } else
        {
                if (degree > 16) degree = 16;
        }

        if (! arrayp(meng_info->generals) || ! sizeof(meng_info->generals))
                meng_info->generals = ({ });

        if (! arrayp(song_info->generals) || ! sizeof(song_info->generals))
                song_info->generals = ({ });

        array1 = zhen1[random(sizeof(zhen1))];
        array2 = zhen1[random(sizeof(zhen1))];

        if (party == "meng")
        {
                // һ��Ӫ�ľ���Ϊ2000��
                addn("eff_qi", degree*2000, me);
                set("qi",query("eff_qi",  me), me);
                set_temp("warquest/group", degree, me);
                set_temp("warquest/array", array1, me);
                set("degree_jungong", degree, me);

                if (degree > 10) set_temp("title", HIR "�ɹ����" NOR, me);
                else if (degree > 8) set_temp("title", HIG "�ɹž�����" NOR, me);
                else if (degree > 5) set_temp("title", HIY "�ɹ�ǧ��" NOR, me);
                else set_temp("title", HIC "�ɹŰٷ�" NOR, me);

                horse = new("/d/city2/meng/horse");
                horse->move(environment(me));
                RIDE_CMD->do_ride(me, horse);
                meng_info->soilders -= degree * 2000;
                meng_info->weapons -= degree * 4000;
                meng_info->horses -= degree * 2000;
                meng_info->generals += ({ me });
                meng_info->count++;
                return;
        } else
        if (party == "song")
        {
                set_temp("title", degree_desc[degree-4], me);
                set("degree_jungong", degree, me);
                set_temp("warquest/array", array2, me);
                ling = new("/adm/npc/obj/lingjian");
                set("owner",query("id",  me), ling);
                ling->move(me, 1);
                song_info->generals += ({ me });
                song_info->count++;
                return;
        }
}

int marshal_die()
{
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG "���ɹ��������ξ�����������\n" +
                "              �ξ���˧ " HIR + query("name", song_info->marshal) + " ( " + query("id", song_info->marshal) + " ) " NOR +
                MAG "ս��ɳ��������ѳ������\n              ��������δѩ�����Ӻ޺�ʱ�𰡣�\n" NOR);

        fail_kingwar();
        return 0;
}

string ask_kingwar(object me)
{
        if (me->query_condition("junquest_fail"))
                return "�������Ǵ���֮�����Գ������������ѱ�����������ذɣ�\n";

        if( query("degree_jungong", me)<8 )
                return "���˹ٵ�λ�����������һ��֮˧���ѷ������ģ���\n";

        if (me->query_skill("craft-cognize", 1) < 120)
                return "���˲�����ͨ�������������һ��֮˧���ѷ������ģ���\n";

        if (me->query_skill("array-cognize", 1) < 120)
                return "���˲�����ͨ�б������������һ��֮˧���ѷ������ģ���\n";

/*
        if( query("kingwar_time", me)+3600>time() )
                return "���˸���ս�������ã���������һ��ʱ�����˵��\n";
*/

        if (objectp(song_info->marshal))
        {
                if (me == song_info->marshal)
                        return "�����Ѿ������������ˣ���������ĥ��ʲô������\n";
                else
                        return "�����Ѿ���" + song_info->marshal->name(1) + "�ʾ������ˣ����˿���ǰȥ����\n";
        }

        if (start_kingwar(me))
        {
                return "���˻��ǿ����̰ɣ��������г̿ɾ��鷳�ˣ�\n";
        }

        return "�ƺ������˵����⣬�㻹������ʦ�ɣ�\n";
}

// start war
int start_kingwar(object me)
{
        object marshal, general, jianjun, room;
        int i;

        ip_numbers = ({ });
        init_marshal(me);

        message_ward(CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                MAG "�ɹſɺ�������֣������ɳ�\n " +
                ""+"�����Ԫ˧"+query("name", me)+MAG+"("+query("id", me)+MAG+")"+
                MAG + "����ʦ���Ͽ���......\n" NOR);

        room = get_object("/d/city2/syuanmen1");
        if (objectp(room))
                set("defence", 200, room);

        room = get_object("/d/city2/myuanmen1");
        if (objectp(room))
                set("defence", 999, room);

        room = get_object("/d/city2/majiu");
        room->reset();

        meng_info->economy = 1000000;
        meng_info->moneys = 10000000;
        meng_info->forages = 10000000;
        meng_info->weapons = 4000000;
        meng_info->stones = 500000;
        meng_info->horses = 2000000;
        meng_info->arrows = 500000;
        meng_info->soilders = 2000000;

        // �����ɹž���
        marshal = new("/d/city2/meng/kehan");
        marshal->move("/d/city2/mying1");
        set_temp("warquest/quest", "�Ӿ����£����ִ���", marshal);
        meng_info->marshal = marshal;
        meng_info->count = 0;
        init_general(marshal);
        general = new("/d/city2/meng/mengj");
        general->move("/d/city2/mying1");
        set_temp("warquest/quest", "������Ӫ�������ɺ�", general);
        init_general(general);

        for (i = 0; i < 4; i++)
        {
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/mying");
                set_temp("warquest/quest", "������Ӫ�������ɺ�", general);
                init_general(general);
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/dhunya");
                init_general(general);
                set_temp("warquest/quest", "������Ӫ�������ɺ�", general);
        }

        if( query("degree_jungong", me)>10 )
        for (i = 0; i < 2; i++)
        {
                general=new("/d/city2/meng/mengj");
                general->move("/d/city2/caoyuan");
                set_temp("warquest/quest", "������ԭ����ֹ����", general);
                init_general(general);
        }

        if( query("degree_jungong", me)>12 )
        for (i = 0; i < 2; i++)
        {
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/myuanmen1");
                set_temp("warquest/quest", "������Ӫ����ֹ����", general);
                init_general(general);
        }

        // ��ʼ���γ���������
        song_info->economy = 1200000;
        song_info->moneys = 50000000;
        song_info->forages = 240000;
        song_info->stones = 240000;
        song_info->arrows = 240000;
        song_info->horses = 60000;
        song_info->weapons = 240000;
        song_info->soilders = 120000;

        jianjun = new("/d/city2/npc/jianjun");
        jianjun->move("/d/city2/sying1");
        init_general(jianjun);
        set_temp("warquest/quest", "������Ӫ��������", jianjun);

        // �����ξ�
        for(i = 0; i < 4; i++)
        {
                general = new("/d/city2/song/songb");
                general->move("/d/city2/sying1");
                init_general(general);
        }

        start_time = time();
        mg_event_id = SCHEDULE_D->set_event(MENG_TIME, 1, this_object(), "continue_kingwar", "meng");
        sc_event_id = SCHEDULE_D->set_event(SONG_TIME, 1, this_object(), "continue_kingwar", "song");
        xl_event_id = SCHEDULE_D->set_event(TRAIN_TIME, 1, this_object(), "auto_train");
        yd_event_id = SCHEDULE_D->set_event(MOVE_TIME, 1, this_object(), "auto_move");
        xh_event_id = SCHEDULE_D->set_event(COST_TIME, 1, this_object(), "auto_cost");
        wc_event_id = SCHEDULE_D->set_event(END_TIME, 0, this_object(), "finish_kingwar");
        ap_event_id = SCHEDULE_D->set_event(ASSI_TIME, 1, this_object(), "check_assignment");
        xt_event_id = SCHEDULE_D->set_event(1, 1, this_object(), "auto_beat");
        // set_heart_beat(1);

        return 1;
}

string join_kingwar(object me)
{
        if (! objectp(song_info->marshal))
                return "����ǰ��û��ս�£��������Ժ������ɣ�\n";

        if (me == song_info->marshal)
                return "Ԫ˧����Ҫ����Ц�ˣ�\n";

        if ((time() - start_time) > 1800)
                // return "����ǰ��ս�¿�Ҫ�����ˣ��������Ժ������ɣ�\n";
                return "����ǰ��ս����Ϳ�ʼ�ˣ��������Ժ������ɣ�\n";

        if (member_array(query_ip_number(me), ip_numbers) != -1
#ifdef DB_SAVE
         && !MEMBER_D->is_valid_member(query("id", me) )
#endif
           )
                return "�ǻ�Աÿ��IP��ֻ��һ��ID�ξ��������������Ժ������ɣ�\n";

        /*
        if( query("age", me)<12 )
                return "����С���Ժ�����Ϊ��Ч���ɣ�\n";
        */

        if( query("combat_exp", me)<100000 )
                return "��־�ɼΣ����������޸���֮������������ذɣ�\n";

        /*
        if( query("degree_jungong", me)<1 )
                return "���ľ���̫��΢�ˣ���ǰ������ûʲô�ð���\n";
        */

        if (member_array(me, song_info->generals) != -1)
                return "�������Ѿ����������ˣ��쵽ǰ��ȥ�ɣ���\n";

/*
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) + MAG "��־֮ʿ" + me->name(1) +
                MAG "����ǰ�߼�����֧Ԯ�ξ������ɹž���֮�У�\n" NOR);
*/

        init_player(me);

        return "��������������ʱ�������ϳ�������ǰ��֧Ԯ�ɣ�\n";
}

// void heart_beat()
void auto_beat()
{
        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
                return;

        // �����Զ���ս
        auto_fight();

        if (time() - start_time > 300)
                auto_check();
}

// check all the players who join the war
void auto_check()
{
        object *total;
        object ob;
        string room;
        object *lost;
        int i;

        room = base_name(environment(song_info->marshal));
        if (! sscanf(room, "/d/city2/%*s") &&
            ! sscanf(room, "/d/xiangyang/%*s") &&
            ! sscanf(room, "/d/wuguan/%*s"))
        {
                message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) + song_info->marshal->name(1) +
                        MAG "��ս�����������ӣ������ξ������죬���Ļ�ɢ�����ɹž���ȫ�߻��ܣ�\n" NOR);
                fail_kingwar();
                return;
        }

        lost = ({ });
        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total = filter_array(total, (: objectp($1) && userp($1) :));
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        // ����Ƿ�����ս��
                        room = base_name(environment(total[i]));
                        if (! sscanf(room, "/d/city2/%*s") &&
                            ! sscanf(room, "/d/xiangyang/%*s") &&
                            ! sscanf(room, "/d/wuguan/%*s"))
                        {
                                message("channel:rumor",
                                        MAG "�����߾��顿���Σ�" + total[i]->name(1) +
                                        MAG "�ľ�����ս�����������ӣ��ξ����Ŀ�ʼ��ɢ��ս�����½���\n" NOR, users());
                                // not in war room
                                restore_status(total[i]);
                                song_info->generals -= ({ total[i] });
                                ip_numbers -= ({ query_ip_number(total[i]) });
                                continue;
                        }
                        // �������ľ���(ѹ��û�д����ĳ���)
                        if( !query_temp("warquest/escort", total[i]) && 
                            !query_temp("warquest/guard", total[i]) && 
                            query_temp("warquest/train", total[i]) && 
                            query("combat_exp", total[i])<20000000 && 
                            member_array(room, ward_place) == -1) {
                                if( query("qi", total[i])<query("max_qi", total[i]) )
                                // total[i]->query_temp("warquest/group") < 1)
                                        lost += ({ total[i] });
                        }
                }
        }

        // song_info->generals -= ({ 0 });
        // kickout the players who lost
        foreach (ob in lost)
                check_out(ob);

        return;
}

void check_assignment()
{
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(ap_event_id);
                return;
        }

        if (time() - start_time < 600)
                return;

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/guard", $1) && 
                                       (sscanf(base_name(environment($1)), "/d/xiangyang/%*s") ||
                                        sscanf(base_name(environment($1)), "/d/wuguan/%*s")) :));

        if (sizeof(total) < 1)
        {
                song_info->economy -= 100000;
                if( song_info->economy < 1000000 )
                message("channel:rumor",
                        MAG "�����߾��顿���Σ��ɹ�ͻ���Ǳ������������ɱ���ӣ����������سǱ���������\n" NOR, users());
                // message_ward(MAG "���α����Ԫ˧���������ĳǷ��������ɹ����������������ɱ���ӡ�\n" NOR);
        }
        return;
}

// ������ս����
// ��Ϊ�ֶ����ƺ�ϵͳ����
void auto_fight()
{
        object *obs, ob, obb, env, room;
        object *total;
        string *dirs;
        string dir;
        string zhen, craft;
        mapping exits;
        int group, number, i, j, team;

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        // ���ݼ�������ȱ������ӱ�
                        if (meng_info->moneys < 1)
                                addn("eff_qi", -1, ob);
                        if (meng_info->forages < 1)
                                addn("eff_qi", -1, ob);

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group < 1) group = 1;
                        set("qi",query("eff_qi",  ob), ob);
                        set_temp("warquest/group", group, ob);

                        // ������������-�ָ�
                        if( query_temp("warquest/recover", ob) )
                                continue;

                        // ������������-����
                        if( query_temp("warquest/confusion", ob) )
                        {
                                set_temp("warquest/recover", 1, ob);
                                ob->start_call_out((: call_other, __FILE__, "recover_status", ob :), 10);
                                continue;
                        }

                        env = environment(ob);
                        obs = all_inventory(env);
                        zhen=query_temp("warquest/array", ob);
                        if( sizeof(obs)>0 && !query_temp("warquest/attack", ob) )
                        {
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "����" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIW "$N" HIW "��������������׼����һ��������г�����ġ�" HIY + zhen +
                                                        HIW "����\n�����µ��ɹž����������⡪��>" HBRED "ͻ��" NOR HIW "����\n" +
                                                        "$N" HIW "һ�����£������������ɹ������ʼ�˿��µĳ�棡��\n" NOR, ob);

                                                craft = "ͻ��";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if( mapp(query("exits", env)) && sizeof(query("exits", env)) && 
                            !query_temp("warquest/attack", ob) )
                        {
                                exits=query("exits", env);
                                dirs = keys(exits);
                                for (j = 0; j < sizeof(dirs); j++)
                                        if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                dirs[j] = 0;
                                dirs -= ({ 0 });
                                if (! sizeof(dirs)) continue;
                                dir = dirs[random(sizeof(dirs))];
                                room = get_object(exits[dir]);

                                if (! objectp(room)) continue;
                                obs = all_inventory(room);
                                if (! sizeof(obs)) continue;
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "����" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIC "$N" HIC "�����������������׼����\n" +
                                                        "һ�����������������������⡪��>" HBRED "����" NOR HIC "����\n" +
                                                        "$N" HIC "һ�����£������뷢��\n" NOR, ob);

                                                craft = "ͻ��";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env, dir, room);
                                                break;
                                        }
                                }
                        }
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        if( query_temp("warquest/group", ob)>0 )
                        {
                                // ���ݼ�������ȱ������ӱ�
                                if (song_info->moneys < 1)
                                        addn("eff_qi", -1, ob);
                                if (song_info->forages < 1)
                                        addn("eff_qi", -1, ob);
                        }

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group > 0)
                                set("qi",query("eff_qi",  ob), ob);
                        if( query_temp("warquest/group", ob)<1 )
                                delete_temp("warquest/group", ob);
                        team=query_temp("warquest/group", ob);
                        number = group - team;

                        if( number>0 && query_temp("warquest/train", ob) )
                        {
                                tell_object(ob, HIR "��ѵ����" HIY + chinese_number(number) + HIR "Ӫ����ʿ�����䵽��ľ����У�\n" NOR);
                                addn_temp("warquest/group", number, ob);
                        } else
                        if( number<0 && team>0 && !query_temp("warquest/train_begin", ob) )
                        {
                                if (abs(number) > team) number = team;
                                else number = abs(number);
                                tell_object(ob, HIW "����ʧ��" HIR + chinese_number(number) + HIW "Ӫ��ʿ����\n" NOR);
                                addn_temp("warquest/group", -number, ob);
                        }

                        // �ж�����Ƿ�����Ϊ�ֶ�����ս��
                        if( !query("env/auto_war", ob))continue;

                        zhen=query_temp("warquest/array", ob);
                        if (! zhen) zhen = "��ͨ��";

                        env = environment(ob);
                        // �����ж�����ܹ���
                        if( !query_temp("warquest/attack", ob) && 
                              query_temp("warquest/group", ob)>0 && 
                            (query_temp("warquest/train", ob) == "cavalry" || 
                              query_temp("warquest/train", ob) == "archer") )
                        {
                                if( mapp(query("exits", env)) && sizeof(query("exits", env)) )
                                {
                                        exits=query("exits", env);
                                        dirs = keys(exits);
                                        for (j = 0; j < sizeof(dirs); j++)
                                                if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                        dirs[j] = 0;
                                        dirs -= ({ 0 });
                                        if (sizeof(dirs))
                                        {
                                                dir = dirs[random(sizeof(dirs))];
                                                room = get_object(exits[dir]);
                                                if (objectp(room))
                                                {
                                                        obs = all_inventory(room);
                                                        if (sizeof(obs) > 0)
                                                        {
                                                                for (j = 0; j < sizeof(obs); j++)
                                                                {
                                                                        obb = obs[j];
                                                                        if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                                                continue;

                                                                        if( query_temp("warquest/train", ob) == "archer" )
                                                                        {
                                                                                if( !query_temp("weapon", ob) )
                                                                                        if (! WIELD_CMD->main(ob, "bow"))
                                                                                                continue;

                                                                                craft = "����";
                                                                                message_vision(HIB "$N" HIB "���������������Ӫ����" HIR + zhen +
                                                                                        HIB "����\nһ�����������������������⡪��>" HBRED + craft +
                                                                                        NOR HIB "����\n$N" HIB "һ�����£������뷢��\n" NOR, ob);
                                                                        } else
                                                                        {
                                                                                craft = "ͻ��";
                                                                                ob->move(room);
                                                                                message_vision(HIC "$N" HIC "�����б���һ�ӣ���ȵ�������Ӫ����" HIR + zhen +
                                                                                        HIC "����\n��о������桪��>" HBRED + craft + NOR HIC "����\n" NOR,
                                                                                        ob, obb);
                                                                        }
                                                                        set_temp("warquest/attack", 1, ob);

                                                                        ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                                        do_attack(ob, obb, zhen, craft, env, dir, room);
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        } else
                        if( !query_temp("warquest/attack", ob) && 
                              query_temp("warquest/group", ob)>0 && 
                              query_temp("warquest/train", ob) == "infantry" )
                        {
                                obs = all_inventory(env);
                                if (sizeof(obs) > 0)
                                {
                                        for (j = 0; j < sizeof(obs); j++)
                                        {
                                                obb = obs[j];
                                                if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                        continue;

                                                craft = "��ս";
                                                message_vision(HIR "$N" HIR "���������������Ӫ���󣡶��鿪ʼ�ų�����ġ�" HIY + zhen +
                                                        HIR "����\n��һƬ��˸�ĵ����У�$N" HIR "ָ�Ӷ��鷢���˿��µĳ�桪��>" HBYEL +
                                                        craft + NOR HIR "��\n" NOR, ob, obb);
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if (base_name(env) == "/d/city2/myuanmen1" && ! ob->is_busy() &&
                            query_temp("warquest/party", ob) == "song" )
                                ob->command("break");
                }
        }
        return;
}

varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room)
{
        object weapon, bow, blade, weapon2;
        object *ilist;
        int i, power;
        int damage, count = 0;
        string party;
        int points;

        if (! objectp(me))
                return;

        party=query_temp("warquest/party", me);

        // �سǱ������⹥��
        if (craft == "��ʯ")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->stones < 1) ||
                            (party == "meng" && meng_info->stones < 1))
                                break;

                        if (party == "song" && song_info->stones < 2000)
                                damage = song_info->stones;
                        else
                        if (party == "meng" && meng_info->stones < 2000)
                                damage = meng_info->stones;
                        else
                                damage = 2000;

                        if (random(10) > 1)
                        {
                                message_vision(HIC "������ʯ�����ʹӳ�ǽ����������$N"
                                        HIC "һʱ������ʿ�����˲��١�\n" NOR, target);
                                message_vision(HIC "$N" HIC "��ʿ��ߺ���Ž�������ʯ�����ʹӳ�ǽ������ȥ��$n"
                                        HIC "һʱ������ʿ�����˲��١�\n" NOR, me, target);
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "$N" HIC "��ʿ��ߺ���Ž�������ʯ�����ʹӳ�ǽ������ȥ��$n"
                                        HIC "ȴ���з�����û���ܵ���ʧ��\n" NOR, me, target);
                                message_vision(HIC "������ʯ�����ʹӳ�ǽ����������$N"
                                        HIC "ȴ���з�����û���ܵ���ʧ��\n" NOR, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->stones -= damage;
                        else
                                meng_info->stones -= damage;
                }
                return;
        } else
        if (craft == "��̨")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->arrows < 1) ||
                            (party == "meng" && meng_info->arrows < 1))
                                break;

                        if (party == "song" && song_info->arrows < 2000)
                                damage = song_info->arrows;
                        else
                        if (party == "meng" && meng_info->arrows < 2000)
                                damage = meng_info->arrows;
                        else
                                damage = 2000;

                        if (random(10) < 9)
                        {
                                message_vision(HIC "��������Ӽ�¥��ɻȰ���������$N"
                                        HIC "һʱ������ʿ�����˲��١�\n" NOR, target);
                                message_vision(HIC "����һ�������죬�Ӽ�������������$N��ʿ��������ɻȣ�$n"
                                        HIC "һʱ������ʿ��������һƬ��\n" NOR, me, target);

                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "��������Ӽ�¥��ɻȰ���������$N"
                                        HIC "һʱ������ʿ�����˲��١�\n" NOR, target);
                                message_vision(HIC "����һ�������죬�Ӽ�������������$N��ʿ��������ɻȣ�$n"
                                        HIC "ȴ���з�����û���ܵ���ʧ��\n" NOR, me, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->arrows -= damage;
                        else
                                meng_info->arrows -= damage;
                }
                return;
        }

        // ��Ч��
        count=zhen_power(zhen,query_temp("warquest/array", target));
        points = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE);

        count = points*count/100;
        count = to_int(pow(to_float(count/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        if( query_temp("warquest/party", me) == "meng" )
        {
                // �ɹž��ӹ���
                if (! objectp(target) || ! target->is_character())
                {
                        addn_temp("apply/attack", -count, me);
                        addn_temp("apply/damage", -count, me);
                        addn_temp("apply/unarmed_damage", -count, me);
                        return;
                }

                weapon=query_temp("weapon", me);
                if (weapon) weapon->unequip();

                blade = present("wan dao", me);

                ilist = all_inventory(me);
                for (i = 0; i < sizeof(ilist); i++)
                {
                        if( query("is_bow", ilist[i]) )
                        {
                                bow = ilist[i];
                                break;
                        }
                }
                if (room && dir) weapon2 = bow;
                else weapon2 = blade;

                if (objectp(weapon2))
                        // WIELD_CMD->do_wield(me, weapon2);
                        weapon2->wield();

                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target) || ! living(target) ||
                            target->is_net_dead()) break;

                        if (objectp(weapon2) &&
                            query("equipped", weapon2) && query("is_bow", weapon2) )
                        {
                                weapon2->do_shoot(query("id", target),me,weapon2,room,dir,1);
                                addn_temp("warquest/reward", 2, target);
                                continue;
                        }

                        if( query("qi", target)<0 || 
                            environment(me) != environment(target))
                                break;
                        /*
                        message_vision(HIC "$N" HIC "ָ�ӵ��ɹ���������ڣ�" +
                                "��������㳯$n" HIC "�����˳������\n" NOR, me, target);
                        */

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("warquest/reward", 2, target);
                }
                addn_temp("apply/attack", -count, me);
                addn_temp("apply/damage", -count, me);
                addn_temp("apply/unarmed_damage", -count, me);
                return;
        }

        power = 0;
        if (craft == "��ս" || craft == "ͻ��" || craft == "����")
                power = points*10/100;
        else if (craft == "�ܶ�" || craft == "ͻ��" || craft == "����")
                power = points*20/100;
        else if (craft == "��Ѹ" || craft == "ͻ��" || craft == "����")
                power = points*30/100;

        power = to_int(pow(to_float(power/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", power, me);
        addn_temp("apply/damage", power, me);
        addn_temp("apply/unarmed_damage", power, me);

        for(i=0;i<query_temp("warquest/group", me);i++ )
        {
                if (! objectp(target)) break;

                if( query_temp("warquest/train", me) == "cavalry" || 
                    query_temp("warquest/train", me) == "infantry" )
                {
                        /*
                        message_vision(HIR "$N" HIR "ָ�ӵ�����ɱ���׶���" +
                                "��������㳯$n�����˹�������\n" NOR, me, target);
                        */
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        // ɱ������û�н���
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                } else
                if( query_temp("warquest/train", me) == "archer" )
                {
                        bow=query_temp("weapon", me);
                        if( bow && query("is_bow", bow) )
                                bow->do_shoot(query("id", target),me,bow,room,dir,1);
                        // ɱ������û�н���
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                }
        }

        if( query_temp("warquest/train", me) == "cavalry" )
        {
                message_vision(HIW "һ���ɱ����$N" HIW "�������ξ�������" +
                        "һ����ʧ�ˣ�\n" NOR, me);
                me->move(env);
        }

        addn_temp("apply/attack", -power, me);
        addn_temp("apply/damage", -power, me);
        addn_temp("apply/unarmed_damage", -power, me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return;
}

// ���������쳣״��
// ���ң�ʿ������...
void recover_status(object me)
{
        delete_temp("warquest/confusion", me);
        delete_temp("warquest/recover", me);

        return;
}

void attack_over(object me)
{
        string party;

        if (! objectp(me) || ! objectp(song_info->marshal))
                return;

        if( !(party=query_temp("warquest/party", me)) )
                return;

        if (party == "meng")
                message_vision(HIB "$N���о���һ�ӣ��ɹ��������һ��������" +
                        "��ʼ����׼��������һ�ֵĳ������\n" NOR, me);
        else
        if (party == "song")
                message_vision(HIW "$N" HIW "��������һ�ӣ���������һ��������" +
                        "��ʼ����׼��������һ�ֵĹ�������\n" NOR, me);

        delete_temp("warquest/attack", me);

        return;
}

// �����ƶ�����
void auto_move()
{
        mapping move_way;
        object *total, ob, room;
        string file;
        int i, count;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(yd_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                move_way = ward_way;
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }

                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        if( !query_temp("warquest/move_from", ob) )
                                continue;

                        room = environment(ob);

                        // ������������-����
                        if( query("craft/trap", room) && 
                            query("craft/trap", room) != "meng" && random(10) )
                        {
                                // ��ʧһӪ����
                                ob->receive_damage("qi", 2000);
                                ob->receive_wound("qi", 2000);
                                if (! ob->is_busy())
                                        ob->start_busy(2 + random(2));
                                delete("craft/trap", room);
                                message_vision(HIB "$N" HIB "������һ֧�ɹ�ͻ����������壬��ʧ�˲��־��ӣ�.....\n" NOR, ob);
                        }

                        file = base_name(room);
                        if (file == "/d/city2/sying1")
                        {
                                if( !query_temp("warquest/attack", ob) )
                                {
                                        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                                                MAG "�ɹ��������ξ�����������\n" NOR);

                                        fail_kingwar();
                                        return;
                                }
                        } else
                        if (file == "/d/city2/syuanmen1")
                        {
                                if( query("defence", room)>0 && !query_temp("warquest/break", ob) )
                                        message("channel:rumor", MAG "�����߾��顿���Σ�һ��" +
                                                query_temp("title", ob)+MAG"������ɹ�ͻ����Ѿ������ξ���Ӫ��"+
                                                "�ξ��Խ���������Ԯ������\n" NOR, users());

                                if( query("defence", room)>0 )
                                {
                                        message_vision("$N�����г���һ�ӡ������Ͼۣ�ӿ���Ǳߣ�һ�߼�������" +
                                                "��Խ��ǽ��һ�߾���������\n", ob);
                                        set_temp("warquest/break", 1, ob);
                                        ob->command("break");
                                } else
                                if( query_temp("warquest/break", ob)){
                                        message("channel:rumor", MAG "�����߾��顿���Σ��ξ���Ӫ" +
                                                MAG "���ɹ�������ƣ�����Σ��������\n" NOR, users());
                                        delete_temp("warquest/break", ob);
                                }

                        }

                        if (! living(ob) || ob->is_fighting() ||
                            query_temp("warquest/attack", ob) || 
                            query_temp("warquest/break", ob) || 
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

                        message_vision(HIB "$N" HIB "������һ֧�ɹ�ͻ��������س��ξ���Ӫ�ƶ���.....\n" NOR, ob);
                        ob->start_busy(2 + random(2));
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total=filter_array(total,(:objectp($1) && query_temp("warquest/purchase", $1):));
                if (! sizeof(total)) return;

                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        room = environment(ob);
                        file = base_name(room);

                        if( query_temp("warquest/move", ob) == "forward" )
                        {
                                move_way = forward_way;
                                if (file == "/d/xiangyang/eastgate1")
                                {
                                        //if( query_temp("warquest/purchase", ob) != "forage" )
                                        if( 1 )
                                        {
                                                if (! ob->is_busy())
                                                ob->start_busy(8 + random(8));
                                                switch(query_temp("warquest/purchase", ob) )
                                                {
                                                case "weapon" :
                                                        message_vision(HIY "$N" HIY "����Ĵ�������������ǣ�����¿�ʼ���ñ����Ϳ��ף�\n" +
                                                                "$N" HIY "��ǰ����������������������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                case "horse"  :
                                                        message_vision(HIY "$N" HIY "����Ĵ�������������ǣ�����¿�ʼ����ս��\n" +
                                                                "$N" HIY "��ǰ������ս��ȫ�����ϣ������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                case "stone"  :
                                                        message_vision(HIY "$N" HIY "����Ĵ�������������ǣ�����¿�ʼ����ʯͷ����ľ��\n" +
                                                                "$N" HIY "��ǰ������ʯľ�������������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                case "arrow"  :
                                                        message_vision(HIY "$N" HIY "����Ĵ�������������ǣ�����¿�ʼ���������\n" +
                                                                "$N" HIY "��ǰ����������������������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                case "enlist" :
                                                        message_vision(HIY "$N" HIY "����Ĵ�������������ǣ�����¿�ʼ��ļ�±���\n" +
                                                                "$N" HIY "��������ļ���±��������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                case "forage" :
                                                        message_vision(HIY "$N" HIY "����Ľ���������ڵ����������ǣ�" +
                                                                "$N" HIY "�������������������̿�ʼ���о��ı���....\n" NOR, ob);
                                                        break;
                                                default :
                                                        break;
                                                }
                                                set_temp("warquest/move", "backward", ob);
                                                move_way = backward_way;
                                        }
                                } else
                                if (file == "/d/city2/chengmen")
                                {
                                        if (! ob->is_busy())
                                        ob->start_busy(5 + random(5));
                                        message_vision(HIY "$N" HIY "����Ľ���������ڵ����˾�ʦ������" +
                                                "$N" HIY "�������������������̿�ʼ���о��ı���....\n" NOR, ob);
                                        set_temp("warquest/move", "backward", ob);
                                        move_way = backward_way;
                                }
                        } else
                        if( query_temp("warquest/move", ob) == "backward"){
                                move_way = backward_way;
                                if (file == "/d/city2/sying1")
                                {
                                        switch(query_temp("warquest/purchase", ob) )
                                        {
                                                case "weapon" :
                                                        message_vision(HIY "$N" HIY "����Ĺ��ñ��״�����ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "�ı��׼�ʱ֧Ԯ�˴���ľ���....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->weapons += count;
                                                        tell_object(song_info->marshal, HIY "���ñ��׵ľ����ˣ���ľ����������ˣ�\n" NOR);
                                                        break;
                                                case "horse"  :
                                                        message_vision(HIY "$N" HIY "����Ĺ���ս�������ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "�������ʱ֧Ԯ�˴���ľ���....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 40 + random(500);
                                                        song_info->horses += count;
                                                        tell_object(song_info->marshal, HIY "����ս��ľ����ˣ���ľ����������ˣ�\n" NOR);
                                                        break;
                                                case "stone"  :
                                                        message_vision(HIY "$N" HIY "����Ĺ���ʯľ������ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "�������ʱ֧Ԯ�˴���ľ���....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->stones += count;
                                                        tell_object(song_info->marshal, HIY "����ʯľ�ľ����ˣ���ľ����������ˣ�\n" NOR);
                                                        break;
                                                case "arrow"  :
                                                        message_vision(HIY "$N" HIY "����Ĺ������������ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "�������ʱ֧Ԯ�˴���ľ���....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->arrows += count;
                                                        tell_object(song_info->marshal, HIY "��������ľ����ˣ���ľ����������ˣ�\n" NOR);
                                                        break;
                                                case "enlist" :
                                                        message_vision(HIY "$N" HIY "�������ļ�±�������ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "���±���ʱ֧Ԯ�˴���ı�Դ....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->soilders += count;
                                                        tell_object(song_info->marshal, HIY "��ļ�±��ľ����ˣ�����±��������ˣ�\n" NOR);
                                                        break;
                                                case "forage" :
                                                        message_vision(HIY "$N" HIY "����Ľ���������ڵ�����������Ӫ��\n" +
                                                                "$N" HIY "�����ݼ�ʱ֧Ԯ�˴���Ĳ���....\n" NOR, ob);

                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 5 + random(10000);
                                                        song_info->forages += count;
                                                        tell_object(song_info->marshal, HIY "Ѻ�����ݵľ����ˣ���Ĳ����������ˣ�\n" NOR);
                                                        break;
                                                default :
                                                        break;
                                        }
                                        delete_temp("warquest/purchase", ob);
                                        delete_temp("warquest/move", ob);
                                        delete_temp("warquest/move_from", ob);
                                        delete_temp("warquest/quest", ob);

                                        if (! ob->is_busy())
                                                ob->start_busy(5 + random(5));

                                        continue;
                                }
                        }
                        if (! living(ob) || ob->is_fighting() ||
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

                        switch(query_temp("warquest/purchase", ob) )
                        {
                        case "weapon" :
                        case "horse"  :
                        case "stone"  :
                        case "arrow"  :
                                message_vision(YEL "$N�����Ź��þ��������������ҹ���н���.....\n", ob);
                                break;
                        case "enlist" :
                                message_vision(YEL "$N��������ļ�±��Ĵ����������ҹ���н���.....\n", ob);
                                break;
                        case "forage" :
                                message_vision(YEL "$N������Ѻ�����ݴ����������ҹ���н���.....\n", ob);
                                break;
                        default :
                                break;
                        }
                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                }
        }
        return;
}

// ���������������
void auto_cost()
{
        int i, count = 0;
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xh_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                if (meng_info->moneys > 0 || meng_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                       }

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (meng_info->moneys > 0)
                                meng_info->moneys -= count * 200;
                        if (meng_info->moneys < 0)
                                meng_info->moneys = 0;
                        if (meng_info->forages > 0)
                                meng_info->forages -= count * 200;
                        if (meng_info->forages < 0)
                                meng_info->forages = 0;
                }
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/group", $1):));
        if (arrayp(total) && sizeof(total))
        {
                if (song_info->moneys > 0 || song_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }

                        if( query_temp("warquest/group", total[i])<1 )
                                delete("warquest/group", total[i]);

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (song_info->moneys > 0)
                                song_info->moneys -= count * 200;
                        if (song_info->moneys < 0)
                                song_info->moneys = 0;
                        if (song_info->forages > 0)
                                song_info->forages -= count * 200;
                        if (song_info->forages < 0)
                                song_info->forages = 0;
                }
        }

        if (song_info->moneys < 1 && ! have1)
        {
                message("channel:rumor",
                        MAG "�����߾��顿���Σ�������ȱ���ӳ����ӱ���ʿ���½�����\n" NOR, users());
                have1 = 1;
        }
        if (song_info->forages < 1 && ! have2)
        {
                message("channel:rumor",
                        MAG "�����߾��顿���Σ����ݶ�ȱ���ӳ����ӱ���ʿ���½�����\n" NOR, users());
                have2 = 1;
        }

        return;
}

void auto_train()
{
        object *total;
        object ob, room;
        string type;
        int i;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xl_event_id);
                return;
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/train_begin", $1):));

        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! living(total[i])) continue;

                        ob = total[i];
                        room = environment(ob);

                        type=query_temp("warquest/train", ob);
                        if (! type)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "Ԫ˧��û�з��ɸ���ѵ����������\n");
                                continue;
                        }

                        if( !room || !query("train", room )
                            || query("train", room) != type )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "���㵽ָ���ı�Ӫ����ѵ���±���\n");
                                continue;
                        }

                        if (song_info->forages < 12000)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"�������ݲ��㣬�����±���ѵ��������ֹ��\n");

                                tell_object(song_info->marshal,
                                        HIY "�������ݲ��㣬��Ķ��鱻����ֹ��ѵ����\n" NOR);
                                continue;
                        }

                        if (song_info->soilders < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"���ڱ�Դ���㣬�������±���ѵ����\n");
                                tell_object(song_info->marshal,
                                        HIY "���ڱ�Դ���㣬��Ķ��鱻����ֹ��ѵ���±���\n" NOR);
                                continue;
                        }

                        if (song_info->weapons < 400)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"���ڱ��ײ��㣬�����±���ѵ��������ֹ��\n");
                                tell_object(song_info->marshal,
                                        HIY "���ڱ������㣬��Ķ��鱻����ֹ��ѵ���±���\n" NOR);
                                continue;
                        }

                        if ((type == "archer" || type == "cavalry") &&
                            song_info->horses < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"����ս���㣬�����±���ѵ��������ֹ��\n");
                                tell_object(song_info->marshal,
                                        HIY "����ս���㣬��Ķ��鱻����ֹ��ѵ���±���\n" NOR);
                                continue;
                        }

                        if( query_temp("warquest/group", ob)>query("degree_jungong", ob) )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"��������������㣬ѵ�����˸��Ӵ���Ķ����ˣ�\n");

                                tell_object(song_info->marshal,
                                        HIY "����ѵ����һ֧�ľ��񲿶��ˣ�\n" NOR);
                                continue;
                        }

                        if( random(query("degree_jungong", ob))>1 )
                        {
                                message_vision(HIW "$N����������һ�ӣ��±���ʼ���ᣬ" +
                                        "��ʼ�����Ų�ͬ�����Σ�����ɢ����\n��ʱ��Ȼ���򣬷�" +
                                        "ʱ�Ӷ����ң�����$N���������ñ�֮������������\n" NOR, ob);

                                addn("eff_qi", 200, ob);
                                song_info->soilders -= 200;
                                song_info->weapons -= 400;
                                if (type == "archer" || type == "cavalry")
                                        song_info->horses -= 200;
                        } else
                                message_vision(HIY "$N����������һ�ӣ������±������Һ��ģ�" +
                                        "��������$N��ָ�ӵ�ǲ��\n$Nֱ���ô����ӵ��ۣ�����\n" NOR, ob);
                        // ���ݶ�������
                        song_info->forages -= 20;
                }
        }
        return;
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        tell_object(me, HIR "\n����Ż��ң��ӻ�Ԫ˧��Ӫ���ּ��пʣ��ѵ������״̬��\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = MAG + me->name(1) + MAG "�ľ��ӱ�" + ob->name(1) + MAG "�ľ���ɱ��ȫ����û��һ���ӻش�Ӫ��" NOR;
        } else
                msg = MAG + me->name(1) + MAG "�ľ���ȫ����û��һ���ӻ��ξ���Ӫ��" NOR;

        message("channel:rumor", MAG "�����߾��顿���Σ�" + msg + "\n" NOR, users());

        me->move("/d/city2/sying1");
        message("vision", "һ����Ӱٿ�Ĵ��˹������漴���ǡ�ž����"
                "һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������"
                "������ӡ�\n", environment(me), ({ me }));
        tell_object(me, "�������У�����ñ���������������"
                    "���ص�ˤ���˵��ϡ�\n");
        if (! living(me))
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{
        message("channel:rumor", MAG "�����߾��顿���Σ�" + MAG + me->name(1) +
                            "��ս�����������ӡ�\n", users());
        restore_status(me);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        tell_object(me, "��һ�����ӳ���ս����������������㳡��\n");

        // continue run quit function
        me->move("/d/city/guangchang");
        message("vision", "ֻ��" + me->name() + "������ŵ����˹�����\n",
                environment(me), ({ me }));

        ip_numbers -= ({ query_ip_number(me) });
        return 1;
}

int general_die(object me)
{
        delete_temp("warquest", me);
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG"���ξ�����"HIR+query("name", me)+"("+query("id", me)+")"NOR+
                MAG "ս��ɳ��������ѳ������\n" NOR);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        ip_numbers -= ({ query_ip_number(me) });
        return 0;
}

void fail_kingwar()
{
        object *total;
        int i;

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "�ξ����ɹž��ӻ����ˣ������ɳ�ʹ�߸����ͣ���\n" NOR);

        if (objectp(song_info->marshal))
        {
                restore_status(song_info->marshal);
                song_info->marshal->move("/d/city/guangchang"); 
                message("vision", "ֻ��" + song_info->marshal->name() + "���˹�����\n", 
                        environment(song_info->marshal), ({ song_info->marshal })); 
                song_info->marshal->apply_condition("junquest_fail", 50);
        }

        total = song_info->generals;
        total = filter_array(total, (: objectp($1) && userp($1) :));
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang"); 
                        message("vision", "ֻ��" + total[i]->name() + "���˹�����\n", 
                                environment(total[i]), ({ total[i] })); 
                }
        }
        restore_kingwar();
        return;
}

void win_kingwar()
{
        object *total;
        int i;

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "�ξ�Ӣ�µĻ������ɹž��ӣ���ʹ�ɹž����������ͣ�\n" NOR);
        give_bouns();
        restore_kingwar();
        return;
}

void finish_kingwar()
{
        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(wc_event_id);
                return;
        }

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG + "�ξ��������ĵֿ���ʹ���ɹž��Ӿù����£����ڳ����ˣ�\n" NOR);
        give_bouns();
        restore_kingwar();
        return;
}

void remove_enemy()
{
        object *enemys;
        int j;

        if (arrayp(enemys = children("/d/city2/meng/kehan")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                        }
                        tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                  "ͻȻ������Ц������������Ӳ����ˣ�\n");
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/d/city2/meng/mengj")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                          "ͻȻ������Ц������Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                          "ͻȻ��ɫ��ϲ������ææ��������Ӳ����ˡ�\n");
                        }
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/d/city2/meng/mengb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                        "ͻȻ������Ц������Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "ͻȻ��ɫ��ϲ������ææ��������Ӳ����ˡ�\n");
                        }
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/song/songb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "ͻȻ��ɫһ�䣬Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "��ֵһ�㣬ͻȻ��ɫ��䣬����ææ��������Ӳ����ˡ�\n");
                        }
                        song_info->generals -= ({ enemys[j] });
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/npc/jianjun")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/meng/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/song/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }
        get_object("/d/city2/majiu")->reset();
        return;
}

// send message out
void message_ward(string msg)
{
        // CHANNEL_D->do_channel(this_object(), "rumor", msg);
        message("channel:rumor", MAG "������ʷ�ǡ�" + msg + NOR, users());
}

// remove overide function
void restore_status(object me)
{
        object bingfu, lingjian, zhanma, kaijia;

        if (objectp(bingfu = present("bing fu", me)))
                destruct(bingfu);

        if (objectp(lingjian = present("ling jian", me)))
                destruct(lingjian);

        if (objectp(zhanma = present("zhan ma", me)))
                destruct(zhanma);

        if (objectp(zhanma = present("shizi ma", me)))
                destruct(zhanma);

        if (objectp(kaijia = present("kai jia", me)))
                destruct(kaijia);

        me->delete_override("quit");
        me->delete_override("die");
        delete_temp("warquest", me);
        delete_temp("title", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);
        // me->clear_condition();

        return;
}

void restore_kingwar()
{
        // set_heart_beat(0);

        if (mg_event_id)
                SCHEDULE_D->delete_event(mg_event_id);
        if (sc_event_id)
                SCHEDULE_D->delete_event(sc_event_id);
        if (xl_event_id)
                SCHEDULE_D->delete_event(xl_event_id);
        if (yd_event_id)
                SCHEDULE_D->delete_event(yd_event_id);
        if (xh_event_id)
                SCHEDULE_D->delete_event(xh_event_id);
        if (ap_event_id)
                SCHEDULE_D->delete_event(ap_event_id);
        if (wc_event_id)
                SCHEDULE_D->delete_event(wc_event_id);
        if (xt_event_id)
                SCHEDULE_D->delete_event(xt_event_id);

        meng_info->economy = 0;
        meng_info->moneys = 0;
        meng_info->forages = 0;
        meng_info->stones = 0;
        meng_info->arrows = 0;
        meng_info->horses = 0;
        meng_info->weapons = 0;
        meng_info->soilders = 0;
        meng_info->marshal = 0;
        meng_info->generals = 0;
        meng_info->count = 0;
        song_info->economy = 0;
        song_info->moneys = 0;
        song_info->forages = 0;
        song_info->stones = 0;
        song_info->arrows = 0;
        song_info->horses = 0;
        song_info->weapons = 0;
        song_info->soilders = 0;
        song_info->marshal = 0;
        song_info->generals = 0;
        song_info->count = 0;
        have1 = 0;
        have2 = 0;
        start_time = 0;
        valid_check = 0;
        return;
}

void give_bouns()
{
        int reward, rew, pot, exp, mar, jungong, i, j;
        string prompt;
        object me;
        object *total, ob;
        int war_times;

        total = song_info->generals;
        if (! objectp(song_info->marshal))
        {
                if (arrayp(total) && sizeof(total) > 0)
                {
                        for (i = 0; i < sizeof(total); i++)
                        {
                                if (! objectp(total[i]))
                                        continue;
                                restore_status(total[i]);
                        }
                }
                return;
        }

        //rew = song_info->marshal->query("jungong");
        reward = query_temp("warquest/reward", song_info->marshal);

        message("channel:rumor", MAG "�����ξ��ǡ�" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());

        reward += 500;
        if (reward > 3000) reward = 3000;
        //if (rew > 200000) rew = 200000;
        // exp = (reward / 2 + random(reward / 2)) * (song_info->marshal->query("degree_jungong") + 1) * 10;
        exp = reward * (query("degree_jungong", song_info->marshal) + 1) * 5;
        war_times = "/adm/daemons/actiond"->query_action("war_reward");
        if (war_times) exp *= war_times;
        pot = exp / 2;
        mar = pot / 2;

        jungong = exp / 1000;
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(song_info->marshal))
                jungong *= 2;
#endif

        addn("jungong", jungong, song_info->marshal);

        prompt = "�����й�";
        GIFT_D->delay_war_bonus(song_info->marshal,
                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 1000 ]));

/*
        if (random(2)) ob = new("/clone/fam/gift/int3");
        else ob = new("/clone/fam/gift/con3");
        ob->move(song_info->marshal, 1);
        if (random(2)) ob = new("/clone/fam/gift/str3");
        else ob = new("/clone/fam/gift/dex3");
        ob->move(song_info->marshal, 1);
        for (j = 0; j < 5; j++)
        {
                ob = new("/clone/goods/sun");
                ob->move(song_info->marshal, 1);
                ob = new("/clone/goods/moon");
                ob->move(song_info->marshal, 1);
        }

        ob = new("/clone/gift/puti-zi");
        ob->set_amount(2);
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/tianxiang");
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/jiuzhuan");
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/xuanhuang");
        ob->move(song_info->marshal, 1);
*/

        message("channel:rumor", HIY "�����ξ��ǡ�����������ʵ�گԻ��\n" +
               "            " + song_info->marshal->name(1) + HIY "�����й����ͻƽ�ǧ����������ƥ����Ůʮ����" +
                "�Ǿ��� " HIR + chinese_number(jungong) +
                HIY " �ߣ��մˣ�\n\n" NOR, users());

        tell_object(song_info->marshal, HIW "�����й��������� " + HIR + chinese_number(jungong) +
                          HIW " �߾�������\n" NOR);

        restore_status(song_info->marshal);
        song_info->marshal->move("/d/city/guangchang");
        message("vision", "ֻ��" + song_info->marshal->name() + "���˹�����\n",
                environment(song_info->marshal), ({ song_info->marshal }));

        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        if (total[i] == song_info->marshal)
                                continue;

                        tell_object(total[i], HIR "�ɹž��ӳ����ˣ�׼����ʦ�س��ɣ�\n" NOR);

                        //rew = total[i]->query("jungong");
                        reward=query_temp("warquest/reward", total[i]);
                        reward += 500;
                        if (reward < 2)
                        {
                                restore_status(total[i]);
                                continue;
                        }
                        if (reward > 3000) reward = 3000;
                        //if (rew > 200000) rew = 200000;
                        // exp = (reward / 2 + random(reward / 2)) * (total[i]->query("degree_jungong") + 1) * 10;
                        exp = reward*(query("degree_jungong", total[i])+1)*5;
                        if (war_times) exp *= war_times;
                        pot = exp / 2;
                        mar = pot / 2;
                        jungong = exp / 1000;
#ifdef DB_SAVE
                        if (MEMBER_D->is_double_reward(total[i]))
                                jungong *= 2;
#endif

                        addn("jungong", jungong, total[i]);

                        GIFT_D->delay_war_bonus(total[i],
                                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 100 ]));

/*
                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        for (j = 0; j < 3; j++)
                        {
                                if( random(2) )
                                        ob = new("/clone/goods/sun");
                                else
                                        ob = new("/clone/goods/moon");
                                ob->move(total[i], 1);
                        }

                       if( reward >= 2000 && time()-query_temp("warquest/time", total[i]) >= 600 )
                        {
                                ob = new("/clone/gift/puti-zi");
                                ob->set_amount(2);
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/tianxiang");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/jiuzhuan");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/xuanhuang");
                                ob->move(total[i], 1);
                        }
*/

                        tell_object(total[i], HIW "�����й��������� " + HIR + chinese_number(jungong) +
                                              HIW " �߾�������\n" NOR);

                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang");
                        message("vision", "ֻ��" + total[i]->name() + "���˹�����\n",
                                environment(total[i]), ({ total[i] }));
                }
        }
        return;
}

int continue_kingwar(string arg)
{
        object general;
        object room;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(mg_event_id);
                SCHEDULE_D->delete_event(sc_event_id);
                return 0;
        }

        if (! arg) return 0;
        if (arg == "meng")
        {
                room = get_object("/d/city2/mying1");
                if (meng_info->forages > 240000 && meng_info->moneys > 240000 &&
                    meng_info->weapons > 48000 && meng_info->horses > 24000 &&
                    meng_info->soilders > 24000)
                {
                        for (int i = 0; i < 4; i++)
                        {
                                general = new("/d/city2/meng/mengb");
                                general->move(room);
                                init_general(general);
                                set_temp("warquest/quest", "������Ӫ�����ִ���", general);
                        }
                }
        } else
        if (arg == "song")
        {
                room = get_object("/d/city2/sying1");
                if (song_info->forages > 100000 && song_info->moneys > 100000 &&
                    song_info->soilders > 24000)
                {
                        general = new("/d/city2/song/songb");
                        general->move(room);
                        init_general(general);
                        tell_object(song_info->marshal,
                                HIR "��͢��ǲ֧Ԯǰ�ߵ�һ���ξ����쵽�ˣ��Ͽ���ǲ������ɣ�����\n" NOR);
                }
        }

        return 1;
}

string do_assign(object me, string arg)
{
        object *inv;
        object ob;
        object ling, horse;
        string who, what;
        int i, count;

        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return "���� paiqian sb to do sth. ���������\n";

        if (who != "all" && ! objectp(ob = present(who, environment(me))))
                return "����û������Ե��ȵ��������죡\n";

        if (who == "all" && (what != "battle" || what != "ST-chuzheng"))
                return "���� paiqian sb to do sth. ���������\n";

        if( query_temp("warquest/party", ob) != "song" )
                return "�Է������ξ�����ι�����ȣ���\n";

        /*
        if( query("degree_jungong", ob)<1 )
                return "�Է���ͳ˧����̫���ˣ��ѿ����ã�\n";
        */

        if (ob == me)
                return "�Լ������Լ����㲻���۰��㣿��\n";

        if( query("id", ob) == "jianjun" )
                return "�㲻����������μ��ȥ��������飡\n";
        
        if( query("eff_qi", ob) < query("max_qi", ob) )
                return "�㻹�ǵȶԷ�����������ǲ����ɡ�\n";

        switch(what)
        {
        case "battle":
        case "chuzheng":
                message_vision(HIR "$N��һ��˼����������ҵ����������˧����ӭս�ɹŴ����\n"
                               "��λ�����뼴�̵���������ͬ��˧����������Υ������۴���\n" NOR, me);

                inv = all_inventory(environment(me));
                for (i=sizeof(inv)-1; i>=0; i--)
                if( query_temp("warquest/group", inv[i])>0 )
                {
                        if( query_temp("warquest/purchase", inv[i]) || 
                            query_temp("warquest/guard", inv[i]) || 
                            (userp(inv[i]) && inv[i] != me))
                                continue;

                        inv[i]->set_leader(me);
                        set_temp("warquest/battle", 1, inv[i]);
                        set_temp("warquest/quest", "���ӳ�����ӭս�ɾ�", inv[i]);
                }
                return "�ڽ�����Ӧ����ĩ����������\n";
                break;
        case "recon": // reconnaissance
        case "zhencha" :
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�ɹŴ������������\n�������ǰ���ɹž�Ӫ�������Ա㱾˧" +
                               "֪��֪�ˣ��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"�������Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/recon", 1, ob);
                set_temp("warquest/quest", "�����ɾ���������", ob);
                // ob->command("recon");
                break;
        case "enlist":
        case "zhaomu-xinbing" :
                /*
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "���������Ѿ����࣬����������֧����ļ�±��Ŀ�֧��\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������б�Ա�ѷ���\n��������ʲ�����ȥ����������ļ�±�" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "enlist", ob);
                set_temp("warquest/quest", "��ļ�±��������Դ", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-weapon":
        case "gouzhi-bingjia" :
                /*
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "���������Ѿ����࣬����������֧�����ñ��׵Ŀ�֧��\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������б����Ϳ����ѷ���\n��������ʲ�����ȥ�������ڲɹ������Ϳ���" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "weapon", ob);
                set_temp("warquest/quest", "���ñ��ף��������", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-arrow":
        case "gouzhi-yujian" :
                /*
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "���������Ѿ����࣬����������֧����������Ŀ�֧��\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "������Ӫ��¥����ѷ���\n��������ʲ�����ȥ�������ڲɹ����" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "arrow", ob);
                set_temp("warquest/quest", "����������������", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-horse":
        case "gouzhi-zhanma" :
                /*
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "���������Ѿ����࣬����������֧������ս��Ŀ�֧��\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "��������ս���ѷ���\n��������ʲ�����ȥ�������ڲɹ�ս��" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "horse", ob);
                set_temp("warquest/quest", "����ս���������", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-stone":
        case "gouzhi-shimu" :
                /*
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "���������Ѿ����࣬����������֧������ʯľ�Ŀ�֧��\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������й�ʯ����ľ�ѷ���\n��������ʲ�����ȥ�������ڲɹ�ʯͷ��ľ��" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "stone", ob);
                set_temp("warquest/quest", "����ʯľ���������", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "guard-xiangyang":
        case "shouwei-xiangyang" :
                if (! userp(ob))
                        return "����������,��ֻ�ܵ������ȥ��ɣ�\n";
                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�����ɹ������ɧ���Ҵ��������ǣ�\n��������ʲ�����ȥ����פ�سǳ�" +
                               "���������󣬾����۴���\n" NOR, me, ob);
                set_temp("title", HIY"���κ��Ӫͳ��"NOR, ob);
                /*
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                */
                set_temp("warquest/guard", 1, ob);
                set_temp("warquest/quest", "�����������ȹ̺�", ob);
                // ob->command("guard");
                ob->move("/d/wuguan/guofu_dating");
                break;
        case "yayun-liangcao":
        case "escort-forage" :
                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������������ѷ���\n��������ʲ����ڰ����ڽ���ʦ��Ӧ֮����Ѻ��" +
                               "�����У��������󣬾����۴���\n" NOR, me, ob);

                set_temp("title", HIY"���ξ���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "forage", ob);
                set_temp("warquest/quest", "Ѻ�����ݣ��������", ob);
                ob->command("stock");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "cavalry" )
                        return "�Է��Ѿ�������ְ�ˣ�������ѡ�ɽ���ɣ�\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������м�����ս֮ʦ��\n����ӽ�ѵ��һ֧����������Ա���ʱ֮�裬" +
                               "��������\n" NOR, me, ob);

                set_temp("title", HIR"���γ���Ӫͳ��"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        UNRIDE_CMD->main(ob);
                        horse = new("/d/city2/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "cavalry", ob);
                set_temp("warquest/quest", "ѵ���������ս׼��", ob);
                ob->command("drill");
                break;

        case "train-infantry":
        case "xunlian-bubing":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "infantry" )
                        return "�Է��Ѿ�������ְ�ˣ�������ѡ�ɽ���ɣ�\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������м�����ս֮ʦ��\n����ӽ�ѵ��һ֧���񲽱����Ա���ʱ֮�裬" +
                               "��������\n" NOR, me, ob);
                set_temp("title", HIW"���β���Ӫͳ��"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "infantry", ob);
                set_temp("warquest/quest", "ѵ����������ս׼��", ob);
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "archer" )
                        return "�Է��Ѿ�������ְ�ˣ�������ѡ�ɽ���ɣ�\n";

                message_vision(HIR "$N��һ��˼���Ӱ�ǰ���һö���������$n���" +
                               "�������м�����ս֮ʦ��\n����ӽ�ѵ��һ֧���񹭼��֣��Ա���ʱ֮�裬" +
                               "��������\n" NOR, me, ob);
                set_temp("title", HIB"��������Ӫͳ��"NOR, ob);

                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }

                set_temp("warquest/train", "archer", ob);
                set_temp("warquest/quest", "ѵ����������ս׼��", ob);
                ob->command("drill");
                break;

        default:
                return "��Ϊһ��֮˧���벻Ҫ������ľ�Ȩ��\n";
        }

        return query("name", ob) + "����Ӧ����ĩ����������\n";
}
