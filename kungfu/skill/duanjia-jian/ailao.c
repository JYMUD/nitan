// ailao.c ����ɽ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "����ɽ����"; }

int perform(object me, object target)
{
        object weapon;
        int i, a;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("�㲻��ս���У�\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɢ�\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("�������޽������ʹ�ó�����ɽ���⣿\n");

        if (me->query_skill("kurong-changong", 1)<150)
                return notify_fail("����ڹ����δ�����޷���Ԧ����ɽ���⣡\n");

        if (me->query_skill("sword", 1) < 150)
                return notify_fail("�㽣����Ϊ�������޷�ʩչ����ɽ���⣡\n");

        if (me->query_skill("duanjia-jian",1)<150)
                return notify_fail("��μҽ���Ϊ�������޷�ʩչ����ɽ���⣡\n");

        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�����õ��ڹ��밧��ɽ������·��㣣�\n");

        if( query("neili", me) <= 500 )
                return notify_fail("�����������ʹ�ð���ɽ���⣡\n");

        message_vision(HIR "\nͻȻ��$N����ͻ�䣬�����ݺᣬ����������������ǰ����������������������\n\n"NOR, me, target);
        message_vision(HIR "\n��������ʩչ����ɽ�����$n����ʵʵ��������ʮ������\n\n" NOR, me, target);

        if( query("combat_exp", me)*10/query("combat_exp", target)<12 )
                a=3;
        else {
                if( query("combat_exp", me)*10/query("combat_exp", target)<15 )
                        a=4;
                else {
                        if( query("combat_exp", me)*10/query("combat_exp", target)<18 )
                                a=5;
                        else a=6;
                }
        }

        for (i=1; i<=a; i++)
                COMBAT_D->do_attack(me, target, weapon);


        if (a>4)
        {
                me->start_busy(a-random(3));
        } else
                me->start_busy(1);

        addn("neili", -200, me);
        addn("jing", -20, me);
        return 1;
}