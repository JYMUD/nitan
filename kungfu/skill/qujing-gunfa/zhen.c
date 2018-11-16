#include <ansi.h>
#include <combat.h>

#define ZHEN "��" HIR "����Ǭ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;

        if( userp(me) && !query("can_perform/qujing-gunfa/zhen", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")
                return notify_fail("��û�м���ȡ������������ʩչ" ZHEN "��\n");

        if(me->query_skill("qujing-gunfa", 1) < 200 )
                return notify_fail("��ȡ������������죬����ʩչ" ZHEN "��\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("����ڹ���Ϊ����������ʩչ" ZHEN "��\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("���������Ϊ̫��������ʩչ" ZHEN "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ�����̫��������ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "������" + weapon->name() + HIW "����ѹ��$n"
              HIW "�������������ŷ���֮��������ȡ������ɱ�š�" HIR "��"
              "��Ǭ��" HIW "����\n����ʯ�䣬���˾�ȫ���ϵ������֣�" +
              weapon->name() + HIW "����ǧ�ٸ����ƣ����׳������$n" HIW
              "ϯ���ȥ��\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "��$N" HIR "������������ȫ��֪����"
                       "���мܣ���������������\n" NOR;
                count = ap / 8;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "������磬������Ȼ����"
                       "æ���������С��Ӧ����\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -200, me);

        for (i = 0; i < 10; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(9));
        return 1;
}
