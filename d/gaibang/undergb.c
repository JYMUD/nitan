// Room: /d/gaibang/undergb.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short","��������");
        set("long", @LONG
����ؤ����Ҫ�ܵ�֮һ���ɴ���������ֱ���������ܹ��߻谵��
�ƺ��м����ڰ��Ķ���������ߡ����µ�������������������ȥϤϤ
�������졣
LONG );
        set("exits", ([
                "up" : __DIR__"pomiao",
                "southwest":__DIR__"zlandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/xi" : 1,
                "/d/gaibang/npc/6dai" : 1 + random(2),
                "/d/gaibang/npc/7dai" : 1 + random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
        set("coor/y", 60);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}
