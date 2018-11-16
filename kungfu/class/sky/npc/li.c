#include <ansi.h>

inherit NPC;

void create()
{
        set_name("��Ѱ��", ({ "li xunhuan", "li", "xunhuan"}));
        set("long", "    һ�����Ű������������ӣ����ε�����\n" 
                    "����Ѫɫ���ƺ����ɫ���ȶ��԰ס�������\n"
                    "����һ��С�������������һ��ľ�ˡ���Χ\n"
                    "������һ�����·𶼿�������\n"); 
        set("nickname", HIR "С��̽��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 34);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "��Ѱ�������̾�˿�����\n" NOR,
                CYN "��Ѱ�������ص�������е�ľż��\n" NOR,
                CYN "��Ѱ�������˼�����\n" NOR,
                CYN "��Ѱ�������ȡ��ȡ���\n" NOR,
        }));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "throwing.fei" :),
                (: perform_action, "dodge.guiyuan" :),
                (: perform_action, "dodge.guiyuan" :),
                (: perform_action, "dodge.guiyuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),             
        }) );

        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("unarmed", 350);
        set_skill("throwing", 350);
        set_skill("xiaoli-feidao", 350);
        set_skill("changquan", 350);
        set_skill("shexing-lifan", 350);
        set_skill("force", 350);
        set_skill("yijinjing", 350);
        set_skill("literate", 250);
        set_skill("martial-cognize", 400);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "changquan");
        map_skill("throwing", "xiaoli-feidao");
        map_skill("unarmed", "changquan");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/renou");
        //carry_object("/kungfu/class/sky/obj/tianxiadan");
        set_temp("handing", carry_object(__DIR__"obj/feidao"));
        add_money("gold", 20);
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
                                 set("qi", 30000);
                                 set("jing", 30000);
                                 set("neili", 35000);
                                 set("eff_qi", 30000);
                         set("max_jing", 30000);
                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());

             if (! ob->query("sky12/floor"))
             {
                      ob->set("sky12/floor", 1);
                 command("say ���ˣ���������أ�����Խ�������ˣ�");
             }
        }

        set("qi", 30000);
        set("jing", 30000);
        set("neili", 35000);
        set("eff_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 35000);

        this_object()->clear_condition();

                if (! query_temp("handing") && random(5) == 1)                
                        set_temp("handing", carry_object(__DIR__"obj/feidao"));

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
