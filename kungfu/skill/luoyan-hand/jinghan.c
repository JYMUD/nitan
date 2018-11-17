// Last Modified by ahda on Aug.30 2001
// jinghan.c

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "雁陣驚寒"
int perform(object me, object target)
{
        string msg;
        int skill, damage, plvl;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能對戰鬥中的對手使用。\n");
                
        //空手兵器均可

        fskill = "huiyan-xinfa";
        bskill = "hand";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 50 )
                return notify_fail("你的"+to_chinese(fskill)+"修為不夠，不能使用"+PNAME+"。\n");

        if( (int)me->query_skill(sskill, 1) < 30 )
                return notify_fail("你的"+to_chinese(sskill)+"修為不夠，不能使用"+PNAME+"。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力修為不夠。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠。\n"); 

        msg = HIC"漁舟唱晚，響窮彭蠡之濱；雁陣驚寒，聲斷衡陽之浦。"HIM"
$N"HIM"使出大落雁手的絕技「雁陣驚寒」，乘$n"HIM"勁力的空隙驀地拍向$n"HIM"的全身要穴！\n"NOR;

        message_combatd(msg, me, target);
        plvl = target->query_skill("parry",1),
        skill = me->query_skill(sskill,1);
        me->start_busy(2);
        addn("neili", -100, me);
        if( random(query("combat_exp", me)*(skill/30+1))>
                query("combat_exp", target)*(plvl/50+1) )
        {
                msg = HIW"$n被$N狂風暴雨般的雙掌拍中要穴，立時真氣大散！\n"NOR;
                damage=80+random(query("str", me)*me->query_skill(bskill)/10);
                message_combatd(msg, me, target);
                target->receive_damage("qi", damage,me);
                COMBAT_D->report_status(target);
                return 1;
        } else
        {
                msg = HIG "結果$p看破了$P的企圖，身行後躍，並沒有上當。\n" NOR;
                message_combatd(msg, me, target);
        }
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                損害敵手氣血

        出手要求：
                回雁心法50級
                大落雁手30級
                內力修為300
                內力200
HELP
        );
        return 1;
}
