#include <ansi.h>
#include <combat.h>

#define JUAN "��" HIW "��â����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/shangjia-dao/juan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JUAN "��\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹�������ʩչ" JUAN "��\n");

        if ((int)me->query_skill("shangjia-dao", 1) < 50)
                return notify_fail("����̼ҵ����������ң�����ʩչ" JUAN "��\n");

        if (me->query_skill_mapped("blade") != "shangjia-dao")
                return notify_fail("��û�м����̼ҵ���������ʩչ" JUAN "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������ʩչ" JUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����" + weapon->name() +  HIW "���²���������������"
              "������ʱ�������ص�â����$n" HIW "ȫ��\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "ֻ������������Я�ź�â��"
                                           "�Լ�ӿ����һʱ��������������������\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "��$p" CYN "����һƫ�����������ߣ��㿪��$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}