//shufang.c  by winder

#include <room.h>
#include <skill.h>

inherit ROOM;

void create()
{        
        seteuid(getuid());
        set("short", "�鷿");
        set("long",
"������źС������鷿�����ŵ��ӿ�����������ѧʫ������ǽ���Ű�\n"
"�ż�����ܣ�һ����ʫѡ��(shi)���������ע�⣬����ǽ�ϻ����˼���\n"
"�ֻ�(hua)���������������ѧ�����ٶ�����\n"
);        
        set("exits", ([        
                "east" : __DIR__"nzlangw3",
        ]));
        set("item_desc", ([
                "shi" : "����һ����ƽ������ʫѡ�������ٵ���������(yin)��\n",
                "hua" : "����һ����ġ֣���ŵ��ֻ������ٵ����ڿ�(kan)��\n",
        ]));

        set("no_steal", "1");
        set("no_fight", "1");
        set("area", "tangmen");
        set("objects", ([
                CLASS_D("tangmen") + "/tangyu" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_look","kan");
        add_action("do_du","yin");
}

int do_look(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 20 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("��������æ���ء�\n");

        if ( arg == "hua")
        {
                if( (int)me->query_skill("literate", 1) > 50 )
                        return notify_fail("������ֻ���ϸ��Ħ��һ��������ִ����Ѿ�ѧ����ʲô�ˡ�\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "��ר�ĵ��ж�ǽ�ϵ��ֻ�����ʱ�������ָ��ġһ����\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 10 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);
                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");

                        if( query("potential", me)-query("learned_points", me) <= 0 )
                                write("�㿴���ֻ�������ĥ����û��һ˿�ĵá�\n");
                }
                return 1;
        }
        else
                return 0;
}

int do_du(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 30 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("��������æ���ء�\n");

        if ( arg == "shi")
        {
                if( (int)me->query_skill("literate", 1) < 51 )
                        return notify_fail("��������ʫѡ��������һҳ���־�ʲôҲ��������\n");

                if( (int)me->query_skill("literate", 1) > 101 )
                        return notify_fail("��������ʫѡ�������˷�����û��ʲô��ѧ���ˡ�\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "��ר�ĵ��ж�����ϵ�ʫ������������ʱ������������\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);

                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");

                        if( query("potential", me) <= query("learned_points", me) )
                                write("�㿴��ʫ��������ĥ����û��һ˿�ĵá�\n");
                }
                return 1;
        }
        else
                return 0;
}