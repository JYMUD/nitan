// smith.c

#include <ansi.h>
#include <mine_def.h>

inherit NPC;
inherit F_DEALER;

string ask_me();
int  do_gu(string arg);
int  do_dapi(string arg);
int  do_cuihuo(string arg);
int  do_repair(string arg);
void reward(object me);
protected void rong_he(object, object);
string identify_mine_stone(object who);
protected string *can_epurate = ({
        IRON_MINE,
        IRON_RES_CU,
        IRON_RES_JING,
        BLACK_IRON,
});

// no create_function: inherit by other NPC

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_look", ({"guankan", "kan"}));
        add_action("do_gu", "gu");
        add_action("do_dapi", "dapi");
        add_action("do_cuihuo", "cuihuo");
        add_action("do_repair", "repair");
        add_action("do_repair", "xiuli");
        add_action("do_epurate", "tilian");     // ������������
        add_action("do_ronghe", "ronghe");
}

void setup()
{
        set("inquiry/job",    (: ask_me :));
        set("inquiry/����",   (: ask_me :));
        set("inquiry/repair", "����Ҫ��(repair)��ʲô��");
        set("inquiry/����",   "����Ҫ��(repair)��ʲô��");
        set("inquiry/����",   (: identify_mine_stone :));

        ::setup();
}

string ask_me()
{
        object me = this_player();

        if (query("combat_exp", me) > 50000)
                return "�����ϸ����δ�������˰ɣ�";

        if (query("qi", me) < 50)
                return "�㻹��Ъ����ɣ�Ҫ�ǳ��������ҿɳе�����";

        if (query_temp("smith/gu", me))
                return "����ķ��䣬����ô��ĥ��(gu)��";

        if (query_temp("smith/dapi", me))
                return "�������������û��(dapi)��";

        if (query_temp("smith/cuihuo", me))
                return "�ɻ���ô��͵��������Ҵ��ȥ(cuihuo)��";

        switch(random(3))
        {
        case 0:
                set_temp("smith/gu", 1, me);
                return "�ã�����ҹ�һ�������(gu)��";

        case 1:
                set_temp("smith/dapi", 1, me);
                return "�����ɣ�����Ҵ�һ������(dapi)��";

        case 2:
                set_temp("smith/cuihuo", 1, me);
                return "ȥ���Ұ���Щ�ճ�¯�Ĵ�һ�»�(cuihuo)��";
        }
}

