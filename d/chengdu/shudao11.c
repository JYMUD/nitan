#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ�����������Խ����ɽ���Ϳ��Խ�
���Ĵ�����ˣ�������ȥ�羰��������Ͽ����·ʮ����᫣�ʱ����ת
ʱ����ɽ��ʱ����Ҫ����ɭ�֡�
LONG );
        set("exits", ([
                "east" : __DIR__"baidicheng",
                  "west" : __DIR__"shudao12",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15080);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}