#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"������·"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northwest":__DIR__"bnw3",
         "southeast":__DIR__"bnw1",
        ]));        
        setup();
}