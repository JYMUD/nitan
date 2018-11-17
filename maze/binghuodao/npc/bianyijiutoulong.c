inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIM "九頭飛龍" NOR, ({ "jiutou long", "jiutou", "long" }));
        set("title", HIY "產卵中的" NOR);
        set("long", HIM "九頭飛龍在產卵期會發生變異，體型會變大一倍，戰鬥力異常恐怖。\n" NOR);

        set("age", 99999);
        set("str",1000);
        set("dex", 1000);
        set("int", 1000);
        set("con", 1000);
        set("max_qi", 500000000);
        set("max_jing", 100000000);
        set("max_jingli", 100000000);
        set("max_neili",5000000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("no_nuoyi", 1);
        set("gift/exp", 3500);
        set("gift/pot", 900);
        set("gift/mar", 50);
        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));


        set_skill("force", 3000);
        set_skill("dodge", 3000);
        set_skill("unarmed", 3000);
        set_skill("sword", 3000);
        set_skill("parry", 3000);
        set_skill("claw", 3000);

        setup();
        add_money("gold", 4 + random(2));
}

void init()
{
        // 隨機攻擊玩家
        if (userp(this_player()))
        {
                kill_ob(this_player());
        }
}
