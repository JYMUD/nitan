// Code of ShenZhou
// branch3.c
// Jay 7/4/96
#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
    set_name(YEL"大樹榦"NOR, ({"shuzhi", "zhi", "branch"}));
    set_weight(1000+random(2000)); 
    if( clonep() )
      set_default_object(__FILE__);
    else {
      set("long", "這是一根折斷的大樹榦。\n");
        set("unit","根");
        set("wield_msg","$N舉起一根大樹榦托在手中。\n");
        set("material", "wood");
    }
    init_staff(random(2));

    setup();
}