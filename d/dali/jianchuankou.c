//Room: /d/dali/jianchuankou.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����ɽ��");
        set("long", @LONG
�����ǲ�ɽ��´��һ�����ĳ��򡣴˵�����ɽ�ڣ����߳�ɽ����
������������·���У�Ψ�д���������ɽ������Ǵ������������
����Ҫ�壬������ڴ����е�¥����������פ�����йٱ������վ��
Ѳ�ߣ��̲�������ˡ�
LONG );
        set("objects", ([
           "/d/dali/npc/jiang": 1,
           "/d/dali/npc/bing": 3,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/shanlu1",
            "south"      : "/d/dali/jianchuan",
        ]));
	set("coor/x", -19180);
	set("coor/y", -6800);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}