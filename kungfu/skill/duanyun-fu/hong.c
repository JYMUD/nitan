//hongtianza.c ��������֮�������ҡ�
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    string msg,*limbs;
    int i,size,damage;
    object weapon;
    object my_w,target_w;
    my_w=query_temp("weapon", me);
//    target_w = target->query_temp("weapon");
    if( !target ) target = offensive_target(me);

              if( !target || !me->is_fighting(target) )
                      return notify_fail("��"HIM"�������ҡ�"NOR"��ֻ����ս���жԶ���ʹ�á�\n");

              if( !objectp(weapon=query_temp("weapon", target)) )
                      return notify_fail("�Է�û��ʹ�ñ���������ʩչ�������ҡ���\n");

    if( target->is_busy() )
    return notify_fail(target->name() + "Ŀǰ��ãȻ��֪���룬�ӽ������ɡ�\n");
    if( (int)me->query_skill("duanyun-fu",1) < 50)
    return notify_fail("��Ŀǰ������ʹ�����������ҡ���\n");
    if( query("neili", me)<100 )
    return notify_fail("�������������\n");
    addn("neili", -60, me);
msg = CYN"$NͻȻ����һ���������ң����ң��������ң��������о޸���Ȼ����$p���б��У�\n"NOR;
    target_w=query_temp("weapon", target);
    me->start_busy(1);

    if( query_temp("weapon", target) || 
   query_temp("secondary_weapon", target)){

    if( random(query("combat_exp", me)/100)>
      query("combat_exp", target)/300){
    if( target_w->weight() > 2 * random(my_w->weight()) ) {
msg+="���$p���е�"+query("name", target_w)+"��$P�ĺ������Ҹ����ţ���Ҳ���ղ��
ס���������ַɳ���\n" NOR;
    target_w->unequip();
    target_w->move(environment(target));
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
}
   msg += HIC
"ֻ��$n���е�"+query("name", target_w)+"��Ȼ���Ҷ������Σ�����
�ܵ�$N�ľ����ļ�������$nѸ����ȥ��\n"NOR;
    message_combatd(msg,me,target);
    target_w->unequip();
    target_w->move(environment(target));
    set("name",query("name",  target_w)+"����Ƭ", target_w);
    set("value",query("value",  target_w)/10, target_w);
    set("weapon_prop", 0, target_w);
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    limbs=query("limbs", target);
    me->start_busy(1);
    msg += "���$p���������������˸����ֲ�����\n" NOR;
    size=(int)(me->query_skill("duanyun-fu")/10);
    damage=random(size)+size;
                                 damage=damage+me->query_str()/3+random(query_temp("apply/damage",me)); 
    for(i=0;i<=random(size);i++)
   {
   msg =HIB"���͡�����Ƭ����$p"+limbs[random(sizeof(limbs))]+"��\n"NOR;
   message_combatd(msg,me,target);
   target->receive_damage("qi",damage,me);
   target->receive_wound("qi",damage/3,me);
   }
    COMBAT_D->report_status(target);
    } else {
    msg += "����$p��æ���Լ��ı�����������û����$P�ļ�ı�óѡ�\n" NOR;
    }
    return 1;
    }
    return notify_fail(target->name() + "Ŀǰ�ǿ��֣�������ʲô��\n");
}
