//Room: /d/dali/sikong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","˾����");
        set("long", @LONG
�����Ǵ����˾���á�����������ı�ȴ�������鼮��������
�˰������������㹤�����ֲ��;�
LONG );
        set("objects", ([
            CLASS_D("dali")+"/batianshi" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19121);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}