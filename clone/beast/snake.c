//snake.c

inherit SNAKE;

void create()
{
        set_name("黑冠巨蟒", ({ "black snake", "she" }) );
        set("race", "野獸");
        set("age", 20);
        set("long", "一隻龐然大物，它眼中噴火,好象要一口把你吞下。\n");
        set("attitude", "aggressive");
        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 500);
        set("max_jing", 500);
        set("str", 86);
        set("con", 80);
        set("limbs", ({ "頭部", "身體", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("combat_exp", 1000000);

        set_temp("apply/attack", 85);
        set_temp("apply/damage", 80);
        set_temp("apply/armor", 88);
        set_temp("apply/defence",80);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");

        return notify_fail("黑冠巨蟒身子太過粗大，無法化為蛇杖。\n");
}