 // ji.c ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/ningxue-shenzhao/ji", me) )
                return notify_fail("�㻹����ʹ����һ�У�\n");

        if (! me->is_fighting(target))
                return notify_fail("�����硹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("claw") != "ningxue-shenzhao")
                return notify_fail("��û��׼��ʹ����Ѫ��צ���޷�ʩչ�����硹��\n");

        skill = me->query_skill("ningxue-shenzhao", 1);

        if (skill < 250)
                return notify_fail("�����Ѫ��צ��Ϊ���ޣ��޷�ʹ�á����硹��\n");

        if (me->query_skill("force") < 350)
                return notify_fail("����ڹ���򲻹�������ʩչ�����硹��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת�����γɡ����硹��\n");

        if( query("neili", me)<500 )
                return notify_fail("������������������޷�ʩչ�����硹��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ�����硹��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һ����Х������Ծ��˫צ�ó�����צӰ�����ƻֺ룬���缲��һ������$n" HIR "����ҪѨ��\n" NOR;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/parry", delta, target);
        addn_temp("apply/dodge", delta, target);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/parry", -delta, target);
        addn_temp("apply/dodge", -delta, target);
        me->start_busy(1 + random(5));

        return 1;
}
