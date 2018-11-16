// jing.c ����һ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����һ��"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������һ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        ap = attack_power(me, "blade");

        if (ap < 120)
                return notify_fail("�����ħ�����ȼ�����, ����ʹ�á�����һ������\n");

        if( query("neili", me)<120 )
                return notify_fail("��������������޷����á�����һ������\n");

        msg = HIY "$N" HIY "һ����ߣ��粽ǰ�ƣ�����" + weapon->name() +
              HIY "�������죬������㿳��$n" HIY "��\n" NOR;

        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -80, me);
                damage = damage_power(me, "blade");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "�������У��������㣬Ȼ��$N"
                                           HIR "������ʽһ�䣬����" + weapon->name() +
                                           HIR "б�ϻ���$n" HIR "��˫�ȡ�\n"
                                           HIR "ֻ��$n" HIR "�����Һ����ѱ����У����Ѫ"
                                           HIR "���������������¡�\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                addn("neili", -30, me);
                msg += HIC "����$n" HIC "���ѿ���$N"
                       HIC "����ͼ�����ɵؽ�$P" HIC "�����мܿ���\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
