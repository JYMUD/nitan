#include <ansi.h>
#include <combat.h>

#define FEI "��" HIY "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/xianglong-zhang/fei", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FEI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(FEI "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 150)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" FEI "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" FEI "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" FEI "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" FEI "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ����������ʩչ" FEI "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" FEI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʩ������ʮ���ơ�" HIW "��������"
              HIY "����˫�Ʒ���������һ�����������ھ���֮��"
              "��\n" NOR;  

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "���$N" HIR "����ɽ������Ĺ�"
                       "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ"
                       "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/3, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/3, me);
        return 1;
}
