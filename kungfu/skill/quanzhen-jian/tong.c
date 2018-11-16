
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me, object target);
string name() { return "ͬ�齣��"; }

int perform(object me, object target)
{
        string weapon;
        int skill;
        int ap, dp, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("ͬ�齣��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("tonggui", me) )
                return notify_fail("������ʹ��ͬ�齣����\n");

        if( query("eff_qi", me)>query("max_qi", me)*2/3 )
                return notify_fail("��ö˶˵ģ����˼�ͬ���ʲô��\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦���޷�ʩչͬ�齣����\n");

        if( me->query_skill("xiantian-gong",1) < 100 )
                return notify_fail("������칦���δ�����޷�ʩչͬ�齣����\n");


        if( me->query_skill("sword") < 135 )
                return notify_fail("���ȫ�潣����Ϊ���㣬������ʹ��ͬ�齣����\n");

        if( query("neili", me) <= 100 )
                return notify_fail("�����������ʹ��ͬ�齣����\n");
        if( query("jingli", me) <= 150 )
                return notify_fail("��ľ�������ʹ��ͬ�齣����\n");


        msg = HIY"$Nʹ����ͬ�齣�����������ݺᣬֻ�����أ�����ƴ�����׺�Σ��֮����\n" NOR;
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("qi", target);
                target->receive_damage("qi", damage-10,me);
                target->receive_wound("qi", damage-10,me);
                msg += HIC "$n��æбԾ����������磬ֻ��һ�����ľ�ʹ������������ǰ����Ѫ�ɽ���\n"NOR;
                set("neili", 0, me);
        }
        else
        {
                me->start_busy(2);
                set("neili", 100, me);
                msg += HIY"����$n΢΢һЦ���������У�������䣬�������С�\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
