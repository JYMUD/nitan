inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����ձ����������¿��ŵġ����治�����������һ����ը��
��һ����¯��
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"street4",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}