// lian.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

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
                return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����û�н����ʹ�á�������������\n");

        if( query("neili", me)<250 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 100)
                return notify_fail("�����ҽ����������ң��޷�ʹ�á�������������\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("��û�м�����ҽ������޷�ʹ�á�������������\n");

        msg = HIG "$N" HIG "���е�" + weapon->name() +
              HIG "һ�Σ�ͻȻ����������������$n" HIG "��ѣ�˶�Ŀ��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "�ۻ����ң���ȫ�޷�����$N"
                                           HIR "�Ľ��У�һ������������������Ѫ���岽��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����ֿ죬��������������$P"
                       HIC "��ɱ�н��£�̾Ϊ��ֹ��\n"NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}