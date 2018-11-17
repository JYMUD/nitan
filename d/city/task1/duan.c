// duan.c 段延慶
inherit NPC;

#include <ansi.h>
void create()
{

        set_name("段延慶", ({ "duan  yanqing"}));
        set("gender", "男性");
        set("nickname", HIC"惡貫滿盈"NOR);
        set("age", 54);
        set("str", 25);
        set("dex", 16);
        set("per", 21);
        set("long", "他一身青袍人，長須垂胸，面目漆黑，一雙眼睜大大的，
一霎也不霎。\n");
        set("combat_exp", 3000000+ random(1000000));
        set("attitude", "peaceful");
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
               (: exert_function, "powerup" :),
               (: exert_function, "regenerate" :),
               (: exert_function, "recover" :),
        }));

        set_skill("finger",  200+ random(50));
        set_skill("force", 200);
        set_skill("dodge",  200+ random(50));
        set_skill("staff",  200+ random(50));
        set_skill("parry",  200+ random(50));
        set_skill("sun-finger",  300 + random(50));
        set_skill("kurong-changong",  200 + random(50));
        set_skill("tiannan-bu",  300 + random(50));
        set_skill("lingshe-zhangfa",  300 + random(50));
        map_skill("dodge", "tianna-step");
        map_skill("force", "kurong-changong");
        map_skill("parry", "sun-finger");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "sun-finger");
        prepare_skill("finger", "sun-finger");

        setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}

#include "npc.h"
