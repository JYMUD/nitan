//�嶾�޷�  �۶�

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "�۶�"
int perform(object me, object target)
{
        string msg;
        object weapon;
        int lvl ;
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
                query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        fskill = "wudu-shengong";
        bskill = "whip";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("���"+to_chinese(fskill)+"����̫ǳ���޷�"+PNAME+"��\n");

        if( (int)me->query_skill(sskill, 1) < 60 )
                return notify_fail("���"+to_chinese(sskill)+"����̫ǳ���޷�"+PNAME+"��\n");

        if( query("neili", me)<250 )
                return notify_fail("����������㣬�޷��۶���\n");

        addn("neili", -200, me);

        if( target->is_busy() )
                return notify_fail(target->name() +"�Ѿ���æ�����ˣ�����Ҫ���ö��ˡ�\n");

        lvl = me->query_skill(bskill, 1);
        msg = BLU"$N"BLU"Ĭ�����������������ڱ��ϣ�ֻ��һ����ɫ��������ס�˳��ޡ�\n";
        if( random(query("combat_exp", me))>query("combat_exp", target)/2 && random(lvl)>20 )
        {
                msg += "$p�벻������������Ⱦ������\n" NOR;
                target->receive_damage("qi", lvl,me);
                target->receive_wound("qi",15 + random(10),me);
                target->receive_wound("jing", 10,me);
                target->apply_condition("snake_poison", random(lvl/10) + 1 + target->query_condition("snake_poison"));
                me->start_busy(1);
                target->start_busy(1 + random(2));
        }
        else
        {
                msg += HIY"����$p������$P�Ķ��ƣ�������ס������û���ж���\n"NOR;
                me->start_busy(3);
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
                �˵���Ѫ��ʹ�����ж�

        ����Ҫ��
                �嶾��50��
                �嶾�޷�60��
                ����250
HELP
        );
        return 1;
}
