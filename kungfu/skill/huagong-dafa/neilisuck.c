// Code of ShenZhou
// neilisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int dmg;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("��Ҫ��ȡ˭��������\n");

       if( query("no_fight", environment(me)) )
              return notify_fail("���ﲻ��ս�����㲻����ʹ�û��������˵�������\n");

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ��������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʩ�û���������������\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է���������\n");

        if( (int)me->query_skill("huagong-dafa",1) < 60 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է���������\n");

        if( query("neili", me)<50 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

        if( query("jingli", me)<20 )
                return notify_fail("��ľ�������������ʹ�û����󷨡�\n");

        if( query("neili", me) >= query("max_neili", me)*2 )
                return notify_fail("����ȡ����������ȫ���޷�����ȡ������\n");

        if( query("max_neili", target) <= 1 )
                return notify_fail( target->name() +
                        "û���κ�������\n");

        if( query("neili", target)<query("max_neili", target)/10 )
                return notify_fail( target->name() +
                        "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κ������ˣ�\n");

        message_vision(
                HIW "$Nһ����ͻȻ��òҰף�����ֱ�����͵ض�׼$n�����д�Ѩ������ȥ��\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                message_vision(
                        HIR "$N�پ�����΢ʹ����ͬ��������˸�С�ף�ȫ��������ˮ����ѭ�׷�й������\n\n" NOR,
                        target );

                tell_object(me, HIG "�����" + target->name() + "������������ԴԴ���������˽�����\n" NOR);

                if( query("neili", target)>me->query_skill("force") )
                {
                        addn("neili", -1*me->query_skill("force"), target);
                        addn("neili", 2*(me->query_skill("force")), me);
                }else{
                        addn("neili", 2*query("neili", target), me);
                        set("neili", 0, target);
                }

                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                    set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                addn("neili", -me->query_skill("force")/7, me);
                addn("jingli", -5, me);

                COMBAT_D->report_status(target);

                call_out("del_sucked", 1+random(2), me);
        }
        else
        {
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                addn("jingli", -10, me);
                me->start_busy(1 + random(3) );
                call_out("del_sucked", 2+random(3), me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}