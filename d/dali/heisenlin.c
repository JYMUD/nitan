//Room: /d/dali/heisenlin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ɭ��");
        set("long", @LONG
ӭ��һ��Ƭ��ѹѹ��ɭ�֣��ߴ�Ĺ��ɲ������������һ�ž���
����������������Щ�ر�
LONG );
// ��ٹ� here.
// wait to be done in future.
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "south"      : "/d/dali/dasenlin",
            "northeast"  : "/d/kunming/htroad3", 
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}