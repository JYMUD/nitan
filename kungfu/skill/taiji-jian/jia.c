// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "���־�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int skill, ap, dp, damage;
        string wn1, wn2, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        skill = me->query_skill("taiji-jian", 1);

        if (skill < 150)
                return notify_fail("���̫�������ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫������������ʩչ" + name() + "��\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("�Է�û��ʹ�ñ���������ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn1 = weapon->name();
        wn2 = weapon2->name();

        msg = HIC "ֻ��$N" HIC "���������Խ����˽�������" + wn1 + HIC "ÿ�����Ի���"
              "�̳��������ջأ�ÿ��һ�ж��Ʒ�\n��һ��ϸ˿��Ҫȥ����$n" HIC "��" + wn2 +
              HIC "֮�ϡ�\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -30, me);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "ȴ��$n" HIR "����" + wn2 + HIR "��" +
                                           wn1 + HIR "��ס�󲻶����������������ټ�ɬ"
                                           "�ͣ��������ɿ�к������\n" NOR);

                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 2);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "������ʧɫ����æԾ�����������Ű���$N"
                       CYN "��������\n" NOR;
                addn("neili", -10, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
