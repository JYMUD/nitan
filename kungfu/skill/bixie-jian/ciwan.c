// ciwan.c ����
// Last Modified by winder on Oct. 28 2000

#include <ansi.h>
#define PNAME "������"
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
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
                
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail(HIY "û������ʲô����ȥ���˼ң�\n" NOR);

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
        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("���"+to_chinese(sskill)+"��������������ʹ��"+PNAME+"��\n");
        if( query("max_neili", me)<600 )
                return notify_fail(HIY "���������Ϊ���������\n" HIY);
        if( query("neili", me)<400 )
                return notify_fail(HIY "�������������㡣\n" HIY);
        if( query_temp("bixie/ciwan", target) )
                return notify_fail(HIR"�Է��Ѿ����С������ˣ�\n"NOR);

        msg = HIC "$N"HIC"ͻȻ����"+weapon->name()+HIC"һ�񣬽����ӥ���ð����$n"HIC"����Ҫ����\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2)
        {
                msg += HIC"$n"HIC"ֻ��������һ�飬һ�������ش�����ȥ��\n"NOR;
                message_combatd(msg, me, target);
                addn("neili", -400, me);
                set_temp("bixie/ciwan", 1, target);
                call_out("ciwan_end", (int) 6+random(6), target);
        } else
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIY"$n"HIY"��æһ���֣�ǡǡ�ܹ���$N�ĳ���һ����\n"NOR;
                message_combatd(msg, me, target);
        }
        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

void ciwan_end( object target)
{
        message_combatd(HIR"$N"HIR"���������Ͻ���������������æ̧�ֳ��С�\n"NOR, target);
        delete_temp("bixie/ciwan", target);

        return;
}
string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
        ʩ�д̶Է�������Ҫ��
                ��ʱ��ʹ�Է�ʧȥ�м�����
                ��ʱ��ʹ���ֲ��������⹦

        ����Ҫ��
                ��а����120��
                �����ķ�100��
        �������600
                ����400
HELP
        );
        return 1;
}