#include <ansi.h>
#include <combat.h>

#define JU "��" HIR "��Ѫצ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JU "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("yingtuo-luozhua", 1) < 200)
                return notify_fail("��������צ������죬����ʩչ" JU "��\n");

        if (me->query_skill_mapped("claw") != "yingtuo-luozhua")
                return notify_fail("��û�м���������צ������ʩչ" JU "��\n");

        if (me->query_skill_prepared("claw") != "yingtuo-luozhua")
                return notify_fail("��û��׼��������צ������ʩչ" JU "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" JU "��\n");

        if( query("neili", me)<420 )
                return notify_fail("�����ڵ���������������ʩչ" JU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap=me->query_skill("claw")+query("force", me);
        dp=target->query_skill("parry")+query("force", target);

        msg = HIW "\n$N" HIW "��ת������˫�ֺ���צ�У�ʩ�����С�" HIR "��"
              "Ѫצ" HIW "����Ѹ���ޱȵ�ץ��$n" HIW "��\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                damage = ap + random(ap);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "����$N" HIR "˫צ������$n" HIR "�����ܲ������ؿڱ�$N" HIR
                                           "ץ��ʮ��Ѫ�ۡ�\n" NOR);

                me->start_busy(2);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "�����мܣ�����$N" CYN "���л��⡣\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_sort(msg, me, target);
        return 1;
}