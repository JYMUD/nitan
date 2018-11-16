#include <ansi.h>
inherit F_SSERVER;

#define QU "��" HIW "˫��ȡˮ" NOR "��"

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;

        if( userp(me) && !query("can_perform/xianglong-zhang/qu", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(QU "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 150)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" QU "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" QU "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" QU "��\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("�Է�û��ʹ�ñ���������ʩչ" QU "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" QU "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ����������ʩչ" QU "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" QU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����һ����ȫ���ھ��ŷ��������ұ۷����⳶����ͼ��$n"
              HIW "��" + weapon->name() + HIW "�������С�\n" NOR;

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*10;

        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -300, me);
                msg += HIR "$n" HIR "ֻ����Χ����ӿ��������" + weapon->name()
                       + HIR "��Ȼ����ס����$N" HIR "�������ַ�ȥ��\n" NOR;
                me->start_busy(2);
                weapon->move(me, 1);
        } else
        {
                addn("neili", -200, me);
                msg += CYN "$n" CYN "ֻ����Χ����ӿ������æ����������"
                       + weapon->name() + CYN "������ܲ�͸�磬ʹ��$N"
                       CYN "�޴����֡�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}