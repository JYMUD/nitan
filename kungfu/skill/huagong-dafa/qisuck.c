// Code of ShenZhou
// qisuck.c

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
                return notify_fail("���ﲻ��ս�����㲻����ʹ�û��������˵ľ�����\n");

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ��������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("������ֲ��ܹ���ȡ���˵ľ�����\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է���������\n");

        if( (int)me->query_skill("huagong-dafa",1) < 50 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է���������\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������ʹ�û����󷨡�\n");

       if( query("jingli", me)<30 )
                return notify_fail("��ľ�������������ʹ�û����󷨡�\n");

        if( query("qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�����ˣ�\n");

        message_vision(
                HIB "$NͻȻ�����һЦ��˫��һ�Ĵָ��׼$n�����İ��˹�����\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "��ͻȻ����ȫ�����������Ʊ�ӿ��������֫��������Ҳʹ����������\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "������������ԴԴ���������˽�����\n" NOR);
                message_vision(
                        HIR "$N����ȫ�����������Ʊ�ӿ��������֫��������Ҳʹ����������\n\n" NOR,
                        target );

                addn("qi", me->query_skill("force"), me);

                if( query("combat_exp", target) >= query("combat_exp", me)/2 )
                        addn("combat_exp", 1, me);

                me->start_busy(random(2));
                target->start_busy(random(2));
                addn("neili", -me->query_skill("force")/6, me);
                addn("jingli", -5, me);

                dmg=random(me->query_skill("force")/100)*query("neili", me)/10;
                if( dmg > 2000) dmg=2000;
                if( dmg <100) dmg=100;
                dmg = random(dmg);
                target->receive_damage("qi", dmg, me );
                target->receive_wound("qi", random(dmg), me);

                COMBAT_D->report_status(target);

                call_out("del_sucked", 1, me);
        }
        else
        {
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                addn("jingli", -10, me);
                me->start_busy(2);
                call_out("del_sucked", 2+random(2), me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}
