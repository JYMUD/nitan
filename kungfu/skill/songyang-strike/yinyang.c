// Last Modified by winder on Jul. 15 2001
// yinyang.c

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "������"
int perform(object me, object target)
{
        string msg;
        int skill, damage;
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

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
                
        if( query_temp("weapon", me) )
                return notify_fail("��ֻ�ܿ��ֳ����С�\n");

        fskill = "hanbing-zhenqi";
        bskill = "strike";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("���"+to_chinese(fskill)+"��Ϊ����������ʹ��"+PNAME+"��\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("���"+to_chinese(sskill)+"��Ϊ����������ʹ��"+PNAME+"��\n");

        if( query("max_neili", me)<600 )
                return notify_fail("���������Ϊ������\n"); 

        if( query("neili", me)<400 )
                return notify_fail("�������������\n"); 

        skill = me->query_skill(bskill, 1);
        msg = HIY"ʹ���������Ƶľ����������ơ���˫��ԶԶһ��һ����$n�پ�һ��\n"HIB"����"HIY"Ϯ����������ʱ��������˸���ս��$nֻһ����һ��"HIR"���ȵ��Ʒ�"HIY"�����˵�������$n������Ϣ�����ӻ��˼��Ρ�\n";

        damage=query("jiali", me)*3+100;

        if(random(me->query_skill(bskill, 1)) > target->query_skill("parry",1)/3)
        {
          if( query("jiali", me)*10>query("neili", target) )
          {
                        msg += HIR"��������$n�ؿڣ����$n���ӷ��˳�ȥ��\n"NOR;
                        target->receive_damage("qi", damage,me);
                        target->receive_damage("jing", damage,me);
                        me->start_busy(1);
                        addn("neili", -100, me);
          } 
          else
          {
                        msg += HIB"��һ��һ��������������$n���ϣ�$n����������Ȼ��Ȼ������Ӧ֮������ס�������࣬�������ˡ�����ʱ��ȫ�����˵���������ܡ�\n"NOR;
                        target->receive_damage("qi", (int)(damage/2),me);
                        target->receive_damage("jing", damage,me);
                        me->start_busy(2);
                        addn("neili", -200, me);
          }
        }
        else 
          {     
                  msg+=HIG "���$p������$P����ͼ�����к�Ծ���ܿ���$P��������\n" NOR;
                me->start_busy(3);
                 addn("neili", -200, me);
          }
        message_combatd(msg, me, target);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �𺦵�����Ѫ

        ����Ҫ��
                ��������120��
                ��������120��
                ������Ϊ600
                ����400
HELP
        );
        return 1;
}
