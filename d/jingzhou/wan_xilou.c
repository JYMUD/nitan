// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "��¥");
        set ("long", @LONG
��������ү��ס�ĵط�����������࣬����һ��ľ������ש����
�м�����͹��������������ϰ�����¡�
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"wan_shufang",
                "east"  : __DIR__"wan_dating",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}