#include <room.h>
inherit ROOM;

void create()
{
        set("short", "Ժ��");
        set("long", @LONG
����һ����Ժ�ӣ���ɨ��һ����Ⱦ������װ���ż����������
�������¡������������⡣������һ�䴢���ң����Źر��š�������
����ɽׯ�Ĵ������ϱ߾��Ǵ����ˡ�
LONG );
        set("exits", ([
                "northup" : __DIR__"dating",
                "west"    : __DIR__"wuqiku",
                "east"    : __DIR__"storeroom",
                "south"   : __DIR__"damen",
        ]));
        create_door("east", "ľ��", "west", DOOR_CLOSED);
        set("coor/x", -49970);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
}
