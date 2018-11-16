// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "������ӿ" NOR; }

inherit F_SSERVER;

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
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("dodge", 1) < 140)
                return notify_fail("��Ļ����Ṧ����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("kuangfeng-jian", 1) < 140)
                return notify_fail("��Ŀ��콣��Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "kuangfeng-jian")
                return notify_fail("��û�м������콣������ʩչ" + name() + "��\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�����������ת����" + weapon->name() + HIW "��ɲ�Ǽ�����\n"
              "������𣬷���������" + weapon->name() + HIW "�͵ؾ���$n" HIW "��\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -230, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55 + random(6),
                                           HIR "$n" HIR "����Ŀ�ɿڴ���ֻ��һ���紵����" + weapon->name() + HIR
                                           "ȴ��͸�ض�����\n" NOR);
        } else
        {
                addn("neili", -120, me);
                me->start_busy(2);
                msg += CYN "����$n" CYN "΢΢һЦ�������㿪��$N"
                       CYN "�Ľ��С�\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
