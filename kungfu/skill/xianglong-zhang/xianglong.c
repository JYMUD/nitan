// xianglong ������
// Last Modified by Winder on Oct. 20, 2000

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int amount);
#define PNAME "������"
int perform(object me,object target)
{
        int skill, count;
        object weapon;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
/*
        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

*/
        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ý����󷨡�\n");
                
        if( query_temp("xianglong", me) )
                return notify_fail("���Ѿ����˽��������ˡ�\n");

        count = me->query_str();
        skill = me->query_skill("strike", 1);
        fskill = "huntian-qigong";
        bskill = "strike";
/*
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
*/
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("���"+to_chinese(fskill)+"��Ϊ������ʹ��"+PNAME+"��\n");

        if( (int)me->query_skill(sskill, 1) < 80 )
                return notify_fail("���"+to_chinese(sskill)+"��Ϊ������ʹ��"+PNAME+"��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        addn("neili", -100, me);
        message_combatd( HIR "$N����һ�������������󷨣����ԽսԽ�£�\n" NOR, me);

        set_temp("xianglong", 1, me);
        addn_temp("apply/str", count/5, me);
        me->start_call_out( (: call_other,  __FILE__, "remove_effect", me , count/5 :), (int)(skill/6) );

        return 1;
}

void remove_effect(object me,int amount)
{
        int dmount;
        if( query_temp("xianglong", me) )
        {
        addn_temp("apply/str", -amount, me);
        delete_temp("xianglong", me);
        tell_object(me, CYN"��Ľ�����������ϣ��������ջص��\n"NOR);
        }
}
string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                ��ǿ�Լ��Ĺ�����

        ����Ҫ��
                ��������100��
                ����ʮ����80��
                ����300
HELP
        );
        return 1;
}
