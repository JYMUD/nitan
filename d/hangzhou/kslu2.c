// kslu2.c

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ����ʯ���̾͵�·��·���������������Ŵ󳵣���������
��ʲô��������������ɢɢ��������һЩ��ɫ��ʯͷ���������ǽ���
ʢ��ͭ��ı�ɽ�ˡ�
LONG );
        set("exits", ([
                "west" : __DIR__"kslu",
                "east" : __DIR__"kuangshan",
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 790);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}