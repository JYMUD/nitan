// shangfei.c �˷ξ�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�˷ξ�"; }

private void remove_effect(object me, int amount);

int perform(object me)
{
        string msg;
        object target;
        int skill, dodge_decrease;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("���˷ξ���ֻ����ս����ʹ�á�\n");

        if( (int)query("neili", me) < 600 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 60 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 60)
                return notify_fail("������ȭ����Ϊ���������ܹ�����˷ξ�! \n");

        if( (int)me->query_skill("force", 1) < 60)
                  return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ���˷ξ�! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷������˷ξ���\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ���˷ξ�����\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "�˷ξ�" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -100, me);

                msg = HIG "$N��ȭ���������ף����족��һ������$n���ϣ�\n$nֻ���ú�����˳����ʱ�Ų�������࣡\n"NOR;
                dodge_decrease = query("apply/dodge", target) / 10;
                addn_temp("apply/dodge", -dodge_decrease, target);
                target->start_busy(2);
                me->start_busy(2 + random(2));
                call_out("remove_effect", skill/60, target, dodge_decrease);
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

private void remove_effect(object me, int amount)
{
        if (!me)
                return;
        addn_temp("apply/dodge", amount, me);
        tell_object(me, "��о��������˳�������е�����ȭ�˷ξ����������ˡ�\n");
}