int do_gu(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (!query_temp("smith/gu", me))
        {
                message_vision("$n��͵͵������ķ�������˼���硣"
                               "������$N��$n��ȵ����������Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n����ķ��ƴ������������$N���˵��˵�ͷ��\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_dapi(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (!query_temp("smith/dapi", me))
        {
                message_vision("$n���𼸿���������������˵ࡣ"
                               "������$N��$n��ȵ������£��Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n���Ŵ��ӶԸճ�¯�Ļ��ȵ����������ô��ţ�"
                        "$N���š���һ��������ȥ��Щ���⡣\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_cuihuo(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (!query_temp("smith/cuihuo", me))
        {
                message_vision("$n�ճ���һ������õ����ӣ�"
                               "������$N��$n��ȵ������£�����Ҹ㻵�ˡ�\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N����ǯ����һ��������ӣ������ˮ"
                       "�أ����ꡱ��һ��������ð��\n",
                       me);
        reward(me);
        return 1;
}

void reward(object me)
{
        int exp, pot;
        object coin;
        object ob;

        delete_temp("smith/gu", me);
        delete_temp("smith/dapi", me);
        delete_temp("smith/cuihuo", me);

        coin = new("/clone/money/silver");
        coin->set_amount(1 + random(2));
        coin->move(this_object());
        message_vision("$N��$n�������Ǹ���Ĺ�Ǯ��\n",
                       this_object(), me);
        command("give coin to " + query("id", me));
        if (! query("zhufu_mod/armor", me) && random(10) == 1)
        {
                ob = new("/clone/goods/zhufu_armor");
                //ob->move(this_object());
                message_vision("$N��$n�ٺ�һЦ�������ɵò������е���˼�������֮ף�����׾��������͸��������ɡ�\n",
                               this_object(), me);
                ob->move(me, 1);
                //command("give zhufu armor to " + query("id", me));
                set("zhufu_mod/armor", 1, me);
        }
        if (query("combat_exp", me) < 10000)
        {
                exp = 200 + random(30);
                pot = exp / 3;
                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
        }
        me->receive_damage("qi", 30 + random(20));
        me->start_busy(1);
}

int do_repair(string arg)
{
        object me;
        object ob;
        mixed  msg;
        int consistence;
        int cost;
        int max;
        mapping repair;

        if (! arg)
                return 0;

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("�����Ϻ���û������������\n");

        if (undefinedp(consistence = query("consistence", ob)))
                return notify_fail(ob->name() + "�ƺ�����Ҫ����������ɣ�\n");

        if (undefinedp(max = query("max_consistence", ob)))
                max = 100;

        if (consistence == max)
                return notify_fail(ob->name() + "�����������������ʲô��\n");

        if (! undefinedp(msg = query("no_repair", ob)))
        {
                if (stringp(msg))
                        write(name() + "�������ҿ������ˡ�\n");
                else
                        write(name() + "����" + msg);
                return 1;
        }

        if (mapp(repair = query_temp("pending/repair", me)) &&
            repair["item"] == ob)
        {
                if (me->is_busy())
                        return notify_fail("��������æ���أ�\n");

                notify_fail("���ȴ�����Ǯ��˵��\n");
                if (MONEY_D->player_pay(me, repair["cost"]) != 1)
                        return 0;

                message_vision("$n��" + ob->name() + "�ݸ���$N��ֻ��$N"
                               "���𹤾ߣ�������������" + ob->name() +
                               "�ú������ޡ�\n", this_object(), me);
                set("consistence", max, ob);
                message_vision("$N���������ˣ������ְ�" + ob->name() +
                               "������$n��$n���˿���������ͳ���һЩǮ"
                               "�����ʡ�\n", this_object(), me);
                me->start_busy(1 + random(max - consistence) / 20);
                delete_temp("pending/repair", me);
                return 1;
        }

        cost = (max - consistence) * query("value", ob) / 480;
        if (cost >= 100000) cost = ((cost - 100000) / 2 + 100000) / 10000 * 10000; else
        if (cost >= 10000)  cost = cost / 1000 * 1000; else
        if (cost >= 1000)   cost = cost / 100 * 100; else
        if (cost >= 100)    cost = cost / 10 * 10;

        msg = "$n�ó�һ" + query("unit", ob) + ob->name() +
              "��$NƳ��һ�ۣ�������Ҫ�޺�����Ҫ" +
              MONEY_D->price_str(cost) + "���С���\n";
        if (query("family/family_name", me) == "���ϻ���" &&
            ob->item_owner() == query("id", me))
        {
                cost /= 2;
                msg += "$n�������ϣ���������������˼��������ۣ���" +
                       MONEY_D->price_str(cost) + "�ɣ���\n";
        } else
        if (me->query_skill("higgling", 1) >= 30 && cost >= 50)
        {
                cost = cost * 500 / (me->query_skill("higgling", 1) + 500);
                switch (random(5))
                {
                case 0:
                        msg += "$n��������磬�����ҳ����չ���������ϣ����������ۿۣ���\n";
                        break;

                case 1:
                        msg += "$n���������Ǵ��ϰ�����ҵ����˰�����������...��\n";
                        break;

                case 2:
                        msg += "$n��������λ���ã������������ô��... �����ۿ���Σ���\n";
                        break;

                case 3:
                        msg += "$n������̫���ˣ���ʵ��û��ô���ˣ����˵㣬���˵�ͺá���\n";
                        break;

                case 4:
                        msg += "$n�������Ҽ��ޣ������ɣ��´���һ�����㣬��������и��ã����˵�ɡ���\n";
                        break;
                }

                if (cost >= 1000)
                        cost = cost / 100 * 100;
                else
                        cost = cost / 10 * 10;
                msg += "$N���ʼ���������ˣ����ˣ��Ǿ�" +
                       MONEY_D->price_str(cost) +
                      "���ˡ���\n";
        }

        message_vision(msg, this_object(), me);
        tell_object(me, YEL "������ȷ�����������Ʒ����������һ���������\n" NOR);
        set_temp("pending/repair/item", ob, me);
        set_temp("pending/repair/cost", cost, me);
        return 1;
}

string identify_mine_stone(object who)
{
        object *inv;

        if(!who)
                return 0;

        if(!sizeof(inv = filter_array(all_inventory(who), (: $1->is_mine_stone() && !$1->query_check() :))))
                return "������û����Ҫ�����Ŀ�ʯ��\n";

        inv->set_check_flag(1);
        return sprintf("����������%s��\n",!random(3)?"��ûʲôֵǮ�Ķ���":"");
}

int do_epurate(string arg)
{
        object tg, ob, me = this_player();
        string mcs, cmcs;
        int ew, value, rtn;

        if(this_object()->is_busy())
                return notify_fail(sprintf("%s˵�����Ȼ������æ���ء�\n", name()));

        if(!arg || !objectp(ob = present(arg, me)))
                return notify_fail("��Ҫ����ʲô��\n");

        if(ob->is_mine_stone())         // ������ʯ
        {
                if(!ob->query_check())
                        ob->set_check_flag(1);

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1) )
                        return notify_fail(sprintf("%sҡҡͷ˵�������ﲻ���κο���ɷݡ�\n", name()));

                if( (ew = ob->query_eff_weight()) < 1 )
                        return notify_fail(sprintf("%sҡҡͷ˵�������ﺬ��%s̫���ˣ�û��������\n", name(), cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%sҡҡͷ˵��������ʯû��������\n", name()));

                value = MINE_D->query_mine_class_value(tg->query_mine_class()) * ew * 3 / 10;
                if(value < 1)
                        value = 1;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s˵������������ʯ���%s��Ҫ%s��\n",
                                this_object()->name(), cmcs, MONEY_D->money_str(value)));
                }

                message_vision("$N����$n���ͷ˵������һ�����\n", this_object(), me);

                call_out("epurate_it", 1+random(2), me, ob, tg);
                return 1;
        }

        else if(ob->is_iron_class_res())        // ����
        {
                int upq;

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1)
                ||  !(upq = MINE_D->query_mine_class_up_quantity(mcs)) )
                        return notify_fail(sprintf("%sҡҡͷ˵�����ⶫ��û���پ����ˡ�\n", this_object()->name()));

                if( (ew = ob->query_weight()/100) < upq )
                        return notify_fail(sprintf("%sҡҡͷ˵������%s����������Ҫ %d �������%s������\n",
                                this_object()->name(),cmcs, upq, cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%sҡҡͷ˵��������û����%s���о����ˡ�\n", this_object()->name(), cmcs));

                ew /= upq;
                value = (MINE_D->query_mine_class_value(tg->query_mine_class()) -
                        MINE_D->query_mine_class_value(mcs)*upq) * ew/2;

                if(value < 10)
                        value = 10;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s˵���������%s���о�����Ҫ%s��\n",
                                name(), cmcs, MONEY_D->money_str(value)));
                }

                destruct(ob);
                tg->set_weight(ew*100);
                if(!tg->move(me) && !tg->move(environment()))
                {
                        destruct(tg);
                        return notify_fail("�쳣���أ�����ʦ����ɡ�\n");
                }

                rong_he(me, tg);
                write(sprintf("%s���ͷ˵�������ˣ���ȥ�ɡ�\n", name()));
                return 1;
        }

        else
                return notify_fail(sprintf("%sҡҡͷ˵�����ⶫ��û��������\n", name()));
}

