inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǻ�ɽ���һƬ���֣���˵�ƽ�������������û��
LONG);
        set("exits", ([ 
               "south"       : __DIR__"shanlu14",
        ]));

        set("outdoors", "henshan");

        if (random(10) == 1)
                set("objects", ([
                        "/kungfu/class/misc/goldtiger"  :  1,
                ]));    

	set("coor/x", -6950);
	set("coor/y", -5500);
	set("coor/z", 20);
	setup();
}
