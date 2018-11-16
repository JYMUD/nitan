#include <ansi.h>

inherit NPC;

mixed give_quest();

void create()
{
        set_name(HIY "��ԯ��" NOR, ({ "vin" }));
        set("long", HIY "    �������׻�ʥ�ۣ�������������ò�������ˡ��׻�Ӣ��ʷ����ɽ��ʦ��\n" NOR);

        set("gender", "����");
        set("age", 22);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 2000000);
        set("max_jing", 500000);
        set("max_neili", 300000);
        set("neili", 300000);
        set("jiali", 2000);
        set("combat_exp", 990000000);

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
                "��ԯ��"     : "��ԯ��Ҳ����е��𣿷�����",
                "������"     : "�����׻�Ӣ��ʷ������",
                "�ܷ�"       : "�����׻�Ӣ��ʷ������������Ա��",
                "��Ը"       : (: give_quest :),
                "�Ϲ�����"   :  "�����Ϲ�ʧ���������������",
                "����"       : "�����Ϲ�ʧ���������������",
                "ת��"       : "Ҫת���ȹ�����أ�",
                "�׻�Ӣ��ʷ"  : "�Ǻǣ����Ҳ���ʣ�",
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/yanhuangpao")->wear();
}

mixed give_quest()
{
        object me = this_player();
        string obj;
        
        if (me->query("sky12/floor") != 12)
        {
                command("say �ߣ��޳ܿ�ͽ��������ô���������ģ����ص���ȥ�ɣ�");
                me->move("/d/city/wumiao");
                me->unconcious();
                return "�ߣ�\n";
        }

        if (stringp(me->query("sky12/quest/obj")))
             return "�Ҳ����������Ѱ��" + me->query("sky12/quest/obj") + 
                    "�������Ķ��أ�\n";
        
        // Ѱ��һ���Ϲ�����     
        obj = ULTRA_QUEST_D->get_random_magic_item();
        
        command("smile");
        message_sort(HIW "\n$N" HIW "��$n" HIW "˵��������ǰ����ʧһ���Ϲ���"
                     "������Ի��" + HIR + obj + HIW "��������ܰ��Ұ����һ���"
                     "���ң��ұ㲻�������㣡\n" NOR, this_object(), me);
        
        me->set("sky12/quest/obj", obj);
        
  return 1;
}

int accept_object(object me, object ob)
{        
        string obj;
        
        if (! me->query("sky12/quest/obj"))
             return 0;

        obj = filter_color(ob->name());
        
        if (me->query("sky12/quest/obj") == obj)
        {
                if (ob->is_item_make() ||
                    ! ob->is_magic_item())
                {
                        command("heng");
                        command("say ������������ң�������");
                        me->unconcious();
                        return 1;
                }
                command("smile");
                if (me->query("sky12/floor") == 12)
                {
                          me->set("sky12/floor", 13);
                     command("say �ܺã��ܺã����¿�������ˣ�");
                }                

                destruct(ob);
                
                me->delete("sky12/quest");

                return 1;
        }
        else return 0;
                   
}

void unconcious()
{
        die();
}
