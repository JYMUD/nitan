
inherit ITEM;

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"

mapping trans = ([
"beijing"   : "/d/beijing/majiu",
"luoyang"   : "/d/luoyang/majiu",
"yangzhou"  : "/d/city/majiu",
"dali"      : "/d/dali/majiu", 
"foshan"    : "/d/foshan/majiu", 
"fuzhou"    : "/d/fuzhou/majiu", 
"guanwai"   : "/d/guanwai/majiu", 
"hangzhou"  : "/d/hangzhou/majiu", 
"lanzhou"   : "/d/lanzhou/majiu", 
"lingzhou"  : "/d/lingzhou/majiu", 
"yongdeng"  : "/d/huanghe/majiu", 
"suzhou"    : "/d/suzhou/majiu",
"xiangyang" : "/d/xiangyang/majiu", 
"yili"      : "/d/xingxiu/majiu", 
"chengdu"   : "/d/city3/majiu", 
"emei"      : "/d/emei/majiu1", 
"emei2"     : "/d/emei/majiu2", 
"quanzhou"  : "/d/quanzhou/majiu1", 
"jiaxing"   : "/d/quanzhou/majiu2", 
"jingzhou"  : "/d/jingzhou/majiu", 
"nanyang"   : "/d/shaolin/majiu1", 
"changan"   : "/d/changan/majiu", 
"wugong"    : "/d/quanzhen/majiu", 
"hengyang"  : "/d/henshan/majiu", 
"kaifeng"   : "/d/kaifeng/majiu", 
"kunming"   : "/d/kunming/majiu", 
"zhongzhou" : "/d/zhongzhou/majiu",
]);

mapping show_trans = ([
"beijing"   : "����",
"luoyang"   : "����",
"yangzhou"  : "����",
"dali"      : "����", 
"foshan"    : "��ɽ", 
"fuzhou"    : "����", 
"guanwai"   : "����", 
"hangzhou"  : "����", 
"lanzhou"   : "����", 
"lingzhou"  : "����", 
"yongdeng"  : "����", 
"suzhou"    : "����",
"xiangyang" : "����", 
"yili"      : "����", 
"chengdu"   : "�ɶ�", 
"emei"      : "����ɽ", 
"emei2"     : "���Ұ�ɽ", 
"quanzhou"  : "Ȫ��", 
"jiaxing"   : "����", 
"jingzhou"  : "����", 
"nanyang"   : "����", 
"changan"   : "����", 
"wugong"    : "�书��", 
"hengyang"  : "����", 
"kaifeng"   : "����", 
"kunming"   : "����", 
"zhongzhou" : "����",
]);

string get_trans_path(string s)
{
        return trans[s];
}

string get_trans_name(string s)
{
        return show_trans[s];
}

int is_horse()
{
        return 1;
}

void setup()
{
        set("ridable", 1);
        set("no_give", 1);
        set("value", 1);
        set("unit", "ƥ");
        set("base_unit", "ƥ");
        set_weight(1);

        set_heart_beat(2);
        /*
        remove_call_out("start_heart_beat");
        call_out("start_heart_beat", 2);
        */
        ::setup();
}

int show_trans(object me)
{
        int i;
        string* places;
        mapping self_flag;

        write(HIY "������������µط���\n" NOR);

        places = keys(show_trans); 
        for (i = 0; i < sizeof(places); i ++)
                write(sprintf("%-20s%-20s\n", places[i], show_trans[places[i]]));

        // �Լ���¼�ĵص�
        self_flag = me->query("horse/flags");

        if (mapp(self_flag) && MEMBER_D->is_valib_member(me->query("id")))
        {
                if (sizeof(self_flag))
                {
                        places = ({});
                        places = keys(self_flag);
                        for (i = 0; i < sizeof(places); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, places[i], "�û���¼�ص�"));
                }
        }
        else if(mapp(self_flag))
        {
                if (sizeof(self_flag))
                {
                        places = ({});
                        places = keys(self_flag);
                        for (i = 0; i < sizeof(places); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, places[i], "�û���¼�ص�"));
                }                
        }

        write(HIY "\n��ʹ�� rideto <����> ����ָ���ط���\n" NOR);

        return 1;

}

