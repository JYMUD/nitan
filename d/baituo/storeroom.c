#include <room.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǹ������ң������ܲ�͸�磬ֻ��һ�ȹر��ŵĴ��š�
LONG );
        set("exits", ([
                "west" : __DIR__"yuanzi",
        ]));
        create_door("west", "ľ��", "east", DOOR_CLOSED);
        set("coor/x", -49970);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
}
