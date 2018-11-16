#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        string msg,dodge_skill;
        int extra,skill,at,df,i,lmt,damage,p;
        object weapon;
        extra = me->query_skill("shenfeng-bian",1);

        if( !target ) target = offensive_target(me);

        if( !target
          || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("�۴ȱ��־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( extra < 160)
              return notify_fail("������޷���Ϊ̫�\n");

        skill = me->query_skill("buddhism",1);

        if( skill < 180)
              return notify_fail("��������ķ��ȼ������� \n");

        if( query("shen", me)<500000 )
              return notify_fail("�ȱ��־������ޱ�����Ϊ��,��ʦ���Ƕ������°�! \n");

        if( query("neili", me)<1500 )
              return notify_fail("���������Ϊ���������ȱ��־���\n");

        weapon=query_temp("weapon", me);

        if( !weapon
          || query("skill_type", weapon) != "whip" )
              return notify_fail("������û�б������ʹ�ôȱ��־���\n");

        msg = RED"ֻ��$N����������ȱ�Ϊ�������е�"+ weapon->name()+RED"�·����������㵹����$n��\n"NOR;
        at=query("combat_exp", me)*me->query_skill("shenfeng-bian",1)/1000;
        df=query("combat_exp", target)*target->query_skill("dodge",1)/1000;
        if( random(at + df) > df ){
            damage=query("shen", me)/2000;
            if(damage > 1500) damage = 1500 + (damage-1500)/100;
            msg += CYN"$n������$N���ޱ߷𷨴򶯣��͵ĺ��ˣ�����û��һ˿Ѫɫ...\n"NOR;
            target->receive_damage("qi", damage, me);
            target->receive_wound("qi", damage/3, me);
            p=query("qi", target)*100/query("max_qi", target);
            msg += "( $n"+eff_status_msg(p)+" )\n"; 
            message_vision(msg, me, target);
            target->start_busy(3);
            weapon=query_temp("weapon", me);
            msg = HIG"\n������$N���е�"+ weapon->name()+HIG"�����ζ�����Ȼ��֪���ж��ٻ���\n" NOR;
            message_vision(msg,me,target);
            lmt = random((me->query_skill("shenfeng-bian", 1)- 100)/50)+1;
            if( lmt > 3 ) lmt =3;
            set_temp("chb", 3, me);
            for(i=1;i <= lmt;i++){
                 extra = me->query_skill("shenfeng-bian", 1);
                 addn_temp("apply/attack", extra/5, me);
                 addn_temp("apply/damage", extra/5, me);
                 COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                 addn_temp("apply/attack", -extra/5, me);
                 addn_temp("apply/damage", -extra/5, me);
            }
            delete_temp("chb", me);
            me->start_perform(5,"�ȱ��־�");
            addn("neili", -(300+random(me->query_skill("force"))), me);
            addn("jingli", -100, me);
            addn("shen", -5000, me);
        }
        else { 
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
              message_vision(msg, me, target);
              if( !target->is_killing(query("id", me))){
                       me->kill_ob(target);
                       target->kill_ob(me);
              }
              addn("neili", -200, me);
              addn("jingli", -50, me);
              me->start_busy(random(2));
              me->start_perform(3,"�ȱ��־�");
        }
        return 1;
}