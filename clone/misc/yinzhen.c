// /clone/misc/yinzhen.c
// Last modified by winder 2003.9.2

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIW "����" NOR, ({ "yin zhen" , "yin", "zhen" }) );
        set_weight(200);

        if( clonep() ) set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIW"�������糤�����룬ϸ�����ͣ���Ϊҽ�Ҵ�Ѩ����֮�á�\n���������������ҽ�߶�Ϊ������ҽ�����������ڹ���\n������������������(zhenjiu)���ˡ�\n" NOR);
                set("value", 0);
                set("yingdu", 50);
                set("base_unit", "ö");
                set("base_weight", 10);
                set("base_value", 0);
                set("material","crimsonsteel");
        }
        set_amount(1);
        init_throwing(30);
        setup();
}

void init()
{
        add_action("do_heal", "zhenjiu");
}

int do_heal(string arg)
{
        object ob, me = this_player();
        int damage, heals, i, exp, pot;
        string msg, s;

        if (me->query_skill("acupuncture", 1) < 1 )
                return notify_fail("���������ûѧ��ȥɱ�˰���\n");
        if( query("equipped", this_object()) != "wielded" )
                return notify_fail("�����������������������ġ�\n");
        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����˭ʩ���������\n");
        if (! ob->is_character() )
                return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n"); 
        if( query_temp("noliving", ob) || !living(ob) )
                return notify_fail("�㻹�ǵ�������֮�������ưɡ�\n");
        if (me->is_busy()) return notify_fail("��������æ���ء�\n");
        if (me->is_fighting() || ob->is_fighting())
                return notify_fail("ս���л������ˣ�����������\n");
        if( ob->is_killing(query("id", me)) )
                return notify_fail("�˼Ҳ�������������ġ�\n");
        if( query("race", ob) != "����" )
          return notify_fail("��Ҫ����ҽ��\n");
        if (ob != me && userp(ob))
        {
                        tell_object(me, YEL "�㲻��Ϊ�����ġ�\n" NOR);
                        return 1;
        }
        if( !userp(ob) && random(me->query_skill("acupuncture",1)+query("cor", me))<1 )
        {
                        message_vision( HIY "$N" HIY "�����$n" HIY "���ˣ���$n" HIY "����$N" HIY "�ǲ�ͣ������˫�֣�����¶�����µ���ɫ��\n" NOR + CYN "$n" CYN "������üͷ����$N" CYN "˵�������ǵ����ջ������˰ɡ�\n"NOR, me, ob);
                        return 1;
        }
        if (me!=ob && ob->query_skill("force") >= 150)
                return notify_fail("�˼��ڹ���񣬲�ָ�����������ˡ�\n");
        if( (query("max_qi", ob)*5/100>query("eff_qi", ob)) )
                return notify_fail("���ڴ������˹��أ�ʩ�����̫Σ���ˣ�\n");
        if( query("neili", me)<80 )
                return notify_fail("����������㣬�޷�ʹ�������Ϊ�����ˣ�\n");
        if( query("jing", me)<50 )
                return notify_fail("��ľ����㣬�޷����о�����\n");
        if( time()-query_temp("last/zhenjiu", ob)<60 )
                return notify_fail("�˼Ҹոս��չ�������ƣ����ڲ���Ҫ���æ��\n");
        if( query("max_qi", ob) == query("eff_qi", ob) )
        {
                if(me != ob) return notify_fail("���˲�û�����ˣ�\n");
                else
                        message_vision(HIW"$N"HIW"�������Լ��������飬������Լ��������ˮƽ��\n" NOR, me);
        }
        set_temp("last/zhenjiu", time(), ob);
        addn("neili", -50, me);
        addn("jing", -30, me);
        me->start_busy(1 + random(1));
        me->improve_skill("acupuncture", 5 + random(me->query_skill("acupuncture",1)));
        tell_object(me, HIC "��ʵ����������ġ������������ˣ�\n" NOR);
        if (me == ob) s = "$N";
                 else s = "$n";
        msg = HIW"$N"HIW"�������룬С���������"+s+HIW"��Ѩ����ȥ��\n"NOR;
        if (random(120) > (int)me->query_skill("acupuncture", 1))
        {
                damage=1+random(query("max_qi", ob)/2);
                i=query("max_qi", ob)*10/damage;

                if (i > 100)
                        msg += CYN"����$N"CYN"������ƫ��û����Ѩ����"+s+CYN"����¶��һ˿�ѹ������顣"NOR;
                else
                {
                        if (i > 40)
                                msg += RED"����$N"RED"�������ͣ���Ȼ�̳���Ѫ�����������еĴ�ɣ�"NOR;
                        else
                                msg += RED"$N"RED"������ȥ�ŷ��̴ִ���Ѩ����"+s+RED"���ۡ��������һ����Ѫ��"NOR;
                }

                ob->receive_wound("qi", damage);
                damage = i;
        }
        else
        {
                msg += HIW"$N"HIW"������׼ȷ����ش���Ѩ������������Ļ���ת����"+s+HIW"�����س���һ��������ɫ�ÿ����ˡ�"NOR;
                damage = -1;
                if( me != ob/* && query("combat_exp", me)<200000*/ )
                {
                        exp = 20 + random(20);
                        pot = 5 + random(5);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);

                        tell_object(me,HIC"������"+chinese_number(exp)+"�㾭���"+chinese_number(pot)+"��Ǳ�ܡ�\n"NOR);
                }

                heals = me->query_skill("acupuncture", 1)+random(me->query_skill("acupuncture", 1));

                if( (query("eff_qi", ob)+heals/3)>query("max_qi", ob) )
                        set("eff_qi",query("max_qi",  ob), ob);
                else addn("eff_qi", heals / 3, ob);
        }

        msg += "\n";
        if (me == ob) message_vision(msg, me);
        else message_vision(msg, me, ob);

        if (damage > 0)
        {
                if( query("qi", ob)<0 )
                {
                        set("eff_qi", 1, ob);
                        set("qi", 1, ob);

                        if (userp(ob))
                        {
                                if (me == ob)
                                        message_vision(HIR"���հ���$N"HIR"��һ����Լ�������\n"NOR, me);
                                else
                                        message_vision(HIR"���հ���$N"HIR"��һ���$n"HIR"������\n"NOR, me, ob);
                        }
                }
                else
                {
                        if (me != ob)
                        {
                                if (random(damage) < 40)
                                {
                                        message_vision(HIR"$N"HIR"ʹ�á����ۡ���в�ֹ��ŭ������Ȼ���¶��֣�����ɱ���Ұ���\n" NOR, ob);
                                        ob->kill_ob(me);
                                        me->fight_ob(ob);
                                }
                                else
                                {
                                        message_vision(HIR"$N"HIR"���ۡ��Ĵ��һ���������ص�����ʹ�����´����ǧ���ĵ㣡\n"NOR,ob);
                                }
                        }
                }
                
        }

        return 1;
}
