#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",CYN"������·"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "east":__DIR__"ce4",
         "west":__DIR__"ce2",
        ]));        
        setup();
}