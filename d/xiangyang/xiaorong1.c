// Room: /d/xiangyang/xiaorong1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "��ͬ");
        set("long", @LONG
���������������ϰ��յľ�ס����ֻ��СŪ��������ЩС���棬
�����С�С�ӻ��̵ȡ�һЩ������������������
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west" : __DIR__"jiekou2",
                "north" : __DIR__"wjb_damen",
        ]));
        set("objects", ([
                __DIR__"npc/kid" : 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7780);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}