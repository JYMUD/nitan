#include <ansi.h>

inherit F_SSERVER;
string name() { return "�������"; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��������졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("��û��׼��ʹ��ǧ�����֣��޷�ʩչ������졣\n");

        skill = me->query_skill("qianzhu-wandushou", 1);

        if (skill < 220)
                return notify_fail("���ǧ��������Ϊ���ޣ��޷�ʩչ������졣\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ������졣\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת����ʩչ������졣\n");

        if( query("neili", me)<500 )
                return notify_fail("������������������޷�ʩչ������졣\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ������졣\n");

        msg = RED "\n$N" RED "����һ����Х��ǿ���ھ���ȫ��"
              "�����ֳ���������֮ɫ���ȵ�����������족,˫"
              "����\nȻ�ĳ�����ʱ�ó��������ɫ��Ӱ��������"
              "��������$n" RED "ȫ��\n\n" NOR;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/parry", skill, target);
        addn_temp("apply/dodge", skill, target);
        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/parry", -skill, target);
        addn_temp("apply/dodge", -skill, target);
        me->start_busy(1 + random(2));

        return 1;
}