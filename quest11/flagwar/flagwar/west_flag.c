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
         "east" :__DIR__"cw5",
       	 "southeast":__DIR__"bnw5",
       	 "northeast":__DIR__"rsw5",
        ]));        
        setup();
}