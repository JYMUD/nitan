// lu.c ¾�ɾ�
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("¾�ɾ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_skill("bluesea-force", 1) < 120)
                return notify_fail("����Ϻ�������������죬����ʹ��¾�ɾ���\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʹ��¾�ɾ���\n");
 
       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��Ȼ��Ц���ĳ�һ�ƣ��������£��仯Ī�⣬����$n"
              HIC "��\n" NOR;
 
        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "parry") + target->query_con();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "Ȼ��$n" HIG "������$N" HIG
                       "�����ƣ����Ų�æ�Ķ������һ����\n" NOR;
        } else
        {
                addn("neili", -75, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                           HIR "$n" HIR "�������ԣ��˹��ֵ���ֻ����$P��������"
                                           "��֮����ֱ�������澭��������ʱ�������ˣ�\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}