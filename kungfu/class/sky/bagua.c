#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "��������" NOR);
        set("long", HIR @LONG

                ��        ��        ��

    ���������������֮�����������Ĵ���ʯ��ᾣ�������
���׳����ںδ���

LONG NOR );

        set("sleep_room", 1);
        set("exits", ([
             "north"      :    __FILE__,
             "south"      :    __FILE__,
             "east"       :    __FILE__,
             "west"       :    __FILE__,
        ]));
        set("sky", 1);
        setup();
}

void init()
{     
        object me = this_player();
     
        if (me->query_skill("conut", 1))        
                 me->add_temp("bagua", 10);
                
        else 
                 me->add_temp("bagua", 1);
        
        if (me->query_temp("bagua") >= 10000 ||
            random(10000 - me->query_temp("bagua")) == 0 )
        {
                 write(HIG "\n�������߳��˰�������԰����������µ���ʶ��\n" NOR);
                 me->move(__DIR__"sky9");
                 me->add_temp("baguazhen", 1);
                 me->delete_temp("bagua");
        }
}
