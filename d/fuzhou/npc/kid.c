// kid.c
// Last Modifyed by Winder on Sep. 10 2002

inherit NPC;
void create()
{
        set_name("頑童",({ "kid" }) );
        set("gender", "男性" );
        set("age", 6);
        set("long", "這是個頑皮小童，頭上扎着衝天小辮。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
        set("shen", 100);
        set("shen_type", 1);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
                case 0:
                        say("頑童大聲哭嚷道：這位" + RANK_D->query_respect(ob) + "，我要燈籠，給我燈籠。\n");
                        break;
                case 1:
                        say("頑童大聲哭嚷道：這位" + RANK_D->query_respect(ob) + "，看什麼看，再看我扁你。\n");
                        break;
        }
}