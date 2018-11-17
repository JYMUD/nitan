//miantiao1.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("刀削麵", ({"daoxiao mian", "miantiao", "mian"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一碗熱氣騰騰的刀削麵。\n");
                set("unit", "碗");
                set("value", 200);
                set("food_remaining", 5);
                set("food_supply", 35);
        }
}