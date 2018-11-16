// chuniang.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  do_cook(string arg);
int  cooking(object me);
int  halt_cooking(object me);

void create()
{
        set_name("����", ({"chu niang", "chu", "niang"}));
        set("long", @LONG
����һ������ȥ����ͨͨ�ĳ���������µ��ڳ����ղ�������һ˫
�ֲڵĴ��֣������Χȹ��ò�����ˣ����������ķ������ȴ�Ǵ���
һ����Ϊ���ƺ�ʮ�ְ�������������һ������
LONG );
        set("gender", "Ů��");
        set("age", 35);
        set("no_get", 1);
        set("attitude", "friendly");

        set("inquiry",([
                "job" : (: ask_job :),
                "����" : (: ask_job :),
        ]));

        set("age", 30);

        set("str", 21);
        set("int", 22);
        set("con", 30);
        set("dex", 21);

        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("dodge", 50);
        set_skill("cooking", 200);
        set_skill("chuancai-jiyi", 200);
        set_skill("unarmed", 50);

        set("vendor_goods", ({
                "/clone/misc/cailiao",
        }));

        setup();
}

void init()
{
        add_action("do_cook", "cook");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query("gender", me) != "Ů��" )
                return "��һ������ү�ǣ�����ʲô�˰���";

        if( query("combat_exp", me)<200000 )
                return "�ϣ�����㱾�°����˵ö�����ô��";

        if( query("jing", me)<100 )
                return "�㻹����Ϣ����ɣ�С�İ������ۿ��ˣ�";

        if( query("combat_exp", me)>500000 )
                return "��λŮ�������ⲻ����ɱС�����㻹��ȥǰ���òͰɣ��������Ͼͺã�";

        if (me->query_skill("cooking") < 60)
                return "��ĳ���������ô������ܰ��ң�";

        if (me->query_skill_mapped("cooking") != "chuancai-jiyi")
                return "��˵��֪��֪�����Ŀ��˿ɶ��ǳԴ��˵ģ������㴨�˵Ļ����˵��";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/cook", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "�����" + obs[0]->name() + "�أ��㻹�Ǳ�����ˡ�";

        set_temp("job/cook", 1, me);
        return "�ðɣ���Ͱ��ҳ���(cook)�ɣ������������̨���Ǳߡ�";
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/����", ob)<1 )
                return 0;

        if (skill != "cooking" && skill != "chuancai-jiyi")
        {
                command("say ���ס...�ҿ�ֻ�������շ���");
                return -1;
        }

        addn_temp("mark/����", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();

        if( query_temp("mark/����", who)<1 )
                set_temp("mark/����", 0, who);

        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                message_vision("����ͬ��ָ��$NһЩ���ڳ��˵ĳ�ʶ�ͼ��ɡ�\n", who);
                addn_temp("mark/����", ob->value()/50, who);
                destruct(ob);
                return 1;
        }

        command("say ��˵���˶Դ�������ûʲô�ã���Ҳ���ܰװ׽���"
                "���������������������ʮ����ͯ�����ۣ�");
        return 0;
}

int do_cook(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if( !query_temp("job/cook", me) )
        {
                tell_object(me, "����ȵ�����Ҫ��ʲô����Ҫ�����ң���æ���أ�\n");
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "cooking" :), me),
                       bind((: call_other, __FILE__, "halt_cooking" :), me));
        tell_object(me, "�������߲ˣ��ߵ�һ�����£���ʼ��ˡ�\n");
        return 1;
}

int cooking(object me)
{
        string msg;
        int finish;
        int gain_exp, gain_pot, gain_money;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 10);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N�����˲�๻�ˣ�վ�������ߵ�ˮ��߿�ʼϴ�ˡ�";
                break;
        case 2:
                msg = "��----��$N��ˮ���е���ˮ��������Ҳϴ�ɾ��ˡ�";
                break;
        case 3:
                msg = "$N�ߵ���̨ǰ��ʼ�вˣ���----��-----��";
                break;
        case 4:
        case 6:
                msg = "$N���͵�����У������вˡ�";
                break;
        case 5:
                msg = "�����ˣ�ð���������̣�$N���кõĲ˵�����У���------";
                break;
        case 7:
                msg = "$N���Ϸ������еĲˣ������ģ�һ����ζɢ��������";
                break;
        default:
                msg = "$N�ڹ��м�����ϣ��ַ����˼��£������õĲ˲������У��ø�$n��";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                msg += "$n����$N���Ĳˣ��ּ�����Ƭ���˳�������ĵ��ͷ"
                       "���Ǹ���ı��꣡�������������ѧ�㳴�˼�����\n";
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                gain_money = 60 + random(60);
                addn_temp("mark/����", random(30), me);
                me->improve_skill("cooking", 10 + random(10));

                // �����ľ���Ϊ10��20����������϶ࣩ�� moneyΪ100�ӳ��˼�
                // ���ĵȼ�ȡ��������϶ࣩ��Ǳ��Ϊ������3�㣬��Ҫ�����Լ�
                // silverΪ����
                ob = new("/clone/money/coin");
                ob->set_amount(gain_money);
                ob->move(me, 1);

        }

        msg = replace_string(msg, "$N", "��");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if( query("combat_exp", me) >= 200000 )
                {
                        write(MAG "������ԼԼ�ķ��ֳ��˾�Ȼ���书��һЩ��֮ͨ�����������\n" NOR);
                        gain_exp = 50 + random(150);
                        gain_pot = (gain_exp + 2) / 3;
                        GIFT_D->work_bonus(me, ([ "exp" : gain_exp, "pot" : gain_pot ]));
                }
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_cooking(object me)
{
        message_vision("$N������������Ť��Ť��̾����"
                       "��Ҳ̫���ˣ��һ���ȥ���������ɣ�\n", me);
        delete_temp("job/cook", me);
        delete_temp("job/step", me);
        return 1;
}
