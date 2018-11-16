// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���ξ�" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ����ս���в���ʹ�á�\n");

        if ((level = me->query_skill("xiaoyaoyou", 1)) < 100)
                return notify_fail("�����ң���Ʒ���������������ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("dodge") != "xiaoyaoyou")
                return notify_fail("��û�м�����ң��Ϊ�Ṧ������ʩչ"+name()+"��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ��������㣬����ʩչ"+name()+"��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����΢�Σ�ʩ����" HIG "���ξ�"
              HIW "���������ߣ�����������������ΪƮ�ݡ�\n" NOR;

        ap = attack_power(me, "dodge");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ��������Ӱ���������ɴ�"
                       "��ʧɫ�����ƶ�Ϊ���͡�\n" NOR;
                target->start_busy(level / 80 + 2);
                me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "����$n" CYN "������$P" CYN "����"
                       "������û���ܵ��κ�Ӱ�졣\n" NOR;
                me->start_busy(2);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
