// xiao.c ����ҹ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i, n;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("̫���񹦵ġ�����ҹ�꡹����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("taixuan-shengong", 1);

        if (skill < 180)
                return notify_fail("���̫������Ϊ����������ʹ�á�����ҹ�꡹��\n");

        if ((int)me->query_skill("force", 1) < 300)
                return notify_fail("����ڹ���Ϊ���������޷�ʹ�á�����ҹ�꡹��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������޷����á�����ҹ�꡹��\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ֻ��װ��������ʩչ������ҹ�꡹��\n");

        n = 4 + skill / 100;

        msg = HIW "$N" HIW "����" + weapon->name() + HIW "�����ζ�����ʱ����һ��"
              HIW "�ͳ���������������ĺ�Х������\nͻȻ��$N" HIW "���е�" +
              weapon->name() + HIW "��һ�����绮����˲������$n"
              HIW "�������" + chinese_number(n) + "����\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 6;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < n; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
