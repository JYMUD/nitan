//Room: /d/dali/yuxuguanqian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�����ǰ");
        set("long", @LONG
����һ����ۣ���ǰ����д�š�����ۡ��������֣�����һ����
ˮ������С����������������ʵ���������Եĺõط���
LONG );
        set("objects", ([
           "/d/dali/npc/xiaodaogu": 2,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yuxuguan",
            "south"  : "/d/dali/hudiequan",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}