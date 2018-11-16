// zhu.c ����

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_buy();
string ask_job();
int  do_copy(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("����", ({ "zhu xi", "zhu" }));
        set("long", "����������Ϊ������һ����ѧ�ң�����"
                    "���īˮ�Ⱥ���Ҫ�\n");
        set("gender", "����");
        set("age", 65);
        set("no_get", 1);
        set_skill("literate", 20000);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        set("inquiry", ([
                "����" : (: ask_buy :),
                "����" : (: ask_job :),
                "����" : (: ask_job :),
                "job"  : (: ask_job :),
                "��"   : "�����鵽��ʱ�����١�",
                "����" : "�裿�㲻���ҵ��������㣿�ߣ�",
        ]));
        set("vendor_goods", ({
                "/clone/book/lbook1",
                "/clone/book/lbook2",
                "/clone/book/lbook3"
        }));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "����˵��������֮�£�Ī������������֮����Ī��������\n",
                "����˵���������ˣ�С�������ɣ����������δ������֮��\n",
                "����˵������ѧ֮�����������¡���������ֹ�����ơ� \n",
                "����˵����������֪���������ģ�������ң��ι�ƽ���¡�\n",
        }) );
}

void init()
{
        add_action("do_copy", "copy");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/��", ob) )
                return 0;
        addn_temp("mark/��", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();

        if( !query_temp("mark/��", who) )
                set_temp("mark/��", 0, who);

        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                message_vision("����ͬ��ָ��$NһЩ����д�ֵ����⡣\n", who);
                addn_temp("mark/��", ob->value()/50, who);
                destruct(ob);
                return 1;
        }

        command("say �����ѧ�棬����Ҫ��ʮ��������");
        return 0;
}

string ask_buy()
{
        return "������в��ٶ����˱ض�����Ӵ!\n";
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/copy", me) )
                return "���㳭�����㳭���ˣ�";

        if( query("combat_exp", me)<20000 )
                return "��Ȼ������ֻ�ǳ����飬������ս��������ô�Ҫ"
                       "����С��å��������ô�죿";

        if( query("combat_exp", me)>100000 )
                return "������Ҳ�����飿�����������ˣ����߰���";

        if( query("qi", me)<20 )
                return "�ҿ�����ɫ���а�����Ъ����ɣ��ҿɲ��볭�鳭����������";

        if( query("jing", me)<10 )
                return "�ҿ��㾫���а����ܳ�������ô��";

        if (me->query_int() < 25 && me->query_skill("literate", 1) < 20)
                return "��˵��������ô����Ҳ�����飿";

        if (! interactive(me))
                return "...";

/*
        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/copy", $1) &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "�����Ѿ���" + obs[0]->name() + "�ڸɻ��ˣ���ȵȰɡ�";
*/

        set_temp("job/copy", 1, me);
        return "�ã���Ͱ��ҳ���(copy)�ɣ���īֽ���������";
}

int do_copy(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if( !query_temp("job/copy", me) )
        {
                message_vision("$N����ë�ʣ�����պī��������$n��ȵ���"
                               "���ҷ��£����Ҷ��ķ��ı���\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "�㿪ʼ������\n");
        return 1;
}

int working(object me)
{
        string msg;
        object ob;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/copy", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 1);
        me->receive_damage("qi", 2);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N�ù���̨����������ī��";
                break;
        case 2:
                msg = "$N����īĥ�ò���ˣ�����ë�ʣ����������������";
                break;
        case 3:
                msg = "$N��պī֭���������飬̯��ֽ�ţ���ʼ��д��";
                break;
        case 4:
        case 6:
                msg = "$N�۾�����ĳ�д�鼮��";
                break;
        case 5:
                msg = "$Nպ��պī��������ϸ�س�д��";
        case 7:
                msg = "$N���Ϸ������鼮��ֽ��Խ��Խ��";
                break;
        default:
                msg = "$N���鼮���ã���ֽ��ī���ɣ�װ���ɲᣬ�ݸ�$n��";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n����$N��д���飬����������У����ӿɽ̣�"
                       "���Ǹ���ı��꣡�������������ѧ���Ļ���\n";
                delete_temp("job/copy", me);
                delete_temp("job/step", me);

                b = 800 + random(100);
                addn_temp("mark/��", 20, me);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                if (me->query_skill("literate", 1) < 100)
                        me->improve_skill("literate", (b + 1) / 2);

                ob = new("/clone/money/coin");
                ob->set_amount(50);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "��");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/head", me) && random(10) == 1) 
                {
                       message_vision("$n��$N�ٺ�һЦ�������ɵò������е�"
                                      "��˼�������֮ף��ͷ�����������͸��������ɡ�\n",
                                      me, this_object());
                       ob = new("/clone/goods/zhufu_head"); 
                       ob->move(me, 1); 
                       tell_object(me, HIM "\n������һ��" + ob->name() + HIM "��\n" NOR); 
                       set("zhufu_mod/head", 1, me); 
                }
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N�����еı�īֽ�ⶪ��һ�ԣ���ɧ����"
                       "ʲôѽ�������Ͳ����˸ɵĻ\n", me);
        delete_temp("job/copy", me);
        delete_temp("job/step", me);
        return 1;
}
