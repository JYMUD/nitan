// cimu.c  辟邪剑法「刺目」
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
#define PNAME "「刺目」"

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
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
   return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能对战斗中的对手使用。\n");
                
                // 兵器空手均可
                
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }
        if( (int)me->query_skill(sskill, 1) < 80 )
                return notify_fail("你的"+to_chinese(sskill)+"不够娴熟，使不出"+PNAME+"。\n");

        if( query("max_neili", me)<400 )
                return notify_fail(RED"你内力修为不足，无法运足内力。\n"NOR);

        if( query("neili", me)<200 )
                return notify_fail("你现在内力不够，没能将"PNAME"使完！\n");

        if( query_temp("bixie/cimu", target) )
                return notify_fail(HIR"对方已经身中"PNAME"了！\n"NOR);

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                msg = HIC"$N"HIC"左手两指并拢，手臂暴长，迅捷异常分刺$n"HIC"双目，\n"NOR;
        else msg = HIC"$N"HIC"手中长剑一振，剑尖一点暴长，分刺$n"HIC"左右双目，\n"NOR;


        if( query("dex", me)>35 && 
            (int)me->query_skill("bixie-jian", 1) > 400 &&
            (int)me->query_skill("kuihua-xinfa", 1) > 350 &&
            query("family/master_id", me) == "dongfangbubai" )
        {
                me->start_busy(2);
                target->start_busy(random(5));
                damage = (int)me->query_skill("sword", 1);
                damage = damage*2 + random(damage);
                target->receive_damage("qi", damage*2,me);
                target->receive_wound("qi", damage,me);
                msg += HIC "$n只看到寒尖一点，双目一阵剧痛，眼前一黑，顿时长声痛极而呼，再也看不到东西了！\n"NOR;
                message_combatd(msg, me, target);
          addn("neili", -200, me);
                set_temp("bixie/cimu", 1, target);
                set_temp("block_msg/all", 1, target);
//                call_out("cimu_end", (int) 2+random(6), me, target);
        }
        else if (random(me->query_skill("force"))>target->query_skill("force")/2 ||
                random(query("combat_exp", me))>query("combat_exp", target)/3 )
        {
                me->start_busy(2);
                target->start_busy(random(3));
                damage = (int)me->query_skill("sword", 1);
                damage = damage/2 + random(damage);
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                msg += HIC "$n只看到寒尖一点，双目一阵剧痛，眼前一黑，就什么也看不见了，顿时长声痛极而呼！\n"NOR;
                message_combatd(msg, me, target);
                addn("neili", -200, me);
                set_temp("bixie/cimu", 1, target);
                set_temp("block_msg/all", 1, target);
                call_out("cimu_end", (int) 2+random(6), target);
        } 
        else
        {
                me->start_busy(2);
                addn("neili", -100, me);
                msg += HIY"$p情急智生，抬手也$P右眼刺去，迫得$P回剑跃开。\n"NOR;
                message_combatd(msg, me, target);
        }
        
        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

void cimu_end(object target)
{
        message_combatd(HIY"$N"HIY"抹了抹流着"HIR"鲜血"HIY"，终于能看见了。\n"NOR, target);
        set_temp("block_msg/all", 0, target);
        tell_object(target,HIR"你终于抹掉了眼前的鲜血，能看见了。\n"NOR);
        delete_temp("bixie/cimu", target);

        return;
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                施招刺对方的眼目，使对方受伤并暂时致盲
                损伤对方气血

        出手要求：
                辟邪剑法80级
                最大内力400
                内力200
HELP
        );
        return 1;
}