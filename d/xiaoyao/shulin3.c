// Room: /d/xiaoyao/shulin3.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һƬï�ܵ����֡��ܶ�ü�ʮ�ɸߵĴ�������һ�飬��һ�Ѱ�
�����ɡ�������¶����ڱεð�Ȼ�޹⡣�����л���ʱ������������Ȼ
���������졣
LONG );
        set("objects", ([ ]));
        set("outdoors", "xiaoyao");
        set("exits", ([ /* sizeof() == 4 */
                "south" : __DIR__"shulin3",
                "north" : __DIR__"shulin3",
                "east"  : __DIR__"shulin2",
                "west"  : "/d/wudang/wdroad4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 100);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}