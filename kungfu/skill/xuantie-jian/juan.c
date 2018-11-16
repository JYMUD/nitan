// This program is a part of NITAN MudLIB
// juan.c ���־�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���־�"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 70)
                return notify_fail("�����������������죬����ʹ�þ��־���\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʹ�þ��־���\n");

        if( query("neili", me)<100 )
                return notify_fail("����������̫��������ʹ�þ��־���\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ���־���\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$Nһ�����е�" + weapon->name() + HIY "�����¶��ϵĳ�$n"
              HIY "���˹�ȥ���������ۣ��仯�޳���\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(ap / 80 + 2);
                addn("neili", -50, me);
                msg += YEL "$p" YEL "��æ�����мܣ�һʱ��Ͼ������\n" NOR;
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ��бԾ�ܿ���$P"
                       CYN "�Ĺ�����\n"NOR;
                addn("neili", -25, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}