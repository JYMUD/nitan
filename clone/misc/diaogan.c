// diaogan.c ����

#include <ansi.h>

inherit ITEM;

void init()
{
        if (interactive(this_player()) &&
            environment() == this_player())
        {
                add_action("do_fish", "fish");
                add_action("do_draw", "draw");
        }
}

void create()
{
        set_name(HIG "����" NOR, ({ "diao gan", "gan" }));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "����һ�������߳��õĵ��ͣ�������������(fish)��\n");
                set("value", 2000);
        }

        setup();
}

int do_fish()
{
        object yr;
        object ob;
        object me = this_player();

        if (! arrayp(query("resource/fish", environment(me))))
                return notify_fail("���￴������������ӡ�\n");

        if (! objectp(yr = present("yu er", me)) || yr->query_amount() < 1)
                return notify_fail("������û������ˡ�\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("�㻹��æ����ͷ�ϵ�������˵�ɡ�\n");

        message_vision("$N�ͳ�һ���������ϸ�ķ��ڵ����ϣ�����һ˦�ˣ�ֻ��ˮ���ϵ�����\n"
                       "һ����ԲȦ���м�ֻ��һ����ɫ�ĸ���������ˮ��������\n", me);
        yr->add_amount(-1);
        me->start_busy((: call_other, __FILE__, "finishing" :),
                       (: call_other, __FILE__, "halt_finishing" :));
        set_temp("owner", me);
        set_temp("fishing", 0, me);
        set_temp("fishing_env", environment(me), me);
        return 1;
}

int finishing(object me)
{
        int stage;

        if( environment(me) != query_temp("fishing_env", me) )
        {
                delete_temp("fishing", me);
                delete_temp("fishing_env", me);
                return 0;
        }

        switch(stage=query_temp("fishing", me) )
        {
        case 1:
                if (random(4))
                {
                        message_vision("$N�ĸ���������𶯣�һ��"
                                       "һ�µ�ҡ�θ���ͣ��\n", me);
                        break;
                }

                message_vision("$N�ĸ��Ӻ�Ȼ���ҵ���������\n", me);
                stage++;
                break;

        case 2:
        case 3:
                message_vision(random(2) ? "$N�ĸ��Ӻ������ҡ�ڸ���ͣ��\n"
                                         : "$N�ĸ�����Ȼ����һ�ܣ�Ȼ��������ˮ�档\n",
                               me);
                stage++;
                break;
        case 4:
                message_vision(random(2) ? "һ����ҵ�ҡ�ڹ��󣬸��Ӱ���"
                                           "������$N��æ������ͣ�һ�����Ͽտ���Ҳ��\n"
                                         : "������Ȼ�����Ұڶ�����Ȼ�ְ��������ˣ�$N�ɻ��"
                                           "������ͣ���������\n���㹳������ʲôҲû�С�\n",
                               me);
                tell_object(me, CYN "����������(draw)�����ˣ��װ׵�����һ�������\n" NOR);
                delete_temp("fishing", me);
                delete_temp("owner");
                return 0;

        default:
                if (random(5))
                {
                        if (random(3)) return 1;
                        tell_object(me, random(2) ? "ˮ�沨��������û��ʲô�仯��\n"
                                                  : "΢������Ĵ���ˮ�浴��һ���ϸ�ˣ�����û�����Ϲ���\n");
                        break;
                }
                message_vision("��Ȼ$N�ĸ�������һ�¡�\n", me);
                stage = 1;
                break;
        }

        set_temp("fishing", stage, me);
        return 1;
}

int halt_finishing(object me)
{
        delete_temp("owner");
        delete_temp("fishing", me);
        message_vision("$N������ͣ��������ǲ����ٵ��ˡ�\n",  me);
        return 1;
}

int do_draw(string arg)
{
        string *fish;
        object ob;
        object me;
        int stage;
        int exp;
        int pot;

        if (! arg || ! id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

        me = this_player();

        if (query_temp("owner") != me)
                return notify_fail("����û�ڵ��㣬���˸�ʲô��\n");

        if( environment(me) != query_temp("fishing_env", me) )
                return 0;

        stage=query_temp("fishing", me);
        if (stage < 2)
        {
                message_vision("$N��æһ�����ͣ��߸ߵľ���������ȴ�����������Ȼ����"
                               "�������ӣ�ֻ��\n��ͷɥ�������°Ѹ�˦�˳�ȥ��\n", me);
                set_temp("fishing", 0, me);
                return 1;
        }

        fish=query("resource/fish", environment(me));
        if (sizeof(fish) < 1)
                log_file("log", sprintf("variable: resource/fish error in %s.\n",
                                        base_name(environment(me))));
        ob = new(fish[random(sizeof(fish))]);

        message_vision(random(2) ? "$N�ּ��ۿ죬�͵�һ�յ��ͣ�ֻ���������һ" +
                                   query("unit", ob)+"Ť��Ťȥ��"+
                                   ob->name() + "��\n"
                                 :"$N˳��һ���ˣ���ʱ��һ"+query("unit", ob)+
                                   ob->name() + "����������\n", me);
        tell_object(me,HIG"�������һ"+query("unit", ob)+
                        ob->name() + HIG + "��\n" NOR);
        ob->move(me, 1);

        delete_temp("owner");
        delete_temp("fishing", me);
        delete_temp("fishing_env", me);

        if( query("total_hatred", me)>10 )
                addn("total_hatred", -10, me);
        else
                set("total_hatred", 0, me);

        if( query("combat_exp", me)<300000 || 
            query("combat_exp", me)>1200000 )
                return 1;

        exp = 50 + random(100);
        pot = exp / 3;
        GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
        tell_object(me, HIC "������΢΢һ��������ѧ�����������һ�㡣\n" NOR);
        return 1;
}

int move(mixed dest, int raw)
{
        object me;

        if (me = query_temp("owner"))
                me->interrupt_me();

        return ::move(dest, raw);
}
