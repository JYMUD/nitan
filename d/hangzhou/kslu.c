// kslu.c

#include <room.h>

inherit BUNCH_ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ����ʯ���̾͵�·��·���������������Ŵ󳵣���������
��ʲô��������������ɢɢ��������һЩ��ɫ��ʯͷ���������ǽ���
ʢ��ͭ��ı�ɽ�ˡ�
LONG );
        set("exits", ([
                "west" : __DIR__"road17",
                "east" : __DIR__"kslu2",
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 780);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
}
