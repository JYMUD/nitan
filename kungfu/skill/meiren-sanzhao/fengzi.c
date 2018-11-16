// fengzi.c

#include <ansi.h>
inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() ||
                  !me->is_fighting(target) ||
          !living(target) || query_temp("no_living", target) )
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (query("gender", me) != "Ů��" || me->query_per()<20) && !wizardp(me) )
                return notify_fail("�����⸱���ݣ���������ô����Ҳû�˶࿴��һ�۵ġ�\n");

        if( query("gender", target) != "����" )
                return notify_fail("��ô�ˣ���Ū��ɧҲҪ�Ҹ���ȷ����ɣ�\n");

        if( level = me->query_skill("meiren-shanzhao", 1) < 150 )
                return notify_fail("����������в�����죬����ʹ��"+name()+"��\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("����ڹ�������죬����ʹ��"+name()+"��\n");

        if( query("neili", me)<300 )
                return notify_fail("����������㣬����û����ʲô�����ˡ�\n");

        if( query_temp("shenlong/fengzi", target) )
                return notify_fail("���Ѿ�������㵹�ˣ��㻹�˷�ʲô���飿\n");

        addn("neili", -200, me);
        me->start_busy(1);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIC"�����У�ȴ��$N"HIC"æ�в��ң�����$n"HIC"����չ��¶��һЦ���˵����������������ϼ����ɫ�������ޣ�\n"
                        "$n���в���һ������Ȼ����һ���׽��ĸо�������Ҳ������ã������\n" NOR, me, target);
                set_temp("shenlong/fengzi", 1, target);
                addn_temp("apply/defense", -level, target);
                if( !target->is_busy() )
                        target->start_busy(random(3)+1);
                target->start_call_out( (: call_other, __FILE__, "remove_effect", target, level:), 30);
        }
        else
        {
                message_combatd(HIY"ֻ��$N"HIY"����$n"HIY"����¶��һЦ��¶����������һ˿û����ȥ��"HIG"��Ҷ"HIY"��\n" NOR, me, target);
        }
        return 1;
}
void remove_effect(object target, int level)
{
        delete_temp("shenlong/fengzi", target);
        addn_temp("apply/defense", level, target);
        message_combatd(HIG"$N��ã�������Ȼһ������ͷ�͵�һ��æ��£����������\n" NOR, target);
}

