//Room: /d/dali/hongsheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ʥ����");
        set("long", @LONG
��ʥ����������һ�����������ڲ�ɽ֮´�����������Ϊ������
������֮һ����ʥ����Ϊ�ķ��ο���שʯ�����������֮����ש����
��ɬ����ʹ���ĽǷ��̡��������������������ߣ�����������
LONG );
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/cangshan",
            "enter"     : "/d/dali/hongsheng1",
            "south"     : "/d/tianlongsi/damen",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalin"); 
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}