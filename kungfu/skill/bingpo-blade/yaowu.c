// modify by xiha@wmkj
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
#include <ansi.h>

inherit F_SSERVER;
string msg;
int perform(object me, object target)
{
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С��������졹?\n");
        weapon=query_temp("weapon", me);
        if(!me->is_fighting())
                return notify_fail("���������졹ֻ����ս����ʹ��!\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������������\n");

   if( query("neili", me)<500 )
     return notify_fail("����������㣡\n");


if( !weapon || query("skill_type", weapon) != "blade" )
    return notify_fail("�������ʹ�ñ���ʱ����ʹ�ã�\n");

        if((int)me->query_skill("bingpo-blade",1) < 120)
        return notify_fail("��ı��Ǻ����ȼ�������!\n");

    msg = MAG
"\n$N����һЦ,���е�"+weapon->name()+""+MAG"����һ��,��ʱ��ɳ��ʯ,����ֱ�����!!\n"NOR;
message_vision(msg, me, target);
   delete("env/brief_message", me);
   delete("env/brief_message", target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
         addn("force", -150, me);
//        target->apply_condition("bp_poison",5+random(5) + target->query_condition("bp_poison"));
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1+random(1));
        return 1;
}