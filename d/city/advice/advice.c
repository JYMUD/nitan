#include <ansi.h>
inherit ROOM;
int is_chat_room()      { return 1;}
void create()
{
       set("short", HIY "��Ϸ�ͷ�" NOR);
        set("long", @LONG
��Ҷ���Ϸ�����������⼰��Ϸ��չ�����������POST�����
лл��Һ�����
LONG );

        set("exits", ([
                "out" : "/d/city/kedian",
                "sea" : "/inherit/room/hanghai_room.c",
                "up"  : "/adm/daemons/fairyland_quest/room_door_hj",
        ]));
                set("no_fight", 1);
                set("no_sleep_room",1);
	set("coor/x", 1);
	set("coor/y", 11);
	set("coor/z", 10);
	setup();
        "/clone/board/advice_b"->foo();

}