#include <ansi.h>
#include <combat.h>

string name() { return HIM "һ��һ����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;

        if( !query("reborn/times", me) ) 
                return notify_fail("����δת���������޷�ʹ��" + name() + "��\n"); 
                
        if( !target) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");
        
        if( me->is_busy() )
                return notify_fail("������æ���ء�\n"); 

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("����������û�����Ű���������ʩչ" + name() + "��\n");

        if( (skill = me->query_skill("tangmen-throwing", 1)) < 800 )
                return notify_fail("������Ű���������죬����ʩչ" + name() + "��\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 800 )
                return notify_fail("��Ĳ�����������죬�޷�ʩչ" + name() + "��\n");

        if( (int)me->query_skill("force") < 800 )
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me) < 1500 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if( !living(target) )
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -1000, me);

        msg = HIM "\n$N" HIM "����ͻȻ����һ֧�����������ޣ�$n" HIM "�����е���ˣ�\n"
              HIM "$n" HIM "��֪�����н�����һ��һ�����С�\n" NOR;

        ap = attack_power(me, "throwing") * 2;
        dp = defense_power(target, "parry") + defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1) * 10;

        message_combatd(msg, me, target);

        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)
        {
                msg = HIR"�ǻ�Խ��Խ�ޣ�һ��һ���磬һľһ������$n"HIR"΢Ц�ŵ����ˣ��ǻ�Ҳл�ˡ�\n" NOR;
                weapon->hit_ob(me,target,query("jiali", me)+200);
                //weapon->move(target);
                weapon->add_amount(-1);

                message_combatd(msg, me, target);
                target->receive_damage("qi", query("max_qi", target), me);
                target->receive_wound("qi", query("max_qi", target), me);
                COMBAT_D->report_status(target);
/*
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
*/
                me->start_busy(2);
        } else
        {
                msg = HIR "Σ��ʱ�̣�$n " HIR "����һ��һ�������ӻ��������жݳ����ǻ����ն�����ֻ������һ�����죬�ǻ�л�ˣ���������ڵ����ϡ�\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                //weapon->move(environment(me));
                weapon->add_amount(-1);
                
                me->start_busy(3);
                target->set_weak(10);
                target->affect_by("poison", 
                        ([ "level" : 8000, 
                           "id":query("id", me), 
                           "name" : "���Ż���", 
                           "duration" : 200 ])); 
                tell_object(target, HIG "����������һ��һ����Ļ�����\n"); 
        }
        return 1;
}


