// sheshen.c ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "����"; }

int perform(object me, object target)
{
        mapping skill_status;
        string msg, *sname;
        object weapon;
        int exp, shen, mine, count;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->is_ghost() || query("eff_qi", me)<0 )
                return notify_fail("���Ѿ����ˡ�\n");


        if( me->is_busy() )
                return notify_fail("������æ���أ�ʹ������һ�С�\n");


//        if( !me->query("yinliting_teach") )
//                 return notify_fail("��δ�ý������ڣ�����ʹ������\n");

        if( (int)me->query_skill("strike") < 250 )
                return notify_fail("���Ӣ�����м�������죬����ʹ������\n");
//        if( me->query("neili") >= 100 || me->query("qi") >= 200)
//                                               return notify_fail("��δ��ɽ��ˮ��֮�أ������ô˺��У�\n")
        if( (int)me->query_skill("shenlong-xinfa", 1) < 250 && (int)me->query_skill("busi-shenlong", 1) < 250 )
                return notify_fail("����ڹ���Ϊ����������ʹ������\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" &&
            me->query_skill_mapped("force") != "busi-shenlong" )
                return notify_fail("�����õ��ڹ���Ӣ��������·��㣣�\n");

        if( query("combat_exp", me)<500000 )
                return notify_fail("��ʵս���鲻�㣬����ʹ������\n");

        if( query("shen", target)>10000 )
                shen=-query("shen", me)/50;
        else shen=query("shen", me)/50;

        exp=query("combat_exp", me)/100;

        msg = HIW"$Nһ����Х�����Ŵ󿪣�ȫ��ײ��$n"+HIW"���Ѿ���ƴ���Ĵ򷨣�����\n"NOR;

        mine=random(query("combat_exp", me)-query("shen", me));

        if( mine>query("combat_exp", target)/3*2 )
        {
                msg += HIR"$n"+HIR"⧲�����֮�£���$N�˸����ţ�ֻ�����������ޱȣ�ȴ�ֻ��������ã�\n�̲�ס�˷���һ���������ĲҽУ�����$n��Ŀ����������£�����ǰ����������ֹͣ�ˡ�\n���˶��ľ����е�������ֻ���¾��Ķ��ǵı���һĻ������\n" NOR;
                message_combatd(msg, me, target);
                addn("max_neili", -(30+random(30)), me);
                addn("combat_exp", -exp, me);
                addn("shen", shen, me);
                me->receive_wound("qi",query("max_qi", me)+200, target);
                target->receive_wound("qi",query("max_qi", target)+200, me);
                me->start_busy(3 + random(3));
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
                set_temp("die_reason", "��"+target->name(1)+"ͬ���ھ�", me);
                set_temp("die_reason", "��"+me->name(1)+"ͬ���ھ�", target);
                me->die();
                target->die();
                return 1;

        }
        else
        {
                msg += HIC "$n" HIC "����$N" HIC "�ô���������æ���ң��Ǳ���״�Ķ�����ȥ�������ŵ������������һ�󶯵����á�\n"NOR;
                message_combatd(msg, me, target);
                me->receive_wound("qi",query("max_qi", me)+200, target);
                me->start_busy(3);
                me->die(target);
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
                return 1;

        }

        return 1;
}