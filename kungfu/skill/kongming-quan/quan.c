
#include <ansi.h>

inherit F_SSERVER;

string name() { return "��ȭ����"; }

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
                return notify_fail("��ȭ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���ֲ���ʩչ��ȭ���裡\n");

        if( me->query_skill_mapped("unarmed") != "kongming-quan" )
                return notify_fail("�����õĲ��ǿ���ȭ������ʩչ��ȭ���裡\n");

        if( me->query_skill_prepared("unarmed") != "kongming-quan" )
                return notify_fail("�������Ĳ��ǿ���ȭ������ʩչ��ȭ���裡\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦��ʩչ������ȭ���裡\n");
        */

        if( me->query_skill("force") < 120 )
                return notify_fail("������칦���δ�����޷�ʩչ��ȭ���裡\n");

        if( me->query_skill("unarmed") < 120 )
                return notify_fail("��ȭ������Ҫ��տ�Ŀ���ȭ������Чʩչ��\n");

        if( query("max_neili", me) <= 1000 )
                return notify_fail("��������ȼ�����ʹ����ȭ���裡\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("��������������޷�����ʩչ��ȭ���裡\n");

        msg = HIY"$N�ſ�һ�����ȣ�˫Ŀ�������䣬��������Ʈ��������˫ȭ�û�������ȭӰ������$n���ֹ�ȥ��\n\n"NOR;
        message_combatd(msg, me, target);

        skill =  me->query_skill("unarmed");

        addn_temp("apply/unarmed_damage", skill/2, me);
        addn_temp("apply/attack", skill/2, me);

        message("vission",HIR  "��һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "��һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "��һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "��һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "ǰһȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "��һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "�����һȭ��\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        me->start_busy(3);

        addn_temp("apply/unarmed_damage", -skill/2, me);
        addn_temp("apply/attack", -skill/2, me);

        addn("neili", -skill, me);

        return 1;
}