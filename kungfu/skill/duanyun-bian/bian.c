
#include <ansi.h>

inherit F_SSERVER;
string name() { return "���Ʊ�ɫ"; }

int perform(object me, object target)
{
        int skill,power;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("���Ʊ�ɫֻ�ܶ�ս���еĶ���ʹ�á�\n");


         /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                 return notify_fail("�����õĲ����������칦��ʩչ�������Ʊ�ɫ��\n");
         */

        if( me->query_skill("force") < 140 )
                return notify_fail("��Ļ����ڹ����δ�����޷�ʩչ���Ʊ�ɫ��\n");

        if( me->query_skill("whip") < 135 )
                return notify_fail("���Ʊ�ɫ��Ҫ��տ�Ķ��Ʊ޷�������Чʩչ��\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("�㲢û��װ������Ϊ������\n");

        power=random(query("neili", me)/50)+query("jiali", me)/2;
        if(power<150) power=150;
        if(power>1000) power=1000;

        if( query("neili", me) <= 200+power*2 )
                return notify_fail("�����������ʹ�÷��Ʊ�ɫ��\n");

        message_combatd(HIW"$N�����������͵�һ��"NOR+"$n"+HIW"�����ޱ߷����������գ�һ��"NOR+HIM"�"NOR+HIW"���������Ӱ����ǵص������Ϯ����\n\n"NOR,me,query_temp("weapon", me));

        addn_temp("apply/attack", power/2, me);
        addn_temp("apply/damage", power/5, me);
        addn_temp("apply/armor", -power/2, target);
        addn_temp("apply/dodge", -power, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn_temp("apply/attack", -power/2, me);
        addn_temp("apply/damage", -power/5, me);
        addn_temp("apply/armor", power/2, target);
        addn_temp("apply/dodge", power, target);

        addn("neili", -power*2, me);
        me->start_busy( 2+random(2));

        return 1;
}

