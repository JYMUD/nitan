#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "����ˮ��̶��" NOR);
        set("long", HIB @LONG

                    ��     ˮ     ��     ̶

    ���������˾�ı�ˮ��̶����˵������֮�׵�����������û�ڴ�̶
�С�̶�б�ˮ���İ��ޱȣ������ƺ��м������ڣ���ʵ�ڿ�������ͨ��
�δ���ˮ�б���̹ǣ������������ܣ���ֻ����������һ��һ����ʧ��


LONG NOR );

        set("exits", ([
                "east" : __DIR__"hantan2",
                "west" : __DIR__"hantan3",
                "south" :__DIR__"hantan1",
                "north" :__DIR__"hantan5",
        ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        set("is_hantan", 1); 

        setup();
}

void init()
{
        object me;
        int meqi, meneili, decqi, mq;
        me = this_player();

        if ( present("diyin xuemai", me))
        {
                tell_object(me, RED "�㻳�еĵ���Ѫ������һ������������ס�������"
                                "������\n" NOR);
                return 0;
        }
        tell_object(me, HIW "�����ݱ�ˮ��̶��̶�к�������ιǣ���"
                        "ֻ������ѪҺ������סһ�㣡\n" NOR);
        meqi=query("qi", me);
        meneili=query("neili", me);
        mq=query("max_qi", me);
        decqi = (int)( mq / (random(4) + 5 + meneili/200) );
        meqi = meqi - decqi;
        set("neili", 0, me);

        if(meqi > 0)
        {
                set("qi", meqi, me);
        }
   else {
                set_temp("die_reason", "�ڱ�ˮ��̶��������", me);
                me->die();
        }
        return 0;
}