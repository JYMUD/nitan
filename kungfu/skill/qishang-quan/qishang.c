// qishang ����
#include <ansi.h>

inherit F_SSERVER;

string name() { return "����"; }

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int i, j, damage;
        int ap, dp;

        if( !target ) target = me->select_opponent();

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");

        if (me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭΪ����ȭ�������⼼�ܣ��޷�ʩչ�����ˡ���\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ�����ˡ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250 )
                return notify_fail("�������ȭ��������죬��û�а취ȭ�����ˡ�\n");

        if( (int)query("neili", me) < 800 )
                return notify_fail("�����Ŀǰ������û�а취������һ�С�\n");

        i = random((int)(me->query_skill("qishang-quan",1)/60));
        if( i < 1 ) i = 1;
        if( i > 7 ) i = 7;

        msg = HIY "$N�����˹���ʹ��������ȭ�����ľ��У�"+chinese_number(i)+"���ޱ�ǿ����������Х������$n���ϸ���ҪѨ��\n"+
              HIC "$n���ᵤ��֮������������ײ����"+chinese_number(i)+"�ɾ���������\n"NOR;

        addn("neili", -500, me);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if( ap /2 + random(ap) > dp || !living(target) )
        {
                me->start_busy(1);
                target->start_busy(i);

                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);

                target->receive_damage("qi", (int)((i*(2*damage))/3), me);
                target->receive_wound("qi", (int)((i*damage)/3), me);

                msg += HIY"���$n���ܲ�ס$N��"+chinese_number(i)+"�־������������ص�ײ����"+GRN"\n($n"+HIR"���ܵ�������ʵ���ᡣ"+GRN")\n"NOR;
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
        } else
        {
                me->start_busy(3);
                if (!target->is_busy()) target->start_busy(1);
                msg += CYN"����$pæ��������$P��"+chinese_number(i)+"�־�����������֮�����ڻ�֮���Ρ�\n"NOR;

        }
        message_combatd(msg, me, target);
        return 1;
}

/*
                                 ��
                                  ����
                                   ����
                                   ����   ������   
                    ��������       ��������   ����
               ��������         ��������     ����  
          ��������         ������  ����     ���� 
       ������    ����      ����    ����
                ����       ����    ���� 
               ����         ������������������
              ����          ������         ����   
            ������������    ���� ��       ���� 
          ����       ����   ����  ����   ����
        ������        ����  ����   ��������
      ���� ����      ����   ����     ����
    ����   ����     ����   ����    ���� ����
  ��        ����������     ����   ����    ����
                         ����  ����         ����
                         ��  ����             ������ 
                       ��   ��                 ������
                     ��
*/