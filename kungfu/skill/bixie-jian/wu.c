// sanqing.c  һ��������
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

#define PNAME "��Ⱥħ���衹"
inherit F_SSERVER;
 
int perform(object me, object target)
{
  object weapon, ob;
        string msg, string1;
        int count,sword_lvl;
        int  i , j;
        int flag;
        string fskill,sskill,bskill,pfname;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname) )
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  if( !objectp(weapon=query_temp("weapon", me)) || 
    query("skill_type", weapon) != "sword" )
    return notify_fail(PNAME"�������Ž����ܳ���\n");
  if (!userp(me)) return notify_fail("npc��������ʹ�����С�\n");
        fskill = "kuihua-xinfa";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("���"+to_chinese(fskill)+"��򲻹���ʹ����"+PNAME+"��\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("���"+to_chinese(sskill)+"�������ң��޷�ʹ��"+PNAME+"��\n");
  if( query("neili", me)<100 )
    return notify_fail("�������������\n");
  msg =  HIM "$N" HIM "Ĭ�˿����ķ������α������ޱȣ�������$n"
              HIM "�������У�\n" NOR;
  message_combatd(msg, me,target);

        sword_lvl = me->query_skill(sskill,1)/15; 
        count = (me->query_skill(sskill,1)-1)/100; 

  for(i=0;i<count+2;i++)
  {
    if (flag == 1) target = offensive_target(me);
    if (!objectp(target)) break;
     addn_temp("apply/attack", sword_lvl, me);
    addn_temp("bixie_hit", 1, me);
    if( i)set_temp("action_flag", 1, me);
    COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
                addn_temp("bixie_hit", -1, me);
    set_temp("action_flag", 0, me);
  }
  addn_temp("apply/attack", -i*sword_lvl, me);
  
  addn("neili", -50, me);
  me->start_busy(1);

  if(flag!=1 && !target->is_fighting(me)) target->fight_ob(me);
  return 1;
}
string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
  write(@HELP

        ʹ�ù�Ч��
                ��������

        ����Ҫ��
                �����ķ�100��
                ��а����101��
                ����100
HELP
  );
  return 1;
}