inherit ROOM;

void create()
{
        set("short", "���䳡");
        set("long", @LONG
�������̼ұ������һ�����䳡�������ĳ�����������ϸϸ
�Ļ����������ʺ����䡣���������Ӳݴ������������Ѿ��ķϺ�
��һ��ʱ���ˡ�
LONG);
        set("exits", ([
                "south"  : __DIR__"shang_houyuan",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}