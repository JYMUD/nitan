//duan.c -��������֮������ն��
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    int damage;
    string msg;
    if( !target ) target = offensive_target(me);
    if( !target||!target->is_character()||!me->is_fighting(target) )
    return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�����ն����\n");
    if( (int)me->query_skill("duanyun-fu",1) < 70)
    return notify_fail("��Ŀǰ������ʹ����������ն����\n");
    if( query("neili", me)<200 )
    return notify_fail("�������������\n");
    addn("neili", -60, me);
msg = HIC"$NͻȻ����һ���������о޸�б���Ͼ���Ȼ���ڰ���л���һ
��Բ�����漴��ֱб��ն��$n����һ˲�䣬$nֻ���ú�����ֹͣ�ˣ�\n"NOR;
    me->start_busy(1);

    if( random(query("combat_exp", me)/100)>
      query("combat_exp", target)/400){
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    damage = (int)me->query_skill("duanyun-fu", 1)+(int)me->query_skill("axe", 1
)/2;
    damage = damage/2 + random(damage);

    target->receive_damage("qi", damage);
    target->receive_wound("qi", damage/2);
   msg += RED
"ֻ��$n��$Nһ�����У���ǰ�ѿ�һ��������˿ڣ�Ѫ��������������\n"NOR;
        message_combatd(msg, me, target);
        COMBAT_D->report_status(target);

    } else {
    msg += HIC "����$p��æ����㿪��$P����û�еóѡ�\n" NOR;
    message_combatd(msg, me, target);
    }
    return 1;
}
