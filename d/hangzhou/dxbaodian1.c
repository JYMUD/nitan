// dxbaodian1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "���۱���");
        set("long", @LONG
������������һ���ߴ���ʮ���׵Ĵ�����д�š����۱����
��ǰ�������˽ǾŲ�ʯ���������ֽ��������
LONG);
        set("exits", ([
                "south"     : __DIR__"tianwangdian",
                "enter"     : __DIR__"dxbaodian2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 739);
	set("coor/y", -2041);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}