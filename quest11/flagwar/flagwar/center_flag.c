#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"�������"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "north":__DIR__"rc5",
         "south":__DIR__"bc5",
         "west" :__DIR__"cw1",
         "east" :__DIR__"ce1",
        ]));        
        setup();
}
