#include <ansi.h>

#define SIX "��" HIW "��������" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/liumai-shenjian/six", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SIX "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" SIX "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 220)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" SIX "��\n");

        if (me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ" SIX "��\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("���������Ϊû�дﵽ�Ǹ����磬�޷���ת��"
                                   "���γ�" SIX "��\n");

        if( query("neili", me)<500 )
                return notify_fail("������������������޷�ʩչ" SIX "��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ" SIX "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "̯��˫�֣���ָ��������ʱ��������ȣ���"
              "�����ڣ���������������Ѩ��һ�����$n" HIW "��\n" NOR;

        if( random(query("combat_exp", me)/200)>query("combat_exp", target)/300 )
        {
                msg += HIR "$n" HIR "ֻ�н����ݺᣬ΢һ��񣬲����������⡣\n" NOR;
                delta = skill / 6;
        } else
                delta = 0;

        message_combatd(msg, me, target);

        addn("neili", -400, me);
        addn_temp("apply/parry", delta, target);
        addn_temp("apply/dodge", delta, target);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                set_temp("liumai-shenjian/hit_msg", i, me);

                COMBAT_D->do_attack(me, target, 0, i * 3);
        }
        addn_temp("apply/parry", -delta, target);
        addn_temp("apply/dodge", -delta, target);
        delete_temp("liumai-shenjian/hit_msg", me);
        me->start_busy(1 + random(5));

        return 1;
}
