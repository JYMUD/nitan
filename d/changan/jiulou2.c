//Room: jiulou2.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����¥��¥");
        set("long", @LONG
��¥�Ǿ�¥��������������Ŀ����Ƕ������������¥�µĿ�
���ǰ�����������¥���ľƲ�Ҳ������¥�Ƴ������ֵġ����Թ���
����ֱ���ݽǣ�[1��31m       �������������ԾƸ߸裬����¥ͷ��������ͬ
�֣�       ������һ�Σ��ٷ��յ���ƺὭ�ϣ����������[2��37��0m
LONG );


        set("exits", ([
                "down" : "/d/changan/jiulou",
        ]));
        set("objects", ([
                "/d/changan/npc/yang-laoban" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}