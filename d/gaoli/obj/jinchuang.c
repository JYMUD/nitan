// jinchuang.c 金創葯
inherit COMBINED_ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("金創葯", ({"jinchuang yao", "jin", "jinchuang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                           set("heal_up", 1);
                                          set("value", 5000);
                set("base_unit", "包");
                set("base_weight", 100);
                 set("long", "這是一包武林人士必備的金創葯。\n");
                set("base_value", 5000);
        }
        set_amount(1);
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼葯？\n");
        if ((int)this_player()->query("eff_qi") == 
            (int)this_player()->query("max_qi"))
                return notify_fail("你現在不需要用金創葯。\n");
        else {
                this_player()->add("qi", 50);
                message_vision("$N吃下一包金創葯，氣色看起來好多了。\n", this_player());
                destruct(this_object());
                return 1;
        }
}

