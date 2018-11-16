// chuanxin.c һ������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "һ������"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage, exp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��һ�����ġ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        ap = attack_power(me, "sword");

        if (ap < 250)
                return notify_fail("�����ħ�����ȼ�����, ����ʹ�á�һ�����ġ���\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������޷����á�һ�����ġ���\n");

        msg = HIC "$N" HIC "һ����Х��˫��һ��������������Ӽ�ת��Ȧ�������е�"
              + weapon->name() + HIC + "��Ϊһ�壬����һ���׹⣬�������һ���ֱ��$n" HIC
              "������\n" NOR;

        dp = defense_power(target, "force");
        exp=query("combat_exp", me)/query("combat_exp", target);

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -220, me);
                damage = damage_power(me, "sword") + (int)me->query_skill("xixing-dafa", 1);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "ֻ��ǰ�ء����ꡱһ�����ѱ�"
                                           "����������һ��Ѫ���������������һ���Һ���\n" NOR);
                me->start_busy(2);
                if (exp > 3)
                {
                      message_combatd(msg, me, target);
                      target->die(me);
                      return 1;
                }
        } else
        {
                addn("neili", -60, me);
                msg += HIG "����$n" HIG "���з���������һת���ѱܿ���$N"
                       HIG "��ȫ��һ����\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
