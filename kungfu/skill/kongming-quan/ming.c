
#include <ansi.h>

inherit F_SSERVER;

string name() { return "��̨����"; }

int perform(object me, object target)
{
        object weapon;
        int damage,skill,wap,wdp;
        string *limb, type, result, str,msg;

        type = "����";

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("��̨����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("sanhua", me) )
                return notify_fail("������ʹ�������۶��ˣ�\n");

        if( query_temp("kongming", me) )
                return notify_fail("������ʹ����̨�����ˣ�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���ֲ���ʩչ��̨������\n");

        if( me->query_skill_mapped("unarmed") != "kongming-quan" )
                return notify_fail("�����õĲ��ǿ���ȭ������ʩչ��̨������\n");

        if( me->query_skill_prepared("unarmed") != "kongming-quan" )
                return notify_fail("�������Ĳ��ǿ���ȭ������ʩչ��̨������\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦��ʩչ������̨������\n");
        */

        if( me->query_skill("force") < 100 )
                return notify_fail("������칦���δ�����޷�ʩչ��̨������\n");

        if( me->query_skill("unarmed") < 100 )
                return notify_fail("��̨������Ҫ��տ�Ŀ���ȭ������Чʩչ��\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�����������ʹ����̨������\n");

        if( query("jing", me) <= 200 )
                return notify_fail("��ľ�����ʹ����̨������\n");


        msg = HIY"$N����һ������Ŀ����Ȼ�峺�ޱȣ�����˫ȭʮ�ֽ���������$n���˹�ȥ��\n\n"NOR;
        message_vision(msg, me, target);

        set_temp("kongming", 1, me);

        skill =  ( me->query_skill("unarmed")
                + me->query_skill("force") ) / 3;

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/unarmed_damage", skill/6, me);
        addn_temp("apply/dodge", skill/2, me);
        addn_temp("apply/parry", skill/2, me);
        addn_temp("apply/defense", skill/2, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -skill/2, me);

        addn("jing", -100, me);
        me->start_busy(random(2));

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill/10);

        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/unarmed_damage", -amount/3, me);
        addn_temp("apply/parry", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        addn_temp("apply/defense", -amount, me);
        delete_temp("kongming", me);
        message_vision(HIY "\n$N����һ�������������ջص��\n\n" NOR, me);

        return;
}