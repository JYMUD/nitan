// Room:/d/changan/tulu4.c

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
����һ�����������·������̫��·�ϵ�����Ҳ���࣬�����
�ش�ƫԶ��Ե�ʣ�����û��ʲô���̡�
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southwest" : "/d/changan/tulu3",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 2020);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}