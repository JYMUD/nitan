#include <ansi.h>
#include <combat.h>

#define ZUI "��" HIR "����Ǭ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/pomopima-jian/zui", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZUI "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ������޷�ʩչ" ZUI "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" ZUI "��\n");

        if (me->query_skill("pomopima-jian", 1) < 120)
                return notify_fail("�����ī���齣��Ϊ�������޷�ʩչ" ZUI "��\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������޷�ʩչ" ZUI "��\n");

        if (me->query_skill_mapped("sword") != "pomopima-jian") 
                return notify_fail("��û�м�����ī���齣���޷�ʹ��" ZUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ������������" + weapon->name() + NOR + HIR
              "��������ԲȦ������������Ȧ������������֮�������$n" HIR
              "��ǰ��ȥ��\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -200, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "ֻ���������ң�����Ϯ�壬"
                                           "΢΢һ�㣬��������������Ѫ�ɽ���\n" NOR );
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "������Ѹ�ͣ�����һԾ��"
                       "������$P" CYN "�������ļ�����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}