#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"三清宮規"NOR, ({ "sqgonggui" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "stone");
            set("long", "一本三清宮的宮規\n");
          } 
    set("owner", "王處一");
        setup();  
}   
