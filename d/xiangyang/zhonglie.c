// Room: /d/xiangyang/zhonglie.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����������ǵ���������ʮ������Ϊ������������������ʿ�Ź�
�����������ÿ���а����ĵĺú����ⶼ��������һ���һꡣ
LONG );
        set("no_beg", 1);
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7790);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}