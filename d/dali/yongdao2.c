//Room: /d/dali/yongdao2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��");
        set("long", @LONG
���������������������������ܵĲ�����ľ�����͸����Ҷ��
�ڵ����������ǰߵ㡣ʯ������·�����࣬��������̲ݣ���׺��
һ�ǰ���С������Χʮ�ְ�����ż���������
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/neitang",
            "east"       : "/d/dali/chahua8",
            "southwest"  : "/d/dali/yongdao1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}