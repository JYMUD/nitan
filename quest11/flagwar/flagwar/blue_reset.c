#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"������Ϣ��"NOR);
        set("long",@LONG
����ս��

��������һ�� 2 ����
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "north":__DIR__"blue_entry",
        ]));        
        setup();
}