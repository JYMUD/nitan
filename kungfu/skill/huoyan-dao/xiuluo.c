 // ���޽��� xiuluo.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���޽���"; }

int perform(object me, object target)
{
      object weapon;

      int i, jiali;
      string msg;

       if( !target ) target = offensive_target(me);
       if( !target
        || !target->is_character()
        || !me->is_fighting(target)
        || !living(target))
                return notify_fail("�����޽���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("�����޽������ǿ��־�����������������ʹ�������ģ�\n");

        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("�����ʹ�û��浶��ʩչ�����޽�������\n");

        if(me->query_skill("huoyan-dao", 1) < 150 )
                return notify_fail("��Ļ��浶����Ӳ������⡸���޽�������������Ҳ�ա�\n");

        if(me->query_skill("strike", 1) < 150 )
                return notify_fail("��Ļ����Ʒ���������죬ʹ���������޽�����������\n");

        if(userp(me) && (int)me->query_skill("xiaowuxiang", 1) < 100 )
                return notify_fail("���С���๦�ȼ������ߣ�ʹ���������޽�������\n");

       if( query("max_neili", me)<2000 )
           return notify_fail("���������Ϊ�������⡸���޽�������������Ҳ�ա�\n");

       if( query("neili", me)<500 )
           return notify_fail("����Ŀǰ�������������⡸���޽�������������Ҳ�ա�\n");

       if( query("jing", me)<80 )
           return notify_fail("��ľ���������\n");



        addn("jing", -20, me);
        msg =HIR "ͻȻ" HIR "$N" HIR "˫�ƴ��˼��ֻ꣬�����������죬�����浶����" HIR "$N" HIR "��ǿ�ھ��Ķ�Ȼ���֮��\n"
             HIR "���ƴ�ʢ��������������ε��������һƬ�������������޽���������" HIR "$n" HIR "ֱ������! \n" NOR;

        message_combatd(msg,me,target);
        i = me->query_skill("force") / 4;
        jiali=query("jiali", me);

        set("jiali", i, me);
        addn_temp("apply/attack", jiali+200, me);
        addn_temp("apply/unarmed_damage", jiali+200, me);
        msg = HIY"\n\n��ɽ�𺣣�\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = HIR"------�޾�������\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = RED"--------------�ķ�����\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        addn_temp("apply/attack", -jiali-200, me);
        addn_temp("apply/unarmed_damage", -jiali-200, me);
        me->start_busy(1+random(2));
        return 1;
}
