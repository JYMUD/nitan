// Last Modified by winder on Sep. 12 2001
// zhuihun.c һ��׷��

#include <ansi.h>;
inherit F_SSERVER;
#define PNAME "һ��׷��"
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
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
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        fskill = "honghua-shengong";
        bskill = "sword";
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("���"+to_chinese(fskill)+"�����ߣ�����ʹ��"+PNAME+"��\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("���"+to_chinese(sskill)+"������죬����ʹ��"+PNAME+"��\n");

        damage = (int)me->query_skill("force", 1);
        damage += (int)me->query_skill(bskill, 1)*3/2;

        if( query("max_neili", me)<damage+100 )
                return notify_fail("���������Ϊ̫����ʹ������һ��׷�꡹��\n");

        if( query("neili", me)<damage )
                return notify_fail("����������̫��������ʹ�á�һ��׷�꡹��\n");
                        
        msg = CYN "$N΢΢һЦ������һ����������Ծ��"+weapon->name()+CYN"���޳�������������$n��\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force")/5 )
        {
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                addn("neili", -(damage/4), me);
                msg += HIR "$nֻ��������ҹĻ������ǵذ�ѹ����һʱ����ǰһ���������������޴��мܣ���\n"NOR;
                me->start_busy(1);
        } else 
        {
                msg += CYN"����$p�������죬����Ծ����$P�Ľ�����\n"NOR;
                addn("neili", -100, me);
                me->start_busy(1+random(1));
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
                �˺��Է���Ѫ

        ����Ҫ��
                �컨��120��
                ׷�������120��
                �㹻��������Ϊ
                �㹻������
HELP
        );
        return 1;
}
