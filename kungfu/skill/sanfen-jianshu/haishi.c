// haishi.c ������¥

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/sanfen-jianshu/haishi", me) )
                return notify_fail("�㲻��ʹ�á�������¥����һ������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������¥��ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("sword", 1) < 150)
                return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�á�������¥����\n");

        if (me->query_skill("sanfen-jianshu", 1) < 150)
                return notify_fail("������ֽ�������Ϊ����������ʹ����һ������\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("����Ṧ��Ϊ�������޷�ʹ�á�������¥����\n");
 
        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���һ��������" + weapon->name() +
              HIW "����֮�ʣ�ͻȻȦת��ʹ�����ֽ����Ķ���֮��"
              "��������¥����һ��֮��\n�����̺����У���ʽ������"
              "������������ʵʵ���������⾶ֱ����$n"
              HIW "��\n\n" NOR;

        addn("neili", -150, me);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        me->start_busy(1 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "��ȫ�޷�������ʵ��ֻ��һ���ĵĴ�ʹ��һ���ҽУ��ѱ�$N"
                                           HIR "�����Ľ��д��С�\n" NOR);
                if (ap / 3 + random(ap) > dp)
                {
                        damage /= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                   HIR "\n$N" HIR "��$n" HIR "�ش�֮�²�������������"
                                                   HIR "��Цһ��������" + weapon->name() +
                                                   HIR "�������ֹ���һ��������$p" HIR "�ؿڡ�\n" NOR);
                }
        } else
        {
                msg += HIC "$n" HIC "��״���μ��ˣ��ܿ���$N"
                       HIC "�����Ĺ�����\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
