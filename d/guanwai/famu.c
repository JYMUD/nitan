// /guanwai/famu.c

#include <ansi.h>

inherit ROOM;

int start_work(object me, object ob);
varargs int end_working(object me, object passive);
int working(object me);
int coagent(object me);
int halt_working(object me, object who, int silent);

void create()
{
        set("short", "��ľ��");
        set("long", @LONG
������¹���������µ�һƬɭ�֣�����������Ĳ����
������ֱͦ�Σ������Ϻõ�ľ�ģ�����������￳��(famu)ľ�ϣ�
Ȼ���˵���ԭ����ٹ����ǽ�����լ������ش���ɽ���֣�ʱ��
�����͵�Ұ�޳�û��
LONG);
        set("exits", ([
                "southup" : __DIR__"luming",
        ]));
        set("outdoors", "changbai");
        setup();
}

void init()
{
        add_action("do_famu", "famu");
        if (find_call_out("call_beast") == -1)
                call_out("call_beast", random(60) + 20);
}

void call_beast()
{
        object ob;
        string beast;
        int n;

        remove_call_out("call_beast");

        if (sizeof(filter_array(all_inventory(), (: interactive :))) < 1)
                return;

        // Call out wovles when player is here
        call_out("call_beast", random(200) + 30);

        if (present("he xiong", this_object()) ||
            present("ye lang", this_object()))
                return;

        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
                n = 1 + random(4);
                beast = "/clone/quarry/lang2";
                break;
        case 8:
                n = 1;
                beast = "/clone/quarry/xiong";
                break;
        case 9:
                n = 1;
                beast = "/clone/quarry/xiong2";
                break;
        }

        message("vision", "ɽ������ͻȻ����" + chinese_number(n) +
                query("unit",get_object(beast)) + beast->name() +
                "\n", this_object());
        while (n--)
        {
                ob = new(beast);
                ob->move(this_object());
        }
}

int do_famu(string arg)
{
        object me;
        object ob;
        object old;
        object weapon;

        me = this_player();

        if (! arg || sscanf(arg, "with %s", arg) != 1)
                return notify_fail("��Ҫ��˭һ��ľ(famu with <sb>)��\n");

        ob = present(arg, this_object());
        if (! ob)
                return notify_fail("����û������˿��Ժ���һ��ľ��\n");

        if (me == ob)
                return notify_fail("���ǲ��Ǵ��Խ�ˮ...��Ҫ����\n");

        if (! living(ob))
                return notify_fail("����ôҲ�õ��˼��ѹ�����˵�ɣ�\n");

        if( query_temp("job/famu", ob) )
        {
                if (! ob->is_busy())
                        delete_temp("job/famu", ob);
                else
                        return notify_fail("�˼��������ڷ�ľ�ء�\n");
        }

        if( query_temp("job/famu", me) )
        {
                if (! me->is_busy())
                        delete_temp("job/famu", me);
                else
                        return notify_fail("�����ڲ������ڷ�ľ�\n");
        }

        if (ob->is_fighting())
                return notify_fail("�˼��������ڴ�ܣ����й������㣿\n");

        if (me->is_fighting())
                return notify_fail("�㻹�Ǵ����˼���˵�ɡ�\n");

        if (ob->is_busy())
                return notify_fail("�˼�������æ��û�������㡣\n");

        if (me->is_busy())
                return notify_fail("�㻹�ǵ��п�����˵�ɡ�\n");

        if( query("qi", ob)<200 )
                return notify_fail("�˼��������ӣ��������˰ɡ�\n");

        if( query("qi", me)<200 )
                return notify_fail("��������Ϣ����������������������˵�ɡ�\n");

        if (ob->query_str() < 30)
                return notify_fail("���˼��Ǹ�ģ���������ܸ������ػ���ˡ�\n");

        if (me->query_str() < 30)
                return notify_fail("��������������ɲ��������ػ\n");

        if( query_temp("pending/job_coagent", ob) == me )
        {
                delete_temp("pending/job_coagent", ob);
                return start_work(me, ob);
        }

        if( objectp(old=query_temp("pending/job_coagent", me)) )
        {
                if (old == ob)
                        return notify_fail("���Ѿ���������Ҫ���ˣ������˼һ�û�д�Ӧ��\n");

                tell_object(old, me->name() + "�ı������ⲻ�����һͬ��ľ�ˡ�\n");
                tell_object(me, "��ı������ⲻ���" + old->name() + "һͬ��ľ�ˡ�\n");
        }

        set_temp("pending/job_coagent", ob, me);
        message_vision("$N��$n������������ɣ�" + RANK_D->query_respect(ob) +
                       "������һͬ��ľ��Σ���\n", me, ob);
        tell_object(ob, YEL + me->name() + "������һͬ��ľ�������"
                    "Ը���һ���(famuwith"+query("id", me)+")�ɡ�\n"NOR);
        return 1;
}

