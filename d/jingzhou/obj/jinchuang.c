// jinchuang.c 金創葯

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("金創葯", ({"jinchuang yao", "jin", "jinchuang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包武林人士必備的金創葯。\n");
                set("value", 5000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼葯？\n");
        if( query("eff_qi", this_player()) == 
            this_player(query("max_qi", )) )
                return notify_fail("你現在不需要用金創葯。\n");
        else {
                this_player()->receive_curing("qi", 50);
                message_vision("$N吃下一包金創葯，氣色看起來好多了。\n", this_player());
                destruct(this_object());
                return 1;
        }
}
