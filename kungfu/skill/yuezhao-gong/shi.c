#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "߱Ԫ��" NOR; }

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

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("yuezhao-gong", 1) < 130)
                return notify_fail("��Խצ���ȼ�����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("claw") != "yuezhao-gong")
                return notify_fail("��û�м���Խצ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("claw") != "yuezhao-gong")
                return notify_fail("��û��׼��Խצ��������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "ʩ��Խצ����" HIR "߱Ԫ��" NOR + WHT "����������"
              "��һ�ᣬֱֱץ��$n" WHT "�������ڡ�\n" NOR;

        addn("neili", -100, me);
        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                addn("neili", -50, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "ֻ��$n" HIR "һ���Һ�������$N" HIR
                                           "����ָץ�����ţ���Ѫ��ʱ�Ĵ��ɽ���\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�������ݣ����μ�ת������Ķ����$P"
                       HIC "�Ĺ�����\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}