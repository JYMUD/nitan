#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"���Ӷ�·"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northeast":__DIR__"bne4",
         "southwest":__DIR__"bne2",
        ]));        
        setup();
}