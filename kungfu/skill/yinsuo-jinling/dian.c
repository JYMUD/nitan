// This program is a part of NITAN MudLIB
// dian.c ���յ�Ѩ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return RED"���յ�Ѩ"NOR; }

int perform(object me, object target)
{
        object weapon;
        object ob;
        int ap, dp;
        string result, str, msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("���յ�Ѩֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
             || query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        // if (!objectp(obj=present("jinling suo", me)))
        //        return notify_fail("������û�н�����������ʹ�õ�Ѩ����\n");

        if( (int)me->query_skill("yinsuo-jinling", 1) < 120 )
                return notify_fail("����������岻�����죬��������Ѩ\n");

        if( (int)me->query_skill("tianluo-diwang",1)<120)
                return notify_fail("������޵����ƻ���㣬�ַ����������\n");

        if( (int)me->query_skill("yunv-xinfa",1)< 135)
                return notify_fail("����ڹ���Ϊ̫������޷����Ѩ��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("�������������ʩչ���յ�Ѩ����.\n");

        if( query("neili", me)<1000 )
                return notify_fail("�������������Ѩ��\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("��û�м����������壬�޷�ʩչ" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "\n$N���Ͻ���ɳ���ʹ������������ϳ˸��յ�Ѩ����ֱȡ$n�Ĵ�׵Ѩ��\n\n"NOR;

        ob=query_temp("weapon", target);
        ap=attack_power(me,"whip") + weapon->query_weight();
        dp=defense_power(target,"dodge");

        if (ap / 2 + random(ap) > dp)
        {
                if (! objectp(ob))
                {
                        int damage = 0;

                        if (target->query_skill("dodge") > 200 && random(2) == 0)
                        {
                                switch (random(2))
                                {
                                case 0:
                                        msg += HIR "$n�������˼����ϳ���������û�ܶ����"
                                                "$N�Ľ���������$n��̴��Ѩ�ϣ�$nֻ����һ��"
                                                "�������Ե�����ϣ���������˵���������ܡ�\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR "$n����Ʈ�������鶯֮����������Ҫ�Ȳʣ�"
                                                      "�����ۡ���һ��������ܸ$n��ɫɷ�ף�ҡҡ��׹��\n";
                                        damage = 5;
                                        break;
                                }
                        } else
                        if (target->query_skill("force") > 200 && random(2) == 0)
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR "$n���һ�����Գ�������ǿ�����ֳ��У���࣡�"
                                                "��һ�����죬�����ཻ��$n����΢�Σ������ֽ��\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR "$nһ����Х��˫�ֻû���������Ӱ����ס��ǰ��"
                                                "ֻ�����͡���һ������Ӱ������$n�Ѿ������ɫ�Ұס�\n";
                                        damage = 4;
                                        break;
                                }
                        } else
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR "$n�������У���Ȼ��֪��ܣ����͡���һ����$N"
                                                "�Ľ���������$n��׵Ѩ�ϣ�$nȫ������,�����ڵء�\n";
//                                        target->unconcious();
                                        damage = 5;
                                        break;
                                case 1:
                                        msg += HIR "$nһת��Ѿ�����˾�ʮ���ֻ���İ취��"
                                                "��δ���ü�ʩչ��ֻ�����͡���һ�����ѱ�$N���д�׵Ѩ��ȫ�����������ڵء�\n";
//                                        target->unconcious();
                                        damage = 5;
                                        break;
                                }
                        }
                        if (damage > 0)
                                target->receive_damage("qi",query("max_qi", target)*damage/15);
                        addn("neili", -(500+damage*40), me);
                        me->start_busy(2);
                        message_combatd(msg + NOR, me, target);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("\n($N"+str+")\n", target);
                        return 1;
                }
                if( objectp(ob) && ob->is_item_make() )
                {
                        msg+=HIR"$næ��"+query("name", ob)+"�мܣ�ֻ���û��ھ������ұ����������\n"NOR;
                } else if (objectp(ob))
                {
                        msg += HIW "$n��æ�мܣ�ֻ������ž����һ����$n���е�" + ob->name()+ HIW"�������ɣ�\n";
                        ob->unequip();
                        ob->move(environment(target));
                }
                target->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                int busy = 0;
                if (target->query_skill("dodge") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += "$nһ����Ц�������仯�˼����������˶�Ŀ��һʱ��$N�޷�������\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += "$nͻȻ���Ʈȥ���������磬��$N���еĺ�̱仯�޴�ʩչ��\n";
                                busy = 1;
                                break;
                        }
                } else
                if (target->query_skill("force") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += "$n��ɫ���أ��ӿ��ܣ����ɶ��ɣ���$N�޴����֣�ֻ���ջؽ��塣\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += "$n������м����Цһ����˫�����������ޱȣ���$Nֻ�ܻ����Ծȡ�\n";
                                busy = 1;
                                break;
                        }
                } else
                {
                        switch (random(3))
                        {
                        case 0:
                                msg += "$n��ҡ�һΣ�����ȥ�����·���ƫƫ�����$N��һ����\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += "$n������������ȥ�鶯���$Nһ�������ƶٻ���\n";
                                busy = 2;
                                break;
                        case 2:
                                msg += "$n��ס����������עȫ��"
                                         + "��������ס��$N�Ľ�����\n";
                                busy = 2;
                                break;
                        }
                }
                target->start_busy(busy);
        }
        message_combatd(msg + NOR, me, target);
        addn("neili", -500, me);
        me->start_busy(2);
        return 1;
}
