#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ���·ʮ����խ�����߲�Զ��һ��
��ɽ��Ҫȥ�ɶ��Ļ������뷭��������ɽ������һƬ�������������̡�
LONG );
        set("exits", ([
                  "westup" : __DIR__"shudao15",
                  "east" : __DIR__"shudao13",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15110);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}