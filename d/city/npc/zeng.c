// zeng.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("����", ({ "zeng rou", "zeng", "rou" }));
        set("gender", "Ů��");
        set("age", 16);
        set("per", 25);
        set("con", 25);
        set("int", 25);
        set("dex", 25);
        set("str", 25);
        set("long",
"����Τ��ү��֪���ڼ�����С檣������￪�������̣���Щ��֪��
�������·�������˵�Ƕ���Τ��ү�ӹ���Ū�����Ľ�Ʒ������ô˵��
����������\n");
        set_skill("unarmed", 60);
        set_skill("changquan", 60);
        map_skill("unarmed", "changquan");
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"cloth/belt",
                __DIR__"cloth/boots",
                __DIR__"cloth/bu-shoes",
                __DIR__"cloth/cloth",
                __DIR__"cloth/color-dress",
                __DIR__"cloth/fu-cloth",
                __DIR__"cloth/gui-dress",
                __DIR__"cloth/hat",
                __DIR__"cloth/jade-belt",
                __DIR__"cloth/liu-dress",
                __DIR__"cloth/marry-dress",
                __DIR__"cloth/mini-dress",
                __DIR__"cloth/moon-dress",
                __DIR__"cloth/pink-dress",
                __DIR__"cloth/qi-dress",
                __DIR__"cloth/red-dress",
                __DIR__"cloth/scarf",
                __DIR__"cloth/sha-dress",
                __DIR__"cloth/shoes",
                __DIR__"cloth/xian-cloth",
                __DIR__"cloth/xiu-cloth",
                __DIR__"cloth/xiu-scarf",
                __DIR__"cloth/yan-dress",
                __DIR__"cloth/zi-dress",
        }));

        set("inquiry", ([
            "����" : (: ask_job :),
            "job"  : (: ask_job :),
        ]));

        setup();
        carry_object(__DIR__"cloth/feature")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sew", "sew");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/sew", me) )
                return "���������·���Ū����ô��";

        if( query("gender", me) != "Ů��" )
                return "��Ů���ӼҵĻ���Ҳ���ɣ�";

        if( query("combat_exp", me)<3000 )
                return "������������ɻ��һ����е㲻���ġ�";

        if( query("combat_exp", me)>300000 )
                return "�������ã������ǿ���ʲô�õ��Լ�ѡ���ɣ������ɻ�Ҳ̫ί���ˣ�";

        if( query("qi", me)<30 )
                return "����ɫ��ô�������Ъ����ɡ�";

        if( query("jing", me)<30 )
                return "�㾫��ͷ���а�������ҵ�������̤�ˣ�";

        if (me->query_int() < 20)
                return "����...����ô���ֱ��ŵģ�Ҳ�����·���";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/sew", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));

        if (sizeof(obs) > 0)
                return "�����Ѿ���" + obs[0]->name() + "�ڰ��������������ˡ�";

        set_temp("job/sew", 1, me);
        return "�ã���Ͱ�������÷�(sew)��С��ɣ������������������";
}

int do_sew(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if( !query_temp("job/sew", me) )
        {
                message_vision("$N͵͵������һ�����룬$nһ����߸����"
                               "����ҷ��£���ʲô����ģ�\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "�㿪ʼ���ҡ�\n");
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
                delete_temp("job/sew", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 1);
        me->receive_damage("qi", 2);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N����һ�����룬�������ߡ�";
                break;
        case 2:
                msg = "$Nչ�����ϣ��������ӱȻ��˰��졣";
                break;
        case 3:
                msg = "$N��������������ӣ����¼�����ӡ��";
                break;
        case 4:
        case 6:
                msg = "$Nר����־��һ��һ�ߵķ��ҡ�";
                break;
        case 5:
                msg = "$N��ü���˿����ӣ�������˼��";
        case 7:
                msg = "$N�ᶯ����ϸָ���������´����·���ģ�������ĳ����ˡ�";
                break;
        default:
                msg = "$N���·���ã�������ϣ����õݸ�$n��";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n����$N��������·�����ͷ���������е���˼��\n";
                delete_temp("job/sew", me);
                delete_temp("job/step", me);

                b = 900 + random(100);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                ob = new("/clone/money/silver");
                ob->set_amount(6);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "��");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/cloth", me) && random(10) == 1) 
                {
                        message_vision("$n��$N΢΢һЦ�������ɵò������е�" 
                                       "��˼�������֮ף��ս�¾��������͸��������ɡ�\n",
                                       me, this_object());
                        ob = new("/clone/goods/zhufu_cloth"); 
                        ob->move(me, 1); 
                        tell_object(me, HIM "\n������һ��" + ob->name() + HIM "��\n" NOR);
                        set("zhufu_mod/cloth", 1, me); 
                }
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N�����е�����һ�ӣ��ֹ�����"
                       "û���������ﲻ���ˣ�\n", me);
        delete_temp("job/sew", me);
        delete_temp("job/step", me);
        return 1;
}
