//Room: /d/dali/xiaodao2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�ּ�С��");
        set("long", @LONG
����һ����ʯ�̳ɵ�С�����������۵�ͨ��ǰ�������������ܵ�
���������˼�������Ω�����ߵ��·�棬΢�紵����Ҷ��ɳɳ���졣
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : "/d/dali/heilongling",
            "west"      : "/d/dali/southgate",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}