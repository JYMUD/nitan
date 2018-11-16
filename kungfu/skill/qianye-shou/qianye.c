// This program is a part of NITAN MudLIB
// qianye.c ǧҶ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "ǧҶ����"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ǧҶ���֡�ֻ����ս���жԶ���ʹ�á�\n");

        skill = me->query_skill("qianye-shou", 1);

        if (skill < 120)
                return notify_fail("���ǧҶ�ֵȼ�����������ʹ�á�ǧҶ���֡���\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷����á�ǧҶ���֡���\n");

        if (me->query_skill_mapped("hand") != "qianye-shou")
                return notify_fail("��û�м���ǧҶ�֣��޷�ʹ�á�ǧҶ���֡���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ٿ�Ŀ���$n" HIC "������һ�Σ�"
              "����������Ӱ����ͬ����ǧ��ֻ��һ�빥��" HIC
              "$n��\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "�������мܣ����޷���ܣ������$P"
                                           HIR "��������Ū����ͷת������Ҳ���˺����ۡ�\n" NOR);
                me->start_busy(1 + random(2));
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap/120 + 2);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ����������ȫȻ������$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
