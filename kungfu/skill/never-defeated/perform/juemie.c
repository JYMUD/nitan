// juemi.c ��ؾ���
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ؾ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_skill("never-defeated", 1) < 120)
                return notify_fail("��Ĳ����񹦻�������죬����ʹ����ؾ���\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("������ֱֳ��в���ʩչ��ؾ���\n");
        
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("������û�м���������Ϊ����������ʩչ��ؾ���\n"); 

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʹ����ؾ���\n");
 
        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "������˼�������Ȼһ�����е�" + weapon->name() +
              HIC "��Ѹ���ޱȵ�ɨ��$n" HIC "���仯����֮��������˼�飡\n" NOR;
 
        ap = attack_power(me, "sword") + me->query_int();
        dp = defense_power(target, "dodge") + target->query_dex();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "ֻ��$n" HIG "�������ţ�ֻ������һ�����Ͷ����$N"
                       HIG "��һ����\n"NOR;
        } else
        {
                addn("neili", -70, me);
                damage = damage_power(me, "sword");
 
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                           HIR "$n" HIR "��æ�񵲣�������һ��ʵ���ǹ���Ī"
                                           "�⣬������ĥ��͸����ʱ����$P" HIR "���ش���\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}