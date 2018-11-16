// shutong.c ��ͯ

#include <ansi.h>

inherit NPC;

string ask_job();
int  do_copy(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("��ͯ", ({ "shu tong", "tong" }));
        set("long", "������������ߵ�С��ͯ������ȥ��ͻ�С��\n");
        set("gender", "����");
        set("age", 15);
        set("no_get", 1);
        set_skill("literate", 50);

        set("combat_exp", 1000);
        set("inquiry", ([
                "����" : "�������������ɣ�������ɲ��ܡ�",
                "����" : (: ask_job :),
                "����" : (: ask_job :),
                "job"  : (: ask_job :),
                "��"   : "�����������úܡ�",
                "����" : "�裿�ҿ�û��������ѽ��",
        ]));

        setup();
}

void init()
{
        add_action("do_copy", "copy");
}

int accept_object(object who, object ob)
{
        command("say ����˵�ˣ��޹�����»���Ҳ���Ҫ��Ķ�����");
        return 0;
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/copy", me) )
                return "���㳭�����㳭���ˣ�";

        if( query("combat_exp", me)<1200 )
                return "��Ȼ������ֻ�ǳ����飬�����㾭��"
                       "̫�������å���ҿɲ��ã�";

        if( query("combat_exp", me)>8000 )
                return "�����㻹�Ǳ����ˣ��ҿɲ���������ܡ�";

        if( query("qi", me)<20 )
                return "�ҿ�����ɫ���а�����Ъ����ɣ��ҿɲ��볭�鳭����������";

        if( query("jing", me)<10 )
                return "�ҿ��㾫���а����ܳ�������ô��";

        if (me->query_int() < 25 && me->query_skill("literate", 1) < 20)
                return "��������������ôһ��㲻̫����ѽ��";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/copy", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "�����Ѿ���" + obs[0]->name() + "�ڸɻ��ˣ���ȵȰɡ�";

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
                message_vision("$N����ë�ʣ�����պī��������$n������"
                               "���а��У�ǧ����ķ��ı�����Ҫ��ʰ�ء�\n",
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
                object ob;
                msg += "$n����$N��д���飬�����������ã�����"
                       "ǿ���ˡ�ŵ��������������ı��꣡�����\n"
                       "����������ѧ���Ļ�����\n";
                delete_temp("job/copy", me);
                delete_temp("job/step", me);

                b = 5 + random(4);
                addn_temp("mark/��", 20, me);
                addn("combat_exp", b, me);
                me->improve_potential((b + 2) / 3);

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
                if (b > 0)
                {
                        tell_object(me, HIC "\n������" +
                                    chinese_number(b) +
                                    "�㾭���" +
                                    chinese_number((b + 2) / 3) +
                                    "��Ǳ�ܡ�\n\n" NOR);
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