int start_work(object me, object ob)
{
        object weapon, hand;
        object swap;

        hand=query_temp("handing", me);
        if (! objectp(hand) || ! hand->is_saw())
        {
                swap = me;
                me = ob;
                ob = swap;
                hand=query_temp("handing", me);
        }

        if (! objectp(hand) || ! hand->is_saw())
                return notify_fail("������˭��û���þ⣬��ô��ľ��\n");

        if( (!objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "axe") && 
            (!objectp(weapon=query_temp("weapon", ob)) || query("skill_type", weapon) != "axe") )
                return notify_fail("����û�и�ͷ�����ɲ��갡��\n");

        set_temp("job/famu", 1, me);
        set_temp("job/step", 1, me);
        set_temp("job/coagent", ob, me);
        set_temp("job/famu", 1, ob);
        set_temp("job/step", 1, ob);
        set_temp("job/coagent", me, ob);
        me->start_busy((: working :), (: halt_working :));
        ob->start_busy((: coagent :), (: halt_working :));
        tell_object(me, "���" + ob->name() + "��ʼ��ľ��\n");
        tell_object(ob, "���" + me->name() + "��ʼ��ľ��\n");
        return 1;
}

private varargs int end_working(object me, object passive)
{
        object coagent;

        if( !query_temp("job/famu", me) )
                return 0;

        coagent=query_temp("job/coagent", me);
        me->interrupt_me(me, 1);
        delete_temp("job", me);
        if (objectp(passive))
        {
                message_vision("$n�����ˣ�$NҲֻ�ø���ͣ��������\n",
                               me, passive);
        }
        if (coagent) end_working(coagent, me);
        return 0;
}

