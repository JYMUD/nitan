inherit KNOWER;
inherit F_VENDOR;

void create()
{
        set_name("珠寶商", ({ "zhubao shang", "zhubao", "shang" }));
        set("gender", "男性" );
        set("age", 32);
        set("long", "這是一個來自西域的珠寶商人。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/fam/etc/va2",
                "/clone/fam/etc/va3",
                "/clone/fam/etc/va5",
                "/clone/fam/etc/va6",
        }));
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy", "buy");
}