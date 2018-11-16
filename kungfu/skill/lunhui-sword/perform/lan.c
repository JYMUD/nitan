#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "������" NOR; } 

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("lunhui-sword", 1) < 600)
                return notify_fail("��������ֻؽ�������죬����ʩչ" + name() + "��\n");

        if( query("neili", me)<3000 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("��û�м��������ֻؽ�������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "��������" + weapon->name() + HIG "����������䣬�����������䣬�����ɾ������� ����\n" NOR;

        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "dodge");

        attack_time = 6;
        count = ap / 10;
        
        if (me->query_skill("lunhui-sword", 1) >= 800)
                count *= 2;

        if (me->query_skill("lunhui-sword", 1) >= 1600)
                count *= 2;
                
        addn_temp("apply/attack", count/2, me);
        addn_temp("apply/damage", count, me);
        
        message_combatd(msg, me, target);

        addn("neili", -3000, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy()) target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count/2, me);
        addn_temp("apply/damage", -count, me);
        
        me->start_busy(3 + random(2));

        return 1;
}
