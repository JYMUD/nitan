// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        if (random(2))
                set_name(HIM "����" NOR, ({ "die xian", "die", "xian" }));
        else
                set_name(HIM "�ʵ�����" NOR, ({ "caidie xianzi", "caidie", "xianzi" }));
                
        set("long", HIM "����Ǵ�˵�еĵ��ɣ�һ����´�磬���ϻ���һ�Բ�ɫ�ĳ����ò�����ɸ�ʤ���֡�\n" NOR);

        set("gender", "Ů��");
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
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "�����걾"   :   "���õĺ����걾��������С�����ˣ�����������Ҫ������ܷ���æ��\n",
                "�����ɵ�"               :   "�ⲻ��������ĵط����ҿ��㻹�ǿ��߰ɡ�\n",
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void unconcious()
{
        die();
}

int accept_object(object me, object obj)
{                                
        object ob;
        
        if (obj->query("id") == "hudie biaoben" &&
            base_name(obj) == "/d/penglai/obj/biaoben")
        {
                command("nod");
                message_vision(HIC "$N" HIC "�ӹ�" + obj->name() + HIC "������Ŀǰ������Ҫ�����лл ����\n" NOR, this_object());
                message_vision(NOR + CYN "\n$N" NOR "�ó�ʮ��������" + me->name() + NOR + CYN "��\n" NOR, this_object(), me);
                ob = new("/clone/money/silver");
                ob->set_amount(10);
                ob->move(me, 1);
                destruct(obj);
                return 1;
        }
        return 0;        

}