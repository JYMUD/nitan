// Room:/d/changan/tulu3.c

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
����һ�����������·������̫��·�ϼ���û�����ˣ�����һ
Ƭ�ļš�
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northeast" : "/d/changan/tulu4",
                "southdown" : "/d/changan/tulu2",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}