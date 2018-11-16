// yingxiong.c

#include <ansi.h>
inherit F_SSERVER;

string name() { return "����Ӣ��"; }

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if( !objectp(target) ) { target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
            !me->is_fighting(target) ||
            !living(target) || query_temp("no_living", target) )
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("gender", me) != "����" && !wizardp(me) )
                return notify_fail("�����⸱����ǻ��Ҳ�������������ˡ����¸����ʵ�ɡ�\n");

        if( (int)me->query_skill("yingxiong-sanzhao", 1) < 150 )
                return notify_fail("���Ӣ�����в�����죬����ʹ��"+name()+"��\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("��Ļ����ڹ�������죬����ʹ��"+name()+"��\n");

        if( query("neili", me)<300 )
                return notify_fail("����������㣬����û����Ӣ���ˡ�\n");

        if( query_temp("shenlong/yingxiong", me) )
                return notify_fail("���Ѿ��ڴ��Ӣ�۵����ˣ�����������\n");

        level = me->query_skill("yingxiong-sanzhao", 1);
        addn("neili", -200, me);
        me->start_busy(1);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                message_combatd(HIY"$N"HIY"Խ��Խ�����ͣ�������������һ����������Ӣ�ۣ�������һ�ɺ�����$N�������𣬶�ʱ�����׺�������\n" NOR, me, target);
                set_temp("shenlong/yingxiong", 1, me);
                addn_temp("apply/attack", level, me);
                addn_temp("apply/unarmed_damage", level, me);
                if( !target->is_busy() )
                        target->start_busy(random(3)+1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, level:), 30);
        }
        else
        {
                message_combatd(HIG"�����е�$N����$n�󺰣���������������������δ�ˣ��ͱ�$n�ȵ���æ���ҡ�\n" NOR, me, target);
        }
        return 1;
}
void remove_effect(object me, int level)
{
        delete_temp("shenlong/yingxiong", me);
        addn_temp("apply/attack", -level, me);
        addn_temp("apply/unarmed_damage", -level, me);
        message_combatd(HIY"$NͻȻ�е��ĵ�һ��ʧ�䣺������Ӣ�ۣ������ڣ����һ��ˣ���ʱ������Ȼ��\n" NOR, me);
}

