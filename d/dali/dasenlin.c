//Room: /d/dali/dasenlin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ɭ��");
        set("long", @LONG
��ȥ��������ɽ���ʹ�ɭ�֣������Ѿ���ľï���˼������ˣ�
�����Ǵ�����ԭ�Ĺٵ���·��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "south"   : "/d/dali/dianchi",
            "north"   : "/d/dali/heisenlin",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6850);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}