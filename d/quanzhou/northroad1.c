// Room: /d/quanzhou/northroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "��ͩ��·");
        set("long", @LONG
����Ȫ�ݵ���Ҫ�ɵ�����ֱ��������ˮ���������ַǷ�����������
�����������Ĺ㳡�����ӵ�����ԶԶ���������������мҺ踣¥��
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([ 
                "east"  : __DIR__"kedian",
                "south" : __DIR__"guangchang",
                "north" : __DIR__"northroad2",
        ]));
	set("coor/x", -900);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}