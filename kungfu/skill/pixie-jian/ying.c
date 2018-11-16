// ying.c ��Ӱ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("gender", me) != "����" && !query("reborn/times", me) )
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

        if( userp(me) && !query("can_perform/pixie-jian/ying", me) )
                return notify_fail("�㻹����ʹ�á���Ӱ����һ�С�\n");

        if (! me->is_fighting(target))
                return notify_fail("����Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("��ı�а������Ϊ���ޣ����ڲ���ʹ�á���Ӱ����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷����á���Ӱ����\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                return notify_fail("��ֻ��װ��������ʩչ����Ӱ����\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

        if (weapon)
        {
                msg = HIR "\n$N" HIR "��Цһ��������Ȱ�Ʈ��$n������ò���˼��!"
                      HIR "���е�" + weapon->name() + HIR "��㣬��̣�������\nɲʱ������$n����������������!\n\n"
                      HIC "$n�����޷����彣�е���·�����·������" HIC "!\n" NOR; 
       
      }

        message_combatd(msg, me, target);
        count = skill + me->query_skill("riyue-guanghua", 1);
        if( me->query_skill_mapped("force") != "riyue-guanghua")
        count /= 2;

        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        
        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);
        
        return 1;
}
