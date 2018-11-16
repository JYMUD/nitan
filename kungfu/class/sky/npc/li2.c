#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_COAGENT;

void create()
{
        set_name("����ң", ({ "li xiaoyao", "li", "xiaoyao"}));
        set("long", "�ɽ��������еĴ�������������ɽ����\n" 
                    "�������գ���ϰ�Ҵ���ѧ����̽�����Լ���\n"
                    "�ľ�����һ�������Ľ�����\n"); 
        set("nickname", HIW "��ɽ����" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 290000);
        set("max_jing", 290000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fei" :),
                (: exert_function, "freeze" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),              
        }) );

        set_skill("dodge", 560);
        set_skill("parry", 560);
        set_skill("unarmed", 560);
        set_skill("hand", 560);
        set_skill("sword", 560);
        set_skill("yujian-shu", 560);
        set_skill("feilong-shou", 560);
        set_skill("zuixian-bu", 560);
        set_skill("force", 560);
        set_skill("bingxin-jue", 560);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "bingxin-jue");
        map_skill("dodge", "zuixian-bu");
        map_skill("parry", "yujian-shu");
        map_skill("sword", "yujian-shu");
        map_skill("unarmed", "feilong-shou");
        map_skill("hand", "feilong-shou");

        prepare_skill("hand", "feilong-shou");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/pangukai")->wear();
        carry_object(__DIR__"obj/chiyoujian")->wield();
        //carry_object("/kungfu/class/sky/obj/miji3");
        //set_temp("handing", carry_object("/kungfu/class/sky/obj/shenjiu"));
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = query_last_damage_from();

        if (objectp(ob) && ob->is_fighting(this_object()))
        {
                         if (arrayp(ob->query_team()))
                         {
                                 command("heng");
                                 command("say ʤ֮���䣡");
                                 set("qi", 290000);
                                 set("jing", 90000);
                                 set("neili", 35000);
                                 set("eff_qi", 290000);
                                 set("max_jing", 90000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 2)
             {
                      ob->set("sky12/floor", 3);
                 command("say �������ɣ�");
             }            
        }

        set("qi", 290000);
        set("jing", 90000);
        set("neili", 35000);
        set("eff_qi", 290000);
        set("max_jing", 90000);
        set("max_neili", 35000);

        this_object()->clear_condition();

        return;
}

// ��ѪС��1000����������������Э����æת��
void heart_beat()
{
        if (this_object()->query("qi") < 1000 || this_object()->query("eff_qi") < 1000)
        {
                die();
        }
        ::heart_beat(); 
        keep_heart_beat(); 
}
