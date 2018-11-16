#include <ansi.h>

inherit NPC;

void create()
{
            set_name("һ�ƴ�ʦ", ({ "yideng dashi", "yideng", "dashi" }));
            set("long", @LONG
һ�ƴ�ʦ�˽������˳ơ���а�������ϵ۱�ؤ����
���ϵ۶λ�ү������ƾ�Ŷ��ϡ�һ��ָ����������
�֣�������֡���ȴ������ʱ��һ�α��������Ϊ
ɮ��֮��󳹴��򣬳�Ϊһλ�õ���ɮ��
LONG );
            set("title", "�������λ�ʵ�");
            set("nickname", HIY "�ϵ�" NOR);
            set("gender", "����");
            set("age", 71);
        set("shen_type", 1);
            set("attitude", "friendly");

            set("str", 33);
            set("int", 35);
            set("con", 38);
            set("dex", 33);

            set("qi", 300000);
            set("max_qi", 300000);
            set("jing", 100000);
            set("max_jing", 100000);
            set("neili", 35000);
            set("max_neili", 35000);
            set("jiali", 300);
            set("combat_exp", 900000000);
            set("score", 500000);

        set_skill("force", 650);
        set_skill("xiantian-gong", 650);
        set_skill("duanshi-xinfa", 650);
        set_skill("kurong-changong", 650);
        set_skill("dodge", 650);
        set_skill("tiannan-bu", 650);
        set_skill("cuff", 650);
        set_skill("jinyu-quan", 650);
        set_skill("strike", 650);
        set_skill("wuluo-zhang", 650);
        set_skill("sword", 650);
        set_skill("staff", 650);
        set_skill("duanjia-jian", 650);
        set_skill("finger", 650);
        set_skill("qiantian-zhi", 650);
        set_skill("sun-finger", 650);
        set_skill("parry", 650);
        set_skill("jingluo-xue", 650);
        set_skill("buddhism", 650);
        set_skill("literate", 650);
        set_skill("sanscrit", 650);
        set_skill("martial-cognize", 650);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("���ϻ���", 11, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.jian" :),
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),                  
        }));

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

            setup();
            carry_object("/clone/cloth/seng-cloth")->wear();
}

void start_kill(object guard, object ob)
{
        if (! objectp(guard) || ! objectp(ob))return;

        guard->kill_ob(ob);        
}

void delay_kill(object guard, object ob)
{
        remove_call_out("start_kill");
        call_out("start_kill", 2, guard, ob);
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard1 = present ("hong qigong", where);
        object guard2 = present ("huang yaoshi", where);
        object guard3 = present ("ouyang feng", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard1 && ! guard1->is_fighting())delay_kill(guard1, ob);
        if (guard2 && ! guard2->is_fighting())delay_kill(guard2, ob);
        if (guard3 && ! guard3->is_fighting())delay_kill(guard3, ob);
        
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
             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
        }

        set("qi", 300000);
        set("jing", 200000);
        set("neili", 35000);
        set("eff_qi", 300000);
        set("max_jing", 100000);
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
