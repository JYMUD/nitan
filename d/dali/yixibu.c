//Room: /d/dali/yixibu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��Ϫ��");
        set("long",@LONG
��Ϫ��Ҳ���������������Ĳ��䡣���ﴦ���µأ������в���ũ
���ũҵ�����Ҫ�����ָ���������񾭳�Ǩ�㣬��������˼�
������⣬�������ݶ��ܼ�ª��
LONG);
        set("objects", ([
           __DIR__"npc/shaonu": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : __DIR__"atoubu",
            "south"      : __DIR__"wuyiminju4",
            "east"       : __DIR__"biluoshan",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}