protected void epurate_it(object me, object ob, object tg)
{
        int ew;

        if(!ob || !me || !tg || (environment(me) != environment()))
        {
                if(tg)
                        destruct(tg);
                return;
        }

        ew = ob->query_eff_weight()*9/10;
        if(ew < 1)
                ew = 1;

        if(ob->query_mine_class() == BLACK_IRON)
                tg->set_sum(ew);
        else
                tg->set_weight(ew*100);

        destruct(ob);
        if(!tg->move(me) && !tg->move(environment()))
                destruct(tg);

        rong_he(me, tg);
        message_vision("$N����$n���ͷ˵�����������ˣ���ȥ�ɡ�\n", this_object(), me);
}

int do_ronghe(string arg)
{
        object me = this_player(), ob;

        if(!stringp(arg)
        || !sizeof(arg)
        || !objectp(ob = present(arg, me))
        || !ob->is_iron_class_res() )
                return notify_fail("��Ҫ�ۺ�ʲô��\n");

        rong_he(me, ob);
        write(sprintf("%s���ͷ˵�������ˡ�\n", name()));
        return 1;
}

protected void rong_he(object me, object ob)
{
        object *inv;
        string cms;
        int wt;

        if(!objectp(me)
        || !objectp(ob)
        || !ob->is_iron_class_res()
        || !(cms = ob->query_mine_class()) )
                return;

        if( !sizeof(inv = filter_array(all_inventory(me), (: ($1->is_iron_class_res())
                && ($1->query_mine_class() == $(cms))
                && ($1 != $(ob)) :))) )
                return;

        if(cms == BLACK_IRON)
        {
                foreach(object tmp in inv)
                {
                        wt += tmp->query_sum();
                        destruct(tmp);
                }

                ob->add_sum(wt);
                return;
        }

        foreach(object tmp in inv)
        {
                wt += tmp->query_weight();
                destruct(tmp);
        }

        wt += ob->query_weight();
        ob->set_weight(wt);
}