// Room: /d/guiyun/chufang.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ǹ���ׯ�ĳ�������Ӧ������ÿ�յķ�ʳ�����г������˺͵�
�ϵ�ζ����������ʦ����æµ�š�ż������Щ�Բ������ʳ������ʱʣ
�µ������������
LONG );
        set("exits", ([
                "west" : __DIR__"fanting",
        ]));
        set("objects",([
                __DIR__"obj/meat" : 2,
                __DIR__"obj/baozi" : 1,
                __DIR__"obj/rice" : 1,
                __DIR__"obj/zongzi" : 1,
        ]));
        set("coor/x", 260);
        set("coor/y", -870);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
