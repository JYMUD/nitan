// wugu.c �޹�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�޹�"; }

int perform(object me, object target)
{
        string msg,force;
        int ap, dp;
        int count;
        int i,j;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("���޹ǡ�ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���޹ǡ�ֻ�ܿ���ʹ�á�\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 120)
                return notify_fail("��Ļ������ƻ�򲻹����޷�ʹ�á��޹ǡ����У�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á��޹ǡ����У�\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("������û��׼��ʹ�û������ƣ��޷�ʹ�á��޹ǡ����У�\n");

        if(!stringp(force = me->query_skill_mapped("force"))
                ||force!="busi-shenlong")
                return notify_fail("��û��ʹ�����������ķ����޷�ʹ�����У�\n");

        msg = HIW "ֻ����$N�ؽڿ������죬������Լ͸���ɺ�����˫�۱�������޹�һ�㣡\n"NOR;
        ap=attack_power(me, "strike")+me->query_str()*20;
        if (living(target))
                 dp=defense_power(target, "parry")+target->query_dex()*20;
        else     dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIW "$n��$P��ʽ���죬��֪����ô�мܣ�������$N��˫���ѵ���ǰ��\n"NOR;
        }

        else
        {
                msg += HIW "$n���Ӿ���ɲ�Ǽ��ѿ���$N����ʽ�������мܡ�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        addn("neili", -200, me);
        j = random(6);
        if (j < 3) j = 3;
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 2);
        }

        me->start_busy(1+random(2));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);

        return 1;
}
