inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ǻ�����ɽ·��ֻ��һ��������᫵�С����
LONG );
        set("exits", ([
                "northup" : "/d/beijing/shanlu2",
                "eastdown": "/d/beijing/zhuang1",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7620);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}