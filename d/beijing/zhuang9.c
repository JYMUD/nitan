#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "С����");
        set("long", @LONG
����һ��С���䣬���ϵ������򡣷���ֻ��һ��һ��������򵥣�
ȴʮ�ָɾ����������ű��졣
LONG );
    set("exits", ([
                "south" : "/d/beijing/zhuang8",
    ]));
    set("objects", ([
        "/d/beijing/npc/furen": 1,
          "/d/beijing/npc/shuanger": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4740);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}