// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "�����" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ"+name()+"��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ"+name()+"��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ"+name()+"��\n");

        if ((int)me->query_skill("fumo-zhang", 1) < 120)
                return notify_fail("���ʮ��·��ħ�Ȼ�򲻹�������ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("staff") != "fumo-zhang")
                return notify_fail("��û�м�����ʮ��·��ħ�ȣ�����ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ�����ȣ�����" + weapon->name() +
              HIW "���裬��Ӱ����������Ȧ������" HIR "�����"
              HIW "������ǵؾ���$n" HIW "��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��ȫ�޷�����������ʵ��ֻ"
                                           "���������项�������ѱ�$N" HIR "������"
                                           "�ȣ�ŻѪ������\n" NOR);
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "����$n" CYN "�����мܣ������ұܣ��ò���"
                       "�׵ֵ�ס��$N" CYN "�Ĺ�����\n" NOR;
                me->start_busy(4);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
