// wuqing.c ��Ůȭ-��Ů����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��Ů����" NOR; }

int perform(object me, object target)
{
        object ob;
        string msg;
        int damage,jiali,married,ap,dp;

        jiali=query("jiali", me);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��Ů����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("������ȷ������еı�����\n");

        if( query("gender", me) != "Ů��" )
                return notify_fail("��Ů����ֻ��Ů�Բ��ܹ�ʹ�á�\n");

        if( (int)me->query_skill("meinv-quan", 1) < 400 )
                return notify_fail("�����Ůȭ���𲻹�������ʹ����Ů���顣\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ���δ��죬��������Ů���顣\n");

        if( query("neili", me)<600 )
                return notify_fail("����������̫��������ʹ����Ů���顣\n");

        if( query("jingli", me)<200 )
                return notify_fail("�����ھ���̫��������ʹ����Ů���顣\n");

        msg = HIB "\n\n$N�����߶�������ȭ���ݺ����飡\n"NOR;
        msg += HIY "\n$N����֧�ã���������ӳ�����̾һ�������ּ���֮�⣬������ʹ��ɱ�С�\n\n"NOR;

        ap=attack_power(me, "unarmed");
        dp=defense_power(target, "force");

        if( mapp(query("family", target)) && query("family/family_name", target) == "ȫ���" )
                ap += ap/3;

        if( ap/2 + random( ap ) > dp || !living(target) )
        {
                damage = damage_power(me, "unarmed");

                //�жϽ������ͷ�������Ϊ�Ĵ���
                if( !mapp(query("couple", me)))married=1;
                else married=query("couple/married", me);
                if( mapp(query("sex", me)))married+=query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;

                addn("neili", -200, me);
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage*2/3), me);
                target->start_busy(0);

                if ( damage < 1000) {
                        msg += HIR"ֻ�����һ����$n��һȭ����С������Ѫ��ӿ��ڶ�����\n"NOR;
                }else if ( damage < 1800) {
                        msg += HIR"ֻ���顢��������$n���۷��ࡢ���۷��ϣ���Ѫֱ����\n"NOR;
                }else if ( damage < 2600) {
                        msg += HIR"ֻ���顢�顢�������죬$nͷ�����ز�������ͬʱ�����ػ��У���Ѫ���硣\n"NOR;
                }else {
                        msg += HIR"ֻ���顢�顢�顢��������ﲻ����$nֱ����ù������ѷ��˳�ȥ��\n"NOR;
                }
                msg += NOR;
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$n���һ�֣�����Ծ�𣬱��ܵķ�Ӧ��$n�ӹ��˽١�\n\n"NOR;
                addn("neili", -100-query("jiali", me), me);
                me->start_busy(2 + random(2));
                message_combatd(msg+"\n", me, target);
                return 1;
        }

        message_combatd(msg+"\n", me, target);
        COMBAT_D->report_status(target);
        return 1;
}
