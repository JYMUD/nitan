//Room: /d/dali/qingxi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��Ϫ��̶");
        set("long", @LONG
��Ϫ��̶����������ˮ�������ڲ�ɽ��������ʥӦ��֮�������
Ͽ���С�ɽȪ�Ҹ�ӿ��������к����Ϫ��أ�׳�����裬��������
ˮ��ʯ������̽��ӣ����׳����Ϫ��
LONG );
        set("objects", ([
           "/d/dali/npc/biaotou": 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northup"   : "/d/dali/dadieshui",
            "eastup"    : "/d/dali/bijishan",
            "southdown" : "/d/dali/xiaodao1",
        ]));
	set("coor/x", -19110);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}