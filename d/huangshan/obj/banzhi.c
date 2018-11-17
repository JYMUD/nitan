// banzhi.c

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;
void create()
{
        set_name(HIW "蒼穹千年寒鐵" NOR, ({ "old iron" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "一塊從蒼穹神劍上因被石縫卡住而掉下來的劍尖。\n");
                set("value", 50000);
                set("rigidity",2000);        
                set("material", "steel");
                set("max_enchant",6);
                set("for_create_weapon",1);
        }
        init_dagger(20);
        set("wield_msg", "$N從懷中摸出一塊$n握在手中。\n");
        set("unwield_msg", "$N將手中的$n藏入懷中。\n");
        setup();
}