// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "ħ��Ѫɱ"; }

int perform(object me, object target)
{
        string msg;
        int ski_value, max_lv;
        int ap, dp, damage;
        int f = 0;

        ski_value = random(me->query_skill("mingyu-gong", 1));
        max_lv = me->query_skill("mingyu-gong", 1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ħ��Ѫɱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill("mingyu-gong", 1) < 500 )
                return notify_fail("������񹦹������㡣 \n");

        if( me->query_skill("force", 1) < 500 )
                return notify_fail("����ڹ������á� \n");

        if( query("neili", me)<1000 )
                return notify_fail("�������������\n");

        if (me->query_skill_mapped("force") != "mingyu-gong")
                return notify_fail("������û�м�������Ϊ�ڹ�������ʩչ��ħ��Ѫɱ����\n");

        msg = HIY "$N�Բм�����Ѫ��ת����ɱ����\n
            ����$N���Ϸ���һ��ǿ���ɱ������\n
    ��$N����ɱ���𽥵ؾۼ���˫��,��˫�����γ�����ħ����\n
            $Nٿ�ش��һ������ħ �� Ѫ ɱ����\n\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR BLINK "$NͻȻ��ͷһ��������ֻ��$N�������һ��Ѫ����$n��ȥ����\n
����ħ��ɱ֮
            ����ɱ�� ��ħ Ѫ �� ɱ��\n\n
$n�⵽ǰ��δ�еĴ��,��$NҲ���˲��ᡣ\n" NOR;

                damage = damage_power(me, "force");
                damage+= query("jiali", me);
                damage*=2;

                if (! target->is_busy())
                        target->start_busy( 3 + random(2) );
                target->receive_wound("jing", damage/2, me);
                //target->receive_wound("qi", damage, me);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200, msg);
                me->receive_wound("qi",query("qi", me)*1/10);
                addn("neili", -500, me);

                f = 1;
        }
        else if( random(4) > 2 )
        {
                msg += HIR BLINK"$N������ת����ɱ��������,�Ե��˺���Ӱ�졣\n" NOR;
                me->receive_wound("qi",query("qi", me)*1/100);
                addn("neili", -200, me);
        }
        else
        {
                msg += HIR BLINK"$n�ܵ�ǿ���ɱ���˺����������á�\n" NOR;
                me->receive_wound("qi",query("qi", me)*5/100);
                target->receive_damage("qi", (int)me->query_skill("mingyu-gong", 1), me);
                if (! target->is_busy())
                        target->start_busy(3);
                addn("neili", -300, me);
        }

        message_combatd(msg, me, target);
        if( f )
                COMBAT_D->report_status(target);
        me->start_busy(3 + random(2));
        return 1;
}

