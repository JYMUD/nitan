// fengyun. ������ӿ

#include <ansi.h>

inherit F_SSERVER;

string name() { return "������ӿ"; }
int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��������ӿ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("��ֻ�п��ֲ���ʹ�á�������ӿ����\n");

        skill = me->query_skill("fengyun-bianhuan", 1);

        if (skill < 150)
                return notify_fail("��ķ��Ʊ����Ϊ̫�ͣ����ڲ���ʹ�á�������ӿ����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷�ʹ����������ӿ����\n");

        msg = HIW "$N" HIW "˫ȭһ���û���һȦȦ�������ޣ���ʵ�ѷֵ�ȭӰ��"
              HIW "�������$n" HIW "�����\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
