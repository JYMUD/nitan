#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"��Ӷ�·"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "southeast":__DIR__"rse5",
         "northwest":__DIR__"rse3",
        ]));        
        setup();
}