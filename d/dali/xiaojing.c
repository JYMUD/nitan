//Room: /d/dali/xiaojing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","ɽ��С��");
        set("long", @LONG
������Դɽ������ʯС�����������ѣ�������ľïʢ��������ա�
������Ҷ������ϡ�ɡ������ౡ�����ϰϰ��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"    : "/d/dali/jinzhihe",
            "westup"  : "/d/dali/dadieshui",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19100);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}