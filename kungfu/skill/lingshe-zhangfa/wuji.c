// This program is a part of NITAN MudLIB
// wuji.c �����޼�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "�����޼�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������޼ɡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("���á������޼ɡ��������г��ȣ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�����������ʹ�á������޼ɡ���\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ������������޷�ʹ�á������޼ɡ���\n");

        if ((int)me->query_skill("lingshe-zhangfa", 1) < 150)
                return notify_fail("��������ȷ��������ң��޷�ʹ�á������޼ɡ���\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("��û�м��������ȷ����޷�ʹ�á������޼ɡ���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ����Ц�����е�" + weapon->name() + HIY "��Ȼ���"
              "��ͬ����һ�㣬ʱ��ʱ�£�������ң���֪����$n" HIY "�δ���\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "ʵ���޷�������$P"
                                           HIR "��ʵ�У��������գ��������У�"
                                           "��ʱ����һ����Ѫ��\n" NOR);
                me->start_busy(2);
                if (! target->is_busy())
                target->start_busy(1);
        } else
        {
                msg += CYN "$n" CYN "�����мܣ�����ֵ�ס��$P"
                       CYN "�Ĺ�����\n" NOR;
                addn("neili", -80, me);
                me->start_busy(3);
                if (! target->is_busy())
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
