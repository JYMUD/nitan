// Room: /d/jiaxing/jxnanmen.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
�����Ǽ��˵����š���Χ����ï�ܵ����֡���������������Ͽ�
�븣�������Ͼ��Ǻų����õĺ��ݳ��ˡ�
LONG );
        set("exits", ([
                "north"    : __DIR__"jiaxing",
                "east"     : __DIR__"tieqiang",
                "south"    : __DIR__"jnroad4",
                "southeast": "/d/hangzhou/road1",
                "southwest": __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiaxing");
	set("coor/x", 1190);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}