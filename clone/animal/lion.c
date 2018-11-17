// laohu.c 獅子
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("獅子", ({ "lion", "shi zi", "shi" }) );
        set("race", "走獸");
        set("age", 25);
        set("long", "一隻黃毛長鬃的雄獅，爪牙銳利，神情威武。\n");
        set("msg_fail", "$n沖$N呲牙吼了一聲");
        set("msg_succ", "$n一面口中向$N荷荷發威，一面向後退了半步，似乎有些怯了");
        set("msg_trained","$n低吼着在$N的面前伏了下來");
        set("auto_follow",1);
        set("attitude", "aggressive");

        set("wildness", 12);
        set("ridable", 1);
        set("ability", 4);
        
        set("str", 40); 
        set("con", 40);
        set("dex", 40); 
        set("int", 10);

        set("combat_exp", 20000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 70);
        set_temp("apply/armor",  30);

        set_weight(150000);

        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "獅子來回走動，朝着你端相了半晌，口中荷荷的發威。\n",
                "獅子長長吼了一聲。\n",
                "獅子趴在地上，擺頭抖了抖鬃毛，一雙眼睛緊緊盯着你。\n",
        }) );

        setup();
}

void die()
{
        message_vision("\n$N仰天慘嚎了一聲，趴在地上不動了。\n", this_object());
        ::die();
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && ob->query_weight() >= 50000) {
                if(!this_object()->query_lord(ob)) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
                }
        }       

//      add_action("do_ride", "ride");
//      add_action("do_unride", "unride");
        add_action("do_look", "look");
}

int do_look(string arg)
{
        object *inv;
        int i;

        inv = all_inventory(this_object());

        if (!id(arg)) return 0;

        if (!sizeof(inv)) return 0;

        printf(query("long", this_object())+
        COMBAT_D->eff_status_msg(query("eff_qi")* 100 / query("max_qi")) + "\n" 
        + "它身上馱着：\n");
        for (i = 0; i < sizeof(inv); i++)
                printf("%s \n", inv[i]->short());
        return 1;
}
