// canyun // bren

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

int i; 
i = me->query_skill("xingyi-zhang", 1)/2;        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("������ͬ�ԡ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ʹ�á�����ͬ�ԡ�ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 180 )
                return notify_fail("��������Ʋ�����죬����ʹ�á�����ͬ�ԡ���\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 180 )
                return notify_fail("�����Ԫ���ȼ�����������ʹ�á��ǹ��㡹��\n");

        if( (int)me->query_dex() < 25 )
                return notify_fail("���������ǿ������ʹ�á�����ͬ�ԡ���\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("�������޷�ʹ�á�����ͬ�ԡ����й�����\n");                                                                                
      

        if( query("neili", me)<700 )
                return notify_fail("����������̫��������ʹ�á�����ͬ�ԡ���\n");
        addn("neili", -300, me);
        addn("jingli", -40, me);
        message_vision(CYN "\n$N˫��һ�꣬��˫��֮���γ�һ��ҫ�۵ġ�"HIW"����"CYN"����\n" NOR,me, target);

        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);
if( random(query("combat_exp", me))>query("combat_exp", target)/2 && 
         random((int)me->query_skill("force")) > (int)target->query_skill("force")/2)
{ 
msg = HIR"$N˫��������ǰ�����λ�������㽫��"HIW"����"HIR"������$n��̴��Ѩ��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
msg = HIG"������$N������ƣ�����һ�������¶�����Ϯ��$n��С����"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
 
msg = HIR"ֻ��$N���������������һԾ�����������������$n��ͷ����"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

msg = HIY"$N�ڿ���һ����ת��Я��"HIR"����֮��"HIY"��, ˫�ư���$n�ĵ��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

}
else 
{
msg = HIR"$N˫��������ǰ�����λ�������㽫��"HIW"����"HIR"������$n��̴��Ѩ��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
msg = HIG"������$N������ƣ�����һ�������¶�����Ϯ��$n��С����"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
 
msg = HIR"ֻ��$N���������������һԾ�����������������$n��ͷ����"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
me->start_perform(5,"��"HIR"����ͬ��"NOR"��")  ; 
call_out("perform2", 3, me, target);  
} 
message_vision(YEL "\n$Nһʽ������ͬ�ԡ����ӵ����쾡�£�˫��һ�֣��������У����ı�����
\n" NOR,me, target);     
       addn("neili", -400, me);
        addn_temp("apply/dex", -i, me);
        addn_temp("apply/damage", -i, me);
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -i, me);me->start_perform(5,"��"HIR"����ͬ��"NOR"��");me->start_busy(2+random(2));

        return 1;
}
int perform2(object me, object target)
{ 
   string msg;
   int i; 
 i = me->query_skill("xingyi-zhang", 1)/2; 
if (!me || !target) return 0;
        if(!living(target)) 
          return notify_fail("�����Ѿ�������ս���ˡ�\n");  

        if( query("neili", me)<300 )
               return notify_fail("���Ҫ�ٳ��ڶ�����ȴ�����Լ������������ˣ�\n");
        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);
msg = HIY"$N�ڿ���һ����ת��Я��"HIR"����֮��"HIY"��, ˫�ư���$n�ĵ��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
 
msg = HIC"ֻ��$Nб���ת�������ĳ����ƣ�����������ֱָ$n��в��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

msg = HIW"$N����Ԫ�񹦷��ӵ����ޣ��û���������Ӱ����$nȫ�����ֹ�ȥ��"NOR;
COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);



 addn("neili", -400, me);
        addn_temp("apply/dex", -i, me);
        addn_temp("apply/damage", -i, me);
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -i, me);me->start_perform(5,"��"HIR"����ͬ��"NOR"��");me->start_busy(2+random(2));

        return 1;
}

