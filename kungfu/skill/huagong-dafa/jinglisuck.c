// Code of JHSH
// jinglisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jl;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("��Ҫ��ȡ˭�ľ�����\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ս�����㲻����ʹ�û��������˵ľ�����\n");

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ��������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("������ֲ��ܹ���ȡ���˵ľ�����\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է��ľ�����\n");

        if( (int)me->query_skill("huagong-dafa",1) < 90 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է���������\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

        if( query("jingli", me)<100 )
                return notify_fail("��ľ�������������ʹ�û����󷨡�\n");

        if( query("jingli", me) >= query("max_jingli", me)*5/2 )
                return notify_fail("����ȡ�ľ�������ȫ���޷�����ȡ������\n");

        if( query("max_jingli", target) <= 0 )
                return notify_fail( target->name() +
                        "û���κξ�����\n");

        if( query("jingli", target)<query("max_jingli", target)/10 )
                return notify_fail( target->name() + "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κξ����ˣ�\n");


        message_vision(HIR "$N��$n΢΢һЦ��ͻȻ���Ʊ�צ������$n������\n\n" NOR, me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "�����ڻ���Ѩ��" + me->name() + "ͻȻ��ס���������ã�ֻ���������ˮ���Ի���Ѩ���ڶ�����\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "�ľ���������ԴԴ���������˽�����\n" NOR);

                jl = (1+random(3)) * (int)me->query_skill("huagong-dafa", 1)/2;
                if( query("jingli", target)>jl )
                {
                        addn("jingli", -1*jl, target);
                        addn("jingli", jl, me);
                }else{
                        addn("jingli", jl/2, me);
                        addn("jingli", -jl/2, target);
                        }
                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                addn("neili", -me->query_skill("huagong-dafa",1)/6, me);
                addn("jingli", -5, me);

                call_out("del_sucked", 2, me);
        }
        else
        {
                message_vision(HIY "����$p������$P����ͼ��û��$P��ס����\n" NOR, me, target);
                addn("jingli", -20, me);
                me->start_busy(2+random(2));
                call_out("del_sucked", 5, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}