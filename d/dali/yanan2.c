//Room: /d/dali/yanan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�س�С·");
        set("long", @LONG
����һ�����ŵ���ϰ���С·������а������Ϯ�ˡ�Զ�����
���棬�̲�����������Ϸˮ��ңң�ɼ��δ����洬�ᷫ���ơ��˵���
�˼��ɾ�����·����ֱ�ϵ��������Ⱥɽ��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"    : "/d/dali/yanan1",
            "westup"  : "/d/dali/bijishan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19090);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}