//Room: /d/dali/shanlu6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long", @LONG
һ��ɽ·��������ï�ܵ����֣����������಻���Ĵ�ɽ��������
һ���޼ʵ���˫���ɴ�ɭ�֣���˵��а�̽��������л����·����
���ɼ�һЩ����Ĵ���ɽ·ת�������š�
LONG );
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : "/d/dali/shanlu5",
            "east"       : "/d/dali/gudao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}