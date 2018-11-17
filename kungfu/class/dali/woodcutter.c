// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit NPC;

int ask_me();

void create()
{
        set_name("樵夫", ({ "qiao fu", "qiao", "woodcutter" }));
        set("long", "一個中年樵夫，看起來普普通通，但眼中隱隱閃動着一股霸氣。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);
        set("max_qi", 1800);
        set("max_jing", 1800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 10);
        set("score", 5000);
        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("axe", 150);
        set_skill("finger", 120);
        set_skill("sun-finger", 100);
        set_skill("tiannan-bu", 100);
        set_skill("kurong-changong", 80);
        map_skill("dodge", "duanshi-shenfa");
        map_skill("force", "kurong-changong");
        map_skill("finger", "sun-finger");
        prepare_skill("finger", "sun-finger");

        set("inquiry", ([
                "上山" : "要想上山，先過了我這關再說。\n",
        ]));

        setup();
        carry_object("/d/heizhao/obj/axe1")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_me()
{
        set("combat_exp", 350000);
        return 1;
}

int accept_fight(object ob)
{
        object me = this_object();

        if (environment(me)==find_object("/d/heizhao/yideng4.c"))
        {
                set("combat_exp",350000);
                set_temp("challenger", ob, me);
                return 1;
        }
        else { return 1; }
}

int chat()
{
        object axx, me = this_object();
        object ob=query_temp("challenger", me);
        object weapon;

        if ( !objectp(ob) ) return ::chat();

        if (me->is_fighting(ob)) {
                if( objectp(weapon=query_temp("weapon", me))){
                        command("unwield axe");
                        message_vision("樵夫大喝一聲，向$N連點了三指。\n", ob);
                        call_out("fast_hit", 1, me, ob, 0);
                        call_out("fast_hit", 2, me, ob, 0);
                        call_out("fast_hit", 3, me, ob, 1);
                }
                return ::chat();
        }

        delete_temp("challenger", me);
        remove_call_out("fast_hit");
        if (me->is_fighting()) return ::chat();

        if( query("qi", me)*2 <= query("max_qi", me)){
                command("say "+"果然高明。");
                command("thumb "+getuid(ob));
                axx=new("/d/heizhao/obj/axe1.c");
                axx->move(me);
                command("give "+getuid(ob)+" axe");
                message_vision("樵夫轉身大步下山而去，一會兒就不見了\n",ob);
                destruct(me);
                return ::chat();
        }
        else {
                if( query("qi", ob)*2 <= query("max_qi", ob)){
                        message_vision("樵夫不屑地對$N撇了撇嘴：“就這點功夫，還想上山見我師傅？滾你的吧！”\n",ob);
                        ob->move("/d/heizhao/shanlu9");
                        set("combat_exp",10);
                        if (!present("axe", me)) {
                                axx=new("/d/heizhao/obj/axe1.c");
                                axx->move(me);
                        }
                        weapon = present("axe", me);
                        command("wield axe");
                        return ::chat();
                }
        }
        return ::chat();
}

void fast_hit(object me, object ob,int a)
{
        COMBAT_D->do_attack(me, ob);
        if (a==1) command("wield axe");
        return;
}