// ����ָ���ص�
int move_to(object me, string place)
{
        object running, horse, follower;
        string trans_path;
        int trans_times, sk_riding, horse_level, horse_tili, cost_tili, level;
        string temp,temp2;
        object trans_target, me_env;
        

        // ����Ƿ�����
        if (! objectp(horse = me->query_temp("is_riding")))
        {
                write("�㲢û��������\n" );
                return 1;
        }
        if (horse->query_temp("running"))
        {
                write(this_object()->name() + NOR "���ڱ����أ�\n" NOR);
                return 1;
        }
        if (me->query_temp("running"))
        {
                write("�����ڱ������ء�\n");
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                write("����æ�أ�\n");
                return 1;
        }
        sk_riding = me->query_skill("riding", 1);
        if (sk_riding < 30)
        {
                write("�������������޷�����ָ���ص㡣\n");
                return 1;
        }

        // ����Ƿ��иõط���ȥ
        if (! stringp(trans_path = get_trans_path(place)))
        {
                        if (stringp(trans_path = me->query("horse/flags/" + place)))
                        {
                                if (! find_object(trans_path) && ! load_object(trans_path))
                                {
                                        write("���޷�����ﵽ����ط���\n");
                                        return 1;
                                }
                                
                        }
                        if (! stringp(trans_path = me->query("horse/flags/" + place)))
                        {
                                write("���޷�����ﵽ����ط���\n");
                                return 1;
                        }                
                        else
                        {
                                if (! MEMBER_D->is_valib_member(me->query("id")) && ! me->query("horse/stone"))
                                {
                                        write("���޷�����ﵽ����ط���\n");
                                        return 1;
                                }
                        }                
        }

        // ĳЩ�ط��޷�������
        trans_target = find_object(trans_path);
        if (! objectp(trans_target))trans_target = load_object(trans_path);

        if (! objectp(trans_target))
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }
        
        if (trans_target->query("no_flyto"))
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }

        // �����Ҳ�޷�����
        if (sscanf(trans_path, "/kungfu/class/sky%s", temp) == 1)
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }

        if (sscanf(trans_path, "/d/newbie/%s", temp) == 1)
        {
                write("���޷�����ﵽ����ط���\n");
                log_file("horse", me->query("id") + "��" + ctime(time()) + " ��ͼ���ü�¼��ص����ִ塣\n");
                return 1;
        }        
        // �������ϲ��ܵ���(��Ӱ�����)
        me_env = environment(me);
        
        if (me_env->query("no_rideto"))
        {
                write("�˴���������\n");
                return 1;                
        }
        if (sscanf(base_name(me_env), "/d/shenlong/%s", temp) == 1 && this_object()->query("id") != "chaoying")
        {
                write("�˴��޷�����\n");
                return 1;
        }
        if (sscanf(trans_path, "/d/shenlong/%s", temp) == 1 && this_object()->query("id") != "chaoying")
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }
        
        if (trans_path == "/d/shenlong/shejingdong")
        {
                write("��������޷���Ӧ�߾����ڵ�������޷�����ﵽ����ط���\n");
                return 1;
        }
        
        // dream_boat���޷�����
        if (sscanf(base_name(me_env), "/clone/misc/dream_%s", temp) == 1)
        {
                write("�˴��޷�����\n");
                return 1;
        }
        
        // ��ҷ����޷�����Լ��ķ������
        if (sscanf(trans_path, "/data/room/%s/%s", temp, temp2) == 2)
        {
                // �Լ�������Խ���
                if (me->query("id") != temp)
                {
                        write("���޷��������˽��סլ��\n");
                        return 1;
                }
        }

        if (sscanf(trans_path, "/clone/misc/dream_%s", temp) == 1)
        {
                write("���޷�����ﵽ����ط���\n");
                return 1;
        }
        if (sscanf(trans_path, "/d/xiangyang/%s", temp) == 1 && XYWAR_D->now_status() == 2)
        {
                write("����������ȫ��䱸���㻹�������Ƚϰ�ȫ��\n");
                return 1;
        }

        if (sscanf(base_name(environment(me)),"/d/xiangyang/%s", temp) == 1  && XYWAR_D->now_status() == 2)
        {
                write("����������ȫ��䱸���㻹�������Ƚϰ�ȫ��\n");
                return 1;
        }

        // ������ĺû��������ߵ��������жϴﵽĿ�ĵ�ʱ��
        level = horse->query("level");
        if (sk_riding >= 300)sk_riding = 300;
        trans_times = 2 + random(1 + 300 / sk_riding) + random(22 - level*4);

        if (trans_times <= 0)
                log_file("horse_time", trans_times + "\n");

        // �ж�����ָ���ص��������ĵ�����
        horse_tili = horse->query("tili");
        cost_tili = 10 + random(trans_times * 25);

        if (horse_tili <= cost_tili)
        {
                write(horse->name() + NOR "�������㣬����������Ϣ����ɡ�\n");
                return 1;
        }

        running = new("/clone/misc/running");

        if (objectp(follower = horse->query_temp("is_rided_follow")))
        {
                if (environment(follower) && (interactive(follower) || ! userp(follower)))
                        follower->move(running);
        }
        me->move(running);
        horse->add("tili", -1 * cost_tili);
        horse->set_temp("running", 1);
        me->set_temp("running", 1);

        message("vision",  "\n" + this_object() ->name() + HIW "һ����"
                  "˻����һ��س�� ����\n" NOR, environment(me), ({horse}));

        call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);

        return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
        object ob, ob2;
        
        if (objectp(me))
        {
                me->move(trans_path);
                me->delete_temp("running");
                if (random(2))me->improve_skill("riding", 1);
        }
        if (objectp(follower))follower->move(trans_path);
        if (objectp(horse))horse->delete_temp("running");
        // �����ͬ����ͬ���Զ��ƶ�����ǰ
        ob = me->query("me_mater");
        if (objectp(ob))
                ob->move(environment(me));
                
        if (objectp(follower))
        {
                ob2 = follower->query("me_mater");
                if (objectp(ob2))
                        ob2->move(environment(follower));        
        }
                                          
        if(objectp(running))destruct(running);

        if (objectp(horse))
                message("vision",  "\n" + this_object()->name() + HIW "����Ŀ�ĵأ���Ȼ��˻��ǰ"
                          "�߸����ʱ������ɢ����\n" NOR, environment(horse), ({horse}));

        return 1;
}

