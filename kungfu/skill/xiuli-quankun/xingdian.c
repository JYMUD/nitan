// canyun // bren

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

int i; 
i = me->query_skill("xingyi-zhang", 1)/5;        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("���ǹ��㡹ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ʹ�á��ǹ��㡹ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 120 )
                return notify_fail("��������Ʋ�����죬����ʹ�á��ǹ��㡹��\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 120 )
                return notify_fail("�����Ԫ���ȼ�����������ʹ�á��ǹ��㡹��\n");

        if( (int)me->query_dex() < 25 )
                return notify_fail("���������ǿ������ʹ�á��ǹ��㡹��\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("�������޷�ʹ�á��ǹ��㡹���й�����\n");                                                                                
      

        if( query("neili", me)<700 )
                return notify_fail("����������̫��������ʹ�á��ǹ��㡹��\n");
        addn("neili", -300, me);
        addn("jingli", -40, me);
        message_vision(HIW "\n$N˫�ƽ����Ӧ,�������Ӱ�������ǰ���$n��Χ��˸������\n" NOR,me, target);

        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
if( (int)me->query_str() >(int)target->query_str()/2) 
{
        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);
msg =  HIW"$N����Ԫ�񹦷��ӵ����ޣ�һ˫���Ʒ���ҫ�۵Ĺ�â���û���������Ӱ��" NOR; 
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
addn("neili", -100, me);me->addn_temp("apply/str",-i);
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/damage", -i, me);
} 
  addn("neili", -400, me);me->addn_temp("apply/damage",-i);
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -i, me);me->start_perform(4,"��"HIW"�ǹ���"NOR"��");me->start_busy(1+random(2));return 1;}
