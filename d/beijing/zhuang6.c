#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "ׯ������");
        set("long", @LONG
����һ�����ã����Ϲ����߰˸���λ������һ�������Ϲ�����һ
�����ˡ�һ�����紵��������ͻȻ���ˡ�
LONG );
    set("exits", ([
        "west" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 100);
        set("coor/y", 4730);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}