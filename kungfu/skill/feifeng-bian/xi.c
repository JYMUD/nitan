#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "��������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int ap,dp,damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("feifeng-bian", 1) < 120)
                return notify_fail("��ķɷ�޷���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("������û�м����ɷ�޷�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "������ң�����" + weapon->name() + HIW "���裬��"
              "��һ����һ����Ȧ�Ӳ���$n" HIW "��\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "ֻ���û���һ����Ϣ����"
                                           "��ӿ��һʱ����ȫ�������������һ����\n" NOR);
                msg += HIY "\n$N" HIY "��״������" + weapon->name() + HIY +
                       "���ӣ�һ�����й���$n" HIY "��\n" NOR;
                message_combatd(msg, me, target);

                for (i = 0; i < 6; i++)
                {
                        if (! me->is_fighting(target))
                                break;
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }

                me->start_busy(1 + random(4));
        } else
        {
                msg += CYN "����$p" CYN "����ܿ�$P" CYN
                       "��һ�У��ƺ���û�з϶���������\n" NOR;
                addn("neili", -70, me);
                me->start_busy(3);
                message_combatd(msg, me, target);
        }

        return 1;
}