// ǿ������
int force_me_ride(object me)
{
        object owner;

    if (! objectp(me))
    {
                write("�������\n");
                return 0;
    }

        if (this_object()->query_temp("is_rided_follow"))
                return 0;

        owner = this_object()->query_temp("is_rided_by");

          this_object()->set_temp("is_rided_follow", me);
        me->set_temp("is_riding_follow", this_object());

    message_vision("$NԾ��$n" NOR "������" + owner->name() + "�����\n", me, this_object());

        return 1;
}

// ����
void heart_beat()
{
     int level;
     object follower;
/*
     remove_call_out("start_heart_beat");
     call_out("start_heart_beat", 2);
*/
     level = this_object()->query("level");

     if (! this_object()->query_temp("running"))
     {
            if (this_object()->query("tili") + 1 < this_object()->query("max_tili"))                
                           this_object()->add("tili", level + random(level));
                
            if (this_object()->query("tili") > this_object()->query("max_tili"))
                this_object()->set("tili", this_object()->query("max_tili"));
     }

     follower = this_object()->query_temp("is_rided_follow");
     if (! objectp(follower))return;

     if (! objectp(environment(follower)) || 
         (objectp(follower) && (userp(follower) && ! interactive(follower))) ||
          (objectp(follower) && environment(follower) != environment(this_object()->query_temp("is_rided_by"))))
     {
            this_object()->delete_temp("is_rided_follow");
     }

     return;
}

int query_autoload()
{
     return 1;
}