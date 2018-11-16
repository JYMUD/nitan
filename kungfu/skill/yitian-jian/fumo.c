// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��ħ����" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("yitian-jian", 1) < 120)
                return notify_fail("������콣��������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("��û�м������콣�����޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����ߣ�����" + weapon->name() +
              HIW "һ�񣬽���΢������������������Я����������"
              "ͬʱ����$n" HIW "��\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        if (target->is_bad()) ap += ap / 5;


        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += HIC "��$n" HIC "ȴ������㣬һ˿���ң�"
                       "ȫ�񽫴��л��⿪����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "ֻ��$n" HIR "һ���ҽУ�����һ�����ض��룬��"
                "ʱ��Ѫ�Ĵ��ɽ���\n" NOR;
}