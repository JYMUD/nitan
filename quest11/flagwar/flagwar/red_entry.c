#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"������"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        set("stab_flag", 1);
        set("party","red");
        set("exits",([
         "south":__DIR__"rc1",
         "southeast":__DIR__"rse1",
         "southwest":__DIR__"rsw1",		         	
        ]));        
        setup();
}
void open_exit() {
        set("exits",([
         "south":__DIR__"rc1",
         "southeast":__DIR__"rse1",
         "southwest":__DIR__"rsw1",		         	
        ]));    
}