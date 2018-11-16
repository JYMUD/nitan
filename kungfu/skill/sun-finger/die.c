// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��������" NOR; }
string *xue_name = ({
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ",
"�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ", "����Ѩ", "����Ѩ", "���Ѩ",
"�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

int perform(object me, object target)
{
        int damage;
        string msg, wp;
        object weapon;
        int ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("sun-finger", 1) < 200)
                return notify_fail("��һ��ָ��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("��û�м���һ��ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("��û��׼��һ��ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        damage = damage_power(me, "finger");
        if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                damage += damage * n * 15/100;
        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if( n > 1 ) msg = HIW "$N" HIW "Ĭ��������ת��ͻȻ��"; else
        msg = HIW "ͻȻ��";

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                wp = weapon->name();
                msg += "$N" HIW "��ָһ�����$n" HIW "����" + wp + NOR + HIW
                       "�������ϡ�" HIY "���" HIW "������" HIY "����" HIW "��"
                       "����" HIY "����" HIW "����Ѩ��\n" NOR;

                ap = attack_power(me, "finger");
                dp = defense_power(target, "force");

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIR "��ʱ��$n" HIR "ֻ��������һ�飬����" + wp +
                               HIR "��Ҳ�óֲ�ס�����ֵ��ڵ��ϡ�\n\n" HIW "��"
                               "����";
                        addn("neili", -150, me);
                        weapon->move(environment(target));
                } else
                {
                        msg += CYN "����$n" CYN "������" + wp + NOR + CYN "ת"
                               "�����֣����ڻ�������һ�С�\n\n" HIW "������";
                        addn("neili", -100, me);
                }
        }

        msg += "$N" HIW "������ָ��һʽ��" HIR "��������" HIW "���������ʱһ��"
               "����������ֱϮ$n" HIW "�ؿڣ�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        msg += "\n" HIW "����$N" HIW "̤ǰһ�������������ŷ�������һָ����$n" HIW
               "��ȥ��ָ���ݺᣬ��Ȼ���죡\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        msg += "\n" HIW "���$N" HIW "һ���ͺȣ���ָ���͡���һ�����������ָ��ͬ"
               "ʱ����$n" HIW "ȫ�����ҪѨ��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        if( query_temp("sun-finger/die", target) == 3
            && query("neili", target) )
        {
                msg += HIY "\n$n" HIY "��$N" HIY "��ָ���У�ȫ��������"
                       "ɢ������ƺӾ��̣�������ʱ��к������\n\n" NOR;
                set("neili", 0, target);
        }
        me->start_busy(3 + random(2));
        addn("neili", -800, me);
        delete_temp("sun-finger/die", target);
        message_combatd(msg, me, target);

        if( !query("neili", target) )
                tell_object(target, HIC "��ֻ�������ھ��ƿտ���Ҳ��һʱ"
                                    "˵���������ܡ�\n" NOR);

        return 1;
}
