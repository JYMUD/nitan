// yihuanghu.c ���㱾�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���㱾�"; }

int perform(object me)
{
        string msg;
        object target;
        int skill;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("�����㱾���ֻ����ս����ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if( (int)query("neili", me) < 1000 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 150 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 150)
                return notify_fail("������ȭ����Ϊ���������ܹ�������㱾�! \n");

          if( (int)me->query_skill("force", 1) < 150)
                  return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�����㱾�! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷��������㱾���\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�����㱾�����\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "���㱾�" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -300, me);

                msg = HIC "���$N˫ȭ����ʱ��ȴ���������ޡ�\n$n������ּ䣬�ѱ�$N��������ס������лк����ģ�\n"NOR;
                target->start_busy(ap/80+2);
                me->start_busy(1);
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;

                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}