// This program is a part of NITAN MudLIB
// shentong.c ���칦 ������ͨ��

// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "������ͨ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("������칦��Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("��û��׼��ʹ�����칦������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��������ͨ����Ƭ�̱������������ȫ��˫�۾������䣬��ƽʱ�������ˡ�\n"
              HIW "$N" HIW "����ͻȻ���ƹ���$n��������������Ϣ��ȴѸ�����硣\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        addn("neili", -800, me);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 600,
                               HIR "$n" HIR "��������Ӧ������$N������ͨ�������񹦻��С�\n" NOR "( $n"
                               RED "���˹��أ��Ѿ�������в�����ʱ�����ܶ���"
                               "��" NOR ")\n" NOR);
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300,
                                                   HIR "���$N" HIR "������ͨ������$n" HIR "��"
                                                   "�ڣ�������ͨ����ʱ͸�ض��룬$n" HIR "���������"
                                                   "����Ѫ��\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У���ȴ���Ǳ��Ķ�ܿ�����\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
