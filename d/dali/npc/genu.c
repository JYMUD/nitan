// genu.c

inherit NPC;

void create()
{
    set_name("歌女",({ "ge nv", "girl" }) );
        set("gender", "女性" );
        set("age", 17);
        set("long", "她是一個賣唱為生的歌女。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 700);
        set("shen_type", 1);
        set("per", 22);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/kenao")->wear();
        carry_object("/d/dali/npc/obj/yaoqin")->wield();
}
