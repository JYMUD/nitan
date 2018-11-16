// long.c

#include <ansi.h>
inherit NPC;

int ask_zhou();
int ask_back();

void create()
{
        set_name("������", ({ "long daozhu", "long" }));
        set("title", HIR "���͵�����" NOR);
        set("gender", "����");
        set("age", 60);
        set("long",
              "���Ǹ���������ʮ����ĺ��ӣ���üȫ�棬��ɫ������һϮ���ۣ���Ȼͦ����\n"
        );

        set_temp("apply/attack", 600);
        set_temp("apply/armor", 1500);
        set_temp("apply/damage", 800);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/dodge", 600);
        set_temp("apply/parry", 600);

        set("qi", 9000);
        set("max_qi", 9000);
        set("jing", 20000);
        set("max_jing", 20000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 250);
        set("combat_exp", 5000000);
        set("score", 20000000);

        set_skill("force", 300);
        set_skill("taixuan-gong", 300);
        set_skill("dodge", 300);
        set_skill("taixuan-gong", 300);
        set_skill("unarmed", 300);
        set_skill("taixuan-gong", 300);
        set_skill("parry", 300);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "unarmed.taixuan" :),
        }) );

        set("chat_chance", 5);
        set("inquiry", ([
                "������" : (: ask_zhou :),
                "���͵�" : "��������Һ�ľ�ֵ������з��ֵġ�",
                "back"   : (: ask_back :),
                "�뵺"   : (: ask_back :),
        ]));

        create_family("���͵�", 0, "����");
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting() && random(3) == 1)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        if( query("combat_exp", ob)<10000 )
              say("������̧ͷ������һ�ۣ�˵������������ǳ����\n");
        else
        if( query("combat_exp", ob)<100000 )
              say("�����������һ�ۣ�˵������δ����򡣡�\n");

        return;
}

int ask_zhou()
{
        message_sort("$N��$n˵�������Ǳ������еĶ���������Ҫ"
                     "��һζ���ϳ����Ǹ��Ĳݡ����ɣ�Ҫ������"
                     "Ч�������������ֲ�ÿʮ��ſ�һ�λ�����"
                     "��һ���˺��ѵõ��ģ�С�ֵ���Ҫ��Ҫ����"
                     "��Ե���ˣ���\n", this_object(), this_player());
        return 1;
}

int ask_back()
{
        object me;

        me = this_player();
        if( query("combat_exp", me) >= 500000 )
        {
         message_vision("$N����Ŀ���һ���$n���ŵ�������û���ȣ����鶼��50�򣬻�Ҫ�Ұ��㣿��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N̾�˿�������������Ȼ������������������������ɣ���\n",
                       this_object());
        me->move("/d/xiakedao/haitan");
        message("vision", "��������" + me->name() + "���˹�����˵�˼��仰����������ȥ�ˡ�\n",
                environment(me), me);
        tell_object(me, HIR "�������㵽��̲�����������������"
                        "�ú����ù��򣬱����鷳���Ǽҵ�������\n" NOR
                        "����æ���˼���Ц�������Ĳ�������ȥ��\n");
        return 1;
}

int accept_object(object who, object ob)
{
        object zhou;

        // û���й�����
        if( !query("story/labazhou", who) )
                return 0;

        // ����ͭ��
        if( (query("id", ob) != "e pai") && (query("id", ob) != "shan pai") )
                return 0;

        // ����
        zhou = new("/d/xiakedao/obj/labazhou");
        if (zhou)
                zhou->move(who, 1);

        message_vision("$N��$n��������������������ұ�����֮ʿ���в��棬���³��ȺȰɣ���\n",
                       this_object(), who);
        destruct(ob);
        return 1;
}

/*
int accept_object(object who, object ob)
{
        object obn;

        if( query("id", ob) != "shanebu" && query("id", ob) != "fuxincao" )
        {
                message_vision("\n������ҡͷ�����ⲻ������Ҫ��ѽ��\n",who);
                return 0;
        }
        if( query("id", ob) == "shanebu" )
        {
                if( random(query("kar", who)) <= 25 )
                {
                        message_vision("������ҡͷ�����ҿ�С�ֵܽ����ڴ���Ե��\n",who);
                        return 1;
                }
                else
                {
                        remove_call_out("destroy");
                        call_out("destroy", 1, who, ob);

                        if(query_temp("cao"))
                        {
                                message_vision("\n�������������Ʒ��񲾣���ϲ������ϲ��λС�ֵ���!\n",who);
                                obn=new("/clone/medicine/nostrum/labazhou");
                                obn->move(who);
                                delete_temp("bu");
                                delete_temp("cao");
                                return 1;
                        }
                        else if(query_temp("bu"))
                        {
                                message_vision("\n�������������Ʒ��񲾣���$Nҡͷ�������Ʒ��������ˡ�\n",who);
                                return 0;
                        }
                        else
                        {
                                message("vision","�������������Ʒ��񲾣���ϲ��������ֻ��Ĳ��ˡ�\n",environment(who));
                                set_temp("bu",1);
                                return 1;
                        }
                }
        }
        if( query("id", ob) == "fuxincao" )
        {
                if( random(query("kar", who)) <= 25 )
                {
                        message_vision("������ҡͷ�����ҿ�С�ֵܽ����ڴ���Ե��\n",who);
                        return 1;
                }
                else
                {
                        remove_call_out("destroy");
                        call_out("destroy", 1, who, ob);

                        if(query_temp("bu"))
                        {
                                message_vision("\n���������Ǹ��Ĳݣ���ϲ������ϲ��λС�ֵ���!\n",who);
                                obn=new("/clone/medicine/nostrum/labazhou");
                                obn->move(who);
                                delete_temp("cao");
                                delete_temp("bu");
                                return 1;
                        }
                        else if(query_temp("cao"))
                        {
                                message_vision("\n���������Ǹ��Ĳݣ���$Nҡͷ�������Ĳ����Ѿ����ˡ�\n",who);
                                return 0;
                        }
                        else
                        {
                                message("vision","�������������Ĳݣ���ϲ��������ֻ�����Ʒ����ˡ�\n",environment(who));
                                set_temp("cao",1);
                                return 1;
                        }
                }
        }
        return 1;
}
*/

