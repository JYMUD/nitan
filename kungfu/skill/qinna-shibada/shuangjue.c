// shuangjue.c  ȭ��˫��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
              int i, j, z, y;
              i = me->query_skill("zhentian-quan",1);
              j = me->query_skill("chuanyun-tui",1);
              z = me->query_skill("xuantian-wuji",1);
              y = (i+j+z)/4;
              

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("ȭ��˫��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

               if( objectp(query_temp("weapon", me)) )
               return notify_fail("��������ʹ�á�ȭ��˫������\n");

        if (me->query_skill_prepared("cuff") != "zhentian-quan"
            || me->query_skill_prepared("leg") != "chuanyun-tui"
            || me->query_skill_mapped("cuff") != "zhentian-quan"
            || me->query_skill_mapped("leg") != "chuanyun-tui")
                return notify_fail("�������޷�ʹ�á�ȭ��˫�������й�����\n");

        if( (int)me->query_skill("zhentian-quan", 1) < 100 )
                return notify_fail("�������ȭ������죬�޷�ʩչ��ȭ��˫����\n");

            if( (int)me->query_skill("strike", 1) < 100 )
                return notify_fail("���ȭ��������죬�޷�ʩչ��ȭ��˫����\n");

          if( (int)me->query_skill("lag", 1) < 100 )
                return notify_fail("����ȷ�������죬�޷�ʩչ��ȭ��˫����\n");

             if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("����ڹ�������죬�޷�ʩչ��ȭ��˫����\n");

        if( (int)me->query_skill("chuanyun-tui", 1) < 150 )
                return notify_fail("��Ĵ����Ȳ�����죬�޷�ʩչ��ȭ��˫����\n");
              if( (int)me->query_skill("parry", 1) < 100 )
                return notify_fail("����мܲ�����죬�޷�ʩչ��ȭ��˫����\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 100)

                return notify_fail("��������޼�����򲻹����޷�ʩչ��ȭ��˫����\n");
               if( (int)me->query_dex() < 30 )
                           return notify_fail("�����Ƿ�ѣ��޷�ʩչ��ȭ��˫����\n");
               if( (int)me->query_str() < 30 )
                           return notify_fail("������ǲ��㣬�޷����ӳ�ȭ��˫����������\n");
               if( (int)me->query_int() < 30 )
                           return notify_fail("������Բ������޷������ȭ��˫����\n");
        if( query("max_neili", me)<2000 )
                return notify_fail("��������������޷�ʩչ��ȭ��˫����\n");
        if( query("neili", me)<1000 )
                return notify_fail("��������������޷�ʩչ��ȭ��˫����\n");

        message_vision(RED "$Nһ����Х��ȭ����ʩ��ʹ�����ؾ�ѧ��ȭ��˫����Ѹ�����׵ع���$n��\n"NOR,me, target);
          addn("neili", -400, me);
                 addn_temp("apply/str", y, me);
                 addn_temp("apply/attack", y, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        addn_temp("apply/str", -y, me);
        addn_temp("apply/attack", -y, me);
        me->start_busy(2);
        return 1;
}