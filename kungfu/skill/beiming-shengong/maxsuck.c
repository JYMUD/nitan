// This program is a part of NITAN MudLIB
// maxsuck.c

#include <ansi.h>

inherit F_SSERVER;
int exert(object me, object target)
{
        int ap, dp, suck;

        if (target == me) target = offensive_target(me);

        if (me->is_busy()) return notify_fail("����æ���ء�\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if( !objectp(target) || query("id", target) == "muren" )
                return notify_fail("��Ҫ��ȡ˭�ĵ�Ԫ��\n");
                
        if( query("race", target) != "����" )
                return notify_fail("����ˣ�ֻ���˲����е�Ԫ��\n");
       
        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ����Ԫ��\n");
        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʩ�ñ�ڤ�����˵�Ԫ��\n");

        if ((int)me->query_skill("beiming-shengong", 1) < 90)
                return notify_fail("��ı�ڤ�񹦹���������������ȡ�Է��ĵ�Ԫ��\n");

        if( query("neili", me)<20 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

        if( me->query_skill("beiming-shengong",1)<query("max_neili", me)/20 )
                return notify_fail("��ı�ڤ��̫���ˣ�����ȡҲ��ͽ�͡�\n");
                
        if( query("max_neili", me)*2 >= me->query_neili_limit()*3 )
                return notify_fail("���������Ϊ�ƺ��Ѿ��ﵽ��ƿ��������ȡҲ��ͽ�͡�\n"); 

        if( query("max_neili", target)<100 || query("no_suck", target) )
                return notify_fail(target->name() +
                        "��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

        if( query("max_neili", target)<query("max_neili", me)/18 )
                return notify_fail(target->name() +
                        "���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

        message_combatd(
                HIG "$N��$n΢΢һЦ��ͻȻ���Ʊ�צ������$n������\n\n" NOR,
                me, target );
                
        me->want_kill(target);               
        if (living(target))
        {
                if (! target->is_killing(me))
                        target->kill_ob(me);
        }
        set_temp("sucked", 1, me);

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp || ! living(target))
        {
                tell_object(target, HIR "��ֻ��ȫ������ȫ��������ѩ����ʧ����Ӱ���٣�\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "�ĵ�Ԫ������ԴԴ���������˽�����\n" NOR);
                
                suck = 100 + (me->query_skill("beiming-shengong", 1) - 90) / 2;
                
                addn("max_neili", -suck, target);
                addn("max_neili", suck, me);
                if( query("max_neili", target)<1 )
                        set("max_neili", 0, target);

                me->start_busy(7);
                if (! target->is_busy())
                target->start_busy(7);
                addn("neili", -10, me);
                // remove_call_out("del_sucked");
                call_out("del_sucked", 10, me);
        }
        else
        {       
                message_combatd(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                me->start_busy(2 + random(5));
                // remove_call_out("del_sucked");
                call_out("del_sucked", 15, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if (! me) return;
        
        if( query_temp("sucked", me) )
                delete_temp("sucked", me);
}

