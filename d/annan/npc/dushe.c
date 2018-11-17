// dushe

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("毒蛇", ({ "dushe" }) );
        set("long",        "一支昂首吐信的毒蛇正虎視眈眈地盯著你。\n");

        set("race", "野獸");
        set("age", 3);
        set("attitude", "peaceful");

        set("max_ging", 1180);
        set("max_qi", 1180);

        set("str", 10);
        set("cor", 50);

        set("limbs", ({ "頭部", "身體", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if (interactive(me = this_player()))
        {
        if (!(ob = present("xionghuang", this_player())))          
               {
               remove_call_out("kill_ob");
               call_out("kill_ob", 1, me);
                }
        }
}

int hit_ob(object me, object ob, int damage)
{
    if( query("combat_exp", ob)>1000)return 1;
        if( random(damage)>query_temp("apply/armor", ob )
        &&        (int)ob->query_condition("snake_poison") < 10 ) {
                ob->apply_condition("snake_poison", 20);
        tell_object(ob, HIG "你覺得被咬中的地方一陣麻木！\n" NOR );
        }
}