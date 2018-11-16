// moxiao.c ħЦ

#include <ansi.h>

inherit F_SSERVER;

string name() { return "ħЦ"; }

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
                return notify_fail("��ħЦ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("tianmo-jian", 1);

        if (skill < 150)
                return notify_fail("�����ħ������Ϊ���ޣ����ڲ���ʹ�á�ħЦ����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷����á�ħЦ����\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ֻ��װ��������ʩչ��ħЦ����\n");

        msg = HIR "$N" HIR "ͻȻ��������ת�����з������������Ĺ�Ц��$n"
              HIR "ֻ������������̣������������ԣ����ƶٻ���\n$N"
              HIR "����˵�$n" HIR "��ǰ�����е�" + weapon->name() +
              HIR "һ��˲������$p�̳�������\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}