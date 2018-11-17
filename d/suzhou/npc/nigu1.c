// nigu1.c

inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("尼姑", ({ "ni gu", "ni", "gu" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long","這位尼姑正坐在鋪墊上，雙手捻着珠鏈，嘴中念念有詞。 \n");
        set("combat_exp", 1000);
        set("attitude", "friendly");
        setup();
}

void init()
{        
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say( "尼姑說道：這位" + RANK_D->query_respect(ob) + "，多謝捐贈，願佛祖保佑。\n");
        return;
}
