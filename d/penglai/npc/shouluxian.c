// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "��·����" NOR, ({ "shoulu xian", "shoulu", "xian" }));

        set("long", HIY "�����ػ���ɽ·�ڵ����ˣ�Ҫ������ɽ�ǵ���·���˵�ָ�����ɡ�\n" NOR);

        set("gender", "����");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("sword", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "�����ɵ�"               :   "�ⲻ��������ĵط����ҿ��㻹�ǿ��߰ɡ�\n",
                "��ɽ���"               :   "�Ǻǣ�������ܸ���һƿ��÷�ƣ��ұ�ָ����������ڡ�\n",
                "��÷��"                 :   "�㲻֪��ô���⵺�����˶����ȣ��������Ʒ���ֻ�оƽ���֪��������������",
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void init()
{
        object me = this_player();
        
        if (objectp(present("penglai qingmeijiu", me)))
                command("say ����~~����˭����÷�ƿ���ó����ñ�����Ʒ��Ʒ����");
}

void unconcious()
{
        die();
}

int accept_object(object me, object obj)
{                        
        
        if (me->query("penglai/nanshan_quest/ok"))
        {
                command("hehe");
                return 0;
        }
        
        if (obj->query("id") == "penglai qingmeijiu" &&
            base_name(obj) == "/d/penglai/obj/qingmeijiu")
        {
                command("wa");
                message_vision(HIC "$N" HIC "�ӹ�" + obj->name() + HIC "��һ�ڱ���˸����� ����\n" NOR, this_object());
                command("haha");
                command("say �ã�ʵ���Ǻ�~~~~");
                command("say ��Ȼ����˱����˵ľ�񫣬������ɽ�ķ�������Ȼ��̸��� ����");
                message_vision("\n$N" NOR "����$n" NOR "����˽��ƺ��ڴ���ʲô�ھ���\n\n" NOR, this_object(), me);
                tell_object(me, HIG "��·�����������˵����#%&$#%@%&%$&#$%@#@$\n" NOR);
                command("say ��ɼǺ��ˣ�����ɽ�ķ������������档");
                me->set("penglai/nanshan_quest/ok", 1);
                destruct(obj);
                return 1;
        }
        else
        {
                command("say ������ֻҪ��÷�ƣ�����ʲô����Ҫ��");
                return 0;
        }        

}