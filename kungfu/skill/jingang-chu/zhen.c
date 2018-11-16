// This program is a part of NITAN MudLIB
// xiang.c 

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;
        
        if( userp(me) && !query("can_perform/jingang-chu/xiang", me) )
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ����衣\n");
                 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("�����Ȼ�ʹʲô������衹��\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("staff") < 100)
                return notify_fail("��Ļ����ȷ���򲻹���\n");

        if ((int)me->query_skill("jingang-chu", 1) < 100)
                return notify_fail("��ĺ����������ƻ������ң��޷�ʹ�á�����衹��\n");

        if (me->query_skill_mapped("staff") != "jingang-chu")
                return notify_fail("��û�м������������ƣ��޷�ʹ�á�����衹��\n");

        msg = HIW "$N" HIW "ʩչ��������Ƶľ�����ʽ������衹��ֻ��" + weapon->name() +
              HIW "�������£��仯Ī�⣬������$n" HIW "����Ҫ����\n" NOR;


        message_combatd(msg, me, target);
        
        count = me->query_skill("jingang-chu", 1) / 10;
        
        addn("neili", -150, me);
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}

