// Code of ShenZhou
// jingsuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jing, jing1, eff_jing;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("��Ҫ��ȡ˭�ľ���\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ս�����㲻����ʹ�û��������˵ľ���\n");

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("��Ļ����󷨹���������������ֲ���ʩ�û��������˾���\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է��ľ���\n");

        if( (int)me->query_skill("huagong-dafa",1) < 45 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է��ľ���\n");

        if( query("neili", me)<50 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

        if( query("jingli", me)<20 )
                return notify_fail("��ľ�������������ʹ�û����󷨡�\n");

        if( query("jing", target)<query("max_jing", target)/5
          || query("jingli", target)<query("max_jingli", target)/10 )
                return notify_fail( target->name() +
                        "�Ѿ������ɢ�����Ѿ��޷�����������ȡ�����ˣ�\n");

        message_vision(
                HIR "$NͻȻ���ص�һЦ��˫��һǰһ���׼$n��̫��Ѩ���˹�����\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "���;������������̰��ʹ����־������ͷ����һƬ�հף�\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "�ľ���������ԴԴ���������˽�����\n" NOR);

                target->receive_damage("jing", (int)me->query_skill("huagong-dafa", 1)/5 );

                if( query("eff_jing", me)<query("max_jing", me) )
                        me->receive_curing("jing", (int)me->query_skill("huagong-dafa", 1)/10);
                else addn("jing", me->query_skill("huagong-dafa",1)/5, me);

                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(random(3));
                target->start_busy(random(3));
                addn("neili", -me->query_skill("huagong-dafa",1)/6, me);
                addn("jingli", -5, me);

                call_out("del_sucked", 2, me);
        }
        else
        {
                addn("neili", -20, me);
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                me->start_busy(3);
                call_out("del_sucked", 4, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}
