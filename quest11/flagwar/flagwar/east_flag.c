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
         "west" :__DIR__"ce5",
         "southwest":__DIR__"bne5",
         "northwest":__DIR__"rse5",
        ]));        
        setup();
}