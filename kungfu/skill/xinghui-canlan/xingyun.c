// xingyun.c �����ܲ�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�����ܲ�"; }

int perform(object me, object target)
{
        int n, ap, dp, damage;
        string msg, pmsg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ����ս���жԶ���ʹ�ð�����\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű�����\n");

        if (weapon->query_amount() < 10)
                return notify_fail("������Ҫ��ʮö��������ʩչ�����ܲ���\n");

        if ((me->query_skill("xinghui-canlan", 1)) < 120)
                return notify_fail("����ǻԲ��ò�����죬���޷�ʹ�������ܲ�������\n");

        if( query("neili", me)<120 )
                return notify_fail("�������������㣬�޷�ʩչ�����ܲ���\n");

        addn("neili", -80, me);
        weapon->add_amount(-10);

        msg= HIW "$N" HIW "����Ծ������һ�ţ���ʱһƬ�ǹ���"
             HIW "��ҹ������һ��ֱ��$n"
             HIW "��ȥ��\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "throwing");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "throwing");
                n = 1 + random(2);
                if (random(ap) > dp)  n += 1 + random(2);
                if (random(ap / 2) > dp)  n += 1 + random(2);
                if (random(ap / 4) > dp)  n += 1 + random(2);
                msg += HIR "���$p" HIR "һ���Һ���������$P" HIR "������" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "��\n" NOR;
                target->receive_wound("qi", damage/2, me);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "����$p" HIG "����Ծ�𣬶����$P" HIG "���������" +
                       weapon->name() + HIG "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}
