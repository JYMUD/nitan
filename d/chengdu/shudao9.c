#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
������һ����ɽ��ɽ�����ٽ�һ���Ƕ��͵����£���ϸ��ȥ����
һЩʯ�ѿ�����ţ�����ȥ��ֻ���������к����м������ӡ�
LONG );
        set("exits", ([
                  "eastdown" :  __DIR__"shudao8",
                "west" : __DIR__"shudao10",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15070);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}