// This program is a part of NITAN MudLIB
// jumie.c  ���ֶ���Ҷָ���������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "�������"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���������ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʹ�á�������𡹣�\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("duoluoye-zhi", 1) < 180)
                return notify_fail("��Ķ���Ҷָ��Ϊ������Ŀǰ����ʹ�á�������𡹣�\n");

        if( query("neili", me)<800 || query("max_neili", me)<2500 )
                return notify_fail("��������������޷�ʹ�á�������𡹣�\n");

        if (me->query_skill_mapped("finger") != "duoluoye-zhi")
                return notify_fail("��û�м�������Ҷָ������ʹ�á�������𡹣�\n");

        msg = HIB "$N" HIB "����ȫ������ֱ����$n" + HIB "��˫��һȦ����һ���ھ�" +
              "��ס$n��" + HIB "�漴ȫ��һָ��������ϧ�ķѴ�����Ԫ������һ���еУ�\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force", 1);
        dp = defense_power(target, "dodge") + target->query_skill("force", 1);

        damage = damage_power(me, "finger");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "ֻ��$p" HIR "һ���Һţ��ѱ�$P" +
                                           HIR "һָ���У�һ�ɰԵ���������$P" +
                                           HIR "��ָ�⴫�����˼�������\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "������񣬼�ʱ������"
                       CYN "$P" CYN "������ǣ�����㿪����һ����\n" NOR;
        }

        msg += HIR "��$P" + HIR "���������������ȣ��������ɲ�" +
               "�ˣ����˲�������ˣ�\n" NOR;

        me->receive_damage("qi", damage / 10);

        message_combatd(msg, me, target);

        return 1;
}