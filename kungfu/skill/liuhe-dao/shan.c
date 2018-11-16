#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "������" NOR; }

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
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ"+name()+"��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ"+name()+"��\n");

        if ((int)me->query_skill("liuhe-dao", 1) < 80)
                return notify_fail("������ϵ����������ң�����ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("blade") != "liuhe-dao")
                return notify_fail("��û�м������ϵ���������ʩչ"+name()+"��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���е�" + weapon->name() +  HIW "���²���������"
              "�任�����ַ�λ��������һ����$n" HIW "���䣡\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "ֻ��$n" HIR "�мܲ�������ʱ��$N"
                                           HIR "��һ������Ҫ�����˿ڼ��ǣ���Ѫ�񽦣�\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�����������ס�Ż�������$P"
                       CYN "�������У�ʼ���κβ��á�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}