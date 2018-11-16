// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIW "�ƾ���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage, p;
        string pmsg;
        string msg;
        object weapon, weapon2;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me) )
            || query("skill_type", weapon) != "throwing" )
                return notify_fail("������û�����Ű���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 180)
                return notify_fail("�㵯ָ��ͨ��Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("throwing", 1) < 180)
                return notify_fail("�����������Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2400 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -300, me);
        weapon->add_amount(-1);

        msg = HIW "����$N" HIW "˫Ŀ�������䣬�����ƿ���������һ" +
              query("base_unit", weapon)+weapon->name()+HIW"��"
              "ָ�ⵯ������������$n" HIW "��\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("throwing");
        dp = defense_power(target, "dodge") + target->query_skill("parry");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");

                msg+=HIR"ֻ����"+query("base_unit", weapon)+
                       weapon->name() + HIR "����Ѹ��֮����$n" HIR
                       "������Ͼ���ܣ������л������У�\n" NOR;

                target->receive_wound("qi", damage + fmsk, me); 
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+300);

                if( (weapon2=query_temp("weapon", target) )
                && ap / 3 + random(ap) + fmsk / 2 > dp) 
                {
                        msg += HIW "$n" HIW "����һ�飬����" + weapon2->name() +
                               HIW "�������ֶ�����\n" NOR;
                        weapon2->move(environment(me));
                }

                p=query("qi", target)*100/query("max_qi", target);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "���ϵ�$P" CYN "�д�һ�ţ���"
                       "æ����Ծ�𣬶���������\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}
