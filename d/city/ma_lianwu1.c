#include <room.h>
inherit ROOM;

void create()
{
        set("short", "���䳡");
        set("long", @LONG
�����ĳ�����������ϸϸ�Ļ����������ʺ����䡣������
����ؤ��ĵ����������䡣���䳡���������ż���ľ׮��ľ׮
��Χ���������ɸ���ɳ�ӡ������Ǳ����⡣���ұ���һ��С�š�
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_bingqi",
                "east"  : __DIR__"ma_xiaojing",
                "north" : __DIR__"ma_zoulang2",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 1 + random(2),
                "/d/gaibang/npc/2dai" : 1,
                "/d/gaibang/npc/6dai" : 1,
                "/d/gaibang/npc/7dai" : 1,
        ]));
        create_door("east", "ľ��", "west", DOOR_CLOSED);
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
}