int working(object me)
{
        object ob;
        object coagent;
        object weapon;
        object wood;
        string msg;
        string gmsg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if( !objectp(coagent=query_temp("job/coagent", me)) )
        {
                message_vision("��æ�������ˣ�$Nֻ��ͣ�ֲ����ˡ�\n", me);
                return end_working(me);
        }

        if (! living(me))
        {
                return end_working(me);
        }

        ob=query_temp("handing", me);
        if (! objectp(ob) || ! ob->is_saw())
        {
                message_vision("��û�ˣ�$Nͣ�ֲ����ˡ�\n", me);
                return end_working(me);
        }

        finish = 0;
        switch(query_temp("job/step", me) )
        {
        case 1:
                me->receive_damage("qi", 20);
                msg = "$N���ܿ�����ѡ����һ���Ϻõ�������";
                break;
        case 2:
                me->receive_damage("qi", 20);
                msg = "$N��$n�ߵ������ԣ�������һ�£�Ȼ����" + ob->name() +
                      "��ʼ�������⡣";
                break;
        case 3:
                me->receive_damage("qi", 30);
                msg = "��֨��֨�¡���ľм����������˲���ľм��";
                break;
        case 4:
                me->receive_damage("qi", 30);
                msg = "����֨��֨����$N��$n�������⡣";
                break;
        case 5:
                me->receive_damage("qi", 30);
                msg = "��֨��֨�¡������ϵ�ľм��Խ��Խ�࣬��ҲԽ��Խ�";
                break;
        case 6:
                me->receive_damage("qi", 30);
                msg = "����֨��֨����$N��$n�������⡣";
                break;
        case 7:
                me->receive_damage("qi", 30);
                msg = "��֨��֨�¡�����Ȼ����������һ����������Щҡ�Ρ�";
                break;
        case 8:
                if( objectp(weapon=query_temp("weapon", me)) && 
                    query("skill_type", weapon) == "axe" )
                {
                        msg = "$N�ڰ��֣���$n������������ȥ���ǡ������ѡ��Ŀ���";
                        break;
                }
                if( objectp(weapon=query_temp("weapon", coagent)) && 
                    query("skill_type", weapon) == "axe" )
                {
                        msg = "$n�ڰ��֣���$N������������ȥ���ǡ������ѡ��Ŀ���";
                        break;
                }
                
                message_vision("�⵽������ϣ�ȴû�ҵ���ͷ��$N��$n"
                               "�ɵ��۾���ֻ��ͣ�֡�\n", me, coagent);
                return end_working(me);
        default:
                msg = "������֨ѽ֨ѽ���ĵ���������$N��$n��æ������";
                finish = 1;
                break;
        }
        msg += "\n";

        // send message out
        gmsg = replace_string(msg, "$N", "��");
        gmsg = replace_string(gmsg, "$n", coagent->name());
        tell_object(me, gmsg);
        gmsg = replace_string(msg, "$n", "��");
        gmsg = replace_string(gmsg, "$N", me->name());
        tell_object(coagent, gmsg);

        if (finish)
        {
                delete_temp("job", me);
                delete_temp("job", coagent);
                coagent->interrupt_me(coagent, 1);

                wood = new("/d/guanwai/obj/largewood");
                wood->move(this_object());

                if (me->query_dex() / 2 + random(me->query_dex() / 3) < 12)
                {
                        message_vision("������Ȼ���أ�$N���ǲ���һ������"
                                       "����ž����һ�°�$Nѹ�˸�����ʵʵ��\n", me);
                        me->unconcious();
                } else
                if (coagent->query_dex() / 2 + random(coagent->query_dex() / 3) < 12)
                {
                        message_vision("������Ȼ���أ�$N���ǲ���һ������"
                                       "����ž����һ�°�$Nѹ�˸�����ʵʵ��\n", coagent);
                        coagent->unconcious();
                } else
                {
                        message_vision("������Ȼ���أ�$N��$nĨ��Ĩͷ"
                                       "�ϵĺ�������һЦ��\n", me, coagent);

                        if (wood->move(me))
                        {
                                message_vision(HIC "$N" HIC "���ˡ���һ������$n" HIC
                                               "�İ����°�" + wood->name() + HIC
                                               "����������\n" NOR, me, coagent);
                        } else
                        if (wood->move(coagent))
                        {
                                message_vision(HIC "$n" HIC "���ˡ���һ������$N" HIC
                                               "�İ����°�" + wood->name() + HIC
                                               "����������\n" NOR, me, coagent);
                        } else
                        {
                                message_vision("$N��$n��ȥ���˵�ľ�ϣ�������̫"
                                               "�أ�ֻ���ȷ��ڵ��ϡ�\n",
                                               me, coagent);
                        }
                }

                if( query("combat_exp", me) >= 500000 && 
                    query("combat_exp", me)<1500000 )
                {
                        // bonus to me
                        b = 150 + random(100);
                        GIFT_D->work_bonus(me, ([ "exp" : b, "pot" : b / 3, "prompt" : "ͨ����ζ����������ѧ������ֽ�һ��" ]));
                        me->improve_skill("force", (b + 3) / 4);
                }

                if( query("combat_exp", coagent) >= 500000 && 
                    query("combat_exp", coagent)<1500000 )
                {
                        // bonus to coagent
                        b = 150 + random(100);
                        GIFT_D->work_bonus(coagent, ([ "exp" : b, "pot" : b / 3, "prompt" : "ͨ����ζ����������ѧ������ֽ�һ��" ]));
                        coagent->improve_skill("force", (b + 3) / 4);
                }

                return 0;
        } else
                addn_temp("job/step", 1, me);

        return 1;
}

int coagent(object me)
{
        return 1;
}

int halt_working(object me, object who, int silent)
{
        if( !query_temp("job/famu", me) )
                return 1;

        if (! silent)
                message_vision("$N̾�˿����������������ˣ���"
                               "��������磡��\n", me);
        end_working(me);
        return 1;
}
