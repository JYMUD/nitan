#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(NOR + YEL "金环蛇" NOR, ({ "jinhuan she", "jinhuan", "she" }));
        set("long", YEL "这是一只让人看了起毛骨悚然的金环蛇。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 40);
        set("max_qi", 300);
        set("max_ging", 300);
        set("combat_exp", 5000);

        set("snake_poison", ([
                "level"  : 40,
                "perhit" : 20,
                "remain" : 40,
                "maximum": 40,
                "supply" : 2,
        ]));

        set("power", 10);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/unarmed_damage", 35);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she" && arg!="jin she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");
        return notify_fail("金环蛇过于细小，不能化为杖。\n");
}