#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
������һ���޼ʵĴ󺣣�
LONG);

        set("no_flyto", 1);
        set("outdoors", "dahai");
        set("no_clean_up", 1);
        setup();

}

