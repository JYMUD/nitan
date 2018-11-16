#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "������ӡ��" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 120)
                return notify_fail("��ĺ��ҵ����������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("��û�м������ҵ���������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�������" + weapon->name() +  HIY "��ʩ����������"
              "ӡ�ơ���˫���յ���������������$n" HIY "�����ƽ���\n"NOR;

        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "force") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "����������˸����ĵ�����"
                                           "һ���ҽУ��������������֣���Ѫ�Ĵ��罦��\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 100 + 3);
        } else
        {
                msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
