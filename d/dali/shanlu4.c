//Room: /d/dali/shanlu4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long", @LONG
һ��ɽ·��������ï�ܵ����֣����������಻���Ĵ�ɽ����·��
�Լ��ɼ�һЩ����Ĵ���ɽ·���������š�
LONG );
        set("objects", ([
           "/d/dali/npc/shennongdizi": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/shanlu2",
            "southwest"  : "/d/dali/shanlu5",
            "westup"     : "/d/wuliang/shanlu1",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}