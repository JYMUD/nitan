#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "��������Դ��" NOR);
        set("long", HIM @LONG

                ��     ��     ��      Դ
    ��յľ�ͷ��һ����Դʤ�أ������ƺ�û���յ㣬��ʼ���ܷ���
��һ������أ����������뵣��������ƣ��ѵ��Ǵ�˵�е��ɾ�����
���������𣬵��ƺ����ø��������ˣ���Լ�䣬����ǰ������һλ��
Ϥ�����꣬�����ⲦŪ�Ź��٣���������֮�������Ŀ���������ֻ��
��Զ���ڴ˴�����������˼�ķ��������
LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tianshen2": 1,
        ]));
        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // ���������MISS������Ѿ���horse.c������
        set("no_rideto", 1);   // ���������MISS������Ѿ���horse.c������
        set("no_obsend", 1);
        set("no_paimai", 1);
        set("sky", 1);
        
        setup();
}

void init()
{
        object me = this_player();
        
        tell_object(me, HIG "\n��ϲ�㣬�Ѿ�������ж�ת����������Ի�������ɶ�ת��\n" NOR);
}
