inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ǻ�����ɽ·��ֻ��һ��������᫵�С��������������̣�
���˾��ñ������쬵ġ�
LONG );
        set("exits", ([
                "westup"    : "/d/beijing/shanlu3",
                "southdown" : "/d/beijing/shanlu1",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7630);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}