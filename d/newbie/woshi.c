#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "����" NOR);
        set("long", @LONG
���Ǵ峤���Է������Ŵ������ţ����ߺܻ谵��������������
ֻ���м����һ����ʰ����������Ĵ󴲣����ž�������˯��������
ָ�� sleep����
LONG);
        set("exits", ([
                "south" : __DIR__"cunzhangjia",
        ]));

        set("xinshoucun", 1);
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);

        setup();

        replace_program(ROOM);
}