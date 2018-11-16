// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "�����" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force", 1) < 130)
                return notify_fail("����ڹ���򲻹���ʹ����" + name() + "��\n");

        if (me->query_skill("chanhun-suo", 1) < 100)
                return notify_fail("��Ĳ���������̫ǳ��ʹ����" + name() + "��\n");

        if( query("neili", me)<220 )
                return notify_fail("��������������޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "chanhun-suo")
                return notify_fail("��û�м�������������ʹ����" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�����һЦ������" + weapon->name() +
              HIY "���ñ�ֱ������$n" HIY "���󣬿��Ǵ�����;ȴ��ͣ�ͣ�ת��$n"
              HIY "�ؿڻ�ȥ��\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -180, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "���$n" HIR "һ���ҽУ�δ�ܿ���$N"
                                           HIR "����ͼ������һ��Ӳ�����ؿڣ���Ѫ��"
                                           "����Ƥ��������\n" NOR);
                message_combatd(msg, me, target);
                // if (ap > 1000) ap = 1000;
                dp += target->query_skill("martial-cognize", 1) * 2;
                if (! target->is_busy() &&
                    query("material", weapon) == "white silk" &&
                    ap / 2 + random(ap) > dp)
                {
                        target->start_busy(3 + random(4));
                        message_vision(HIW "$N" HIW "һ�������е�" + weapon->name() +
                                       HIW "��ಡ��Ĵ��˳���������Ȼ����$n"
                                       HIW "��\n$n" HIW "���һ������æ�˺���ȥ��һ�С�\n" NOR,
                                       me, target);
                }
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����һԾ���𣬶�ܿ���"
                       CYN "$P" CYN "�Ĺ�����\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}