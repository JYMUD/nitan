#include <room.h>
inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
С·��������ͷ׵�ʯ���̳ɵġ�ʯ����ɸ��ֻ��ƣ���
�Ǻÿ���·�߳�����ɻ�ͤͤ�����ѷ�����ȥ��ֻ��ż������
�ļ����������������ܵ�������
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_lianwu1",
                "east"  : __DIR__"ma_huayuan",
        ]));
        create_door("west", "ľ��", "east", DOOR_CLOSED);
        set("no_clean_up", 0);
	set("coor/x", 40);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
}