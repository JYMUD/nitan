#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
������һƬ�����أ�ԶԶ����������������������̣�������
��Ȯ��֮�����������Ҫ����Ļ��������������ִ������������ָ
�� ask hua about ���壩��
LONG);
        set("exits", ([
                "east" : __DIR__"road1",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/huabo" : 1,
        ]));

        setup();

        replace_program(ROOM);
}
