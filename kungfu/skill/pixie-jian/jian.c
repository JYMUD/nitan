#include <ansi.h>
#include <combat.h>

#define PI "��" HIW "��а��Ӱ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        string name;
        object weapon;
        int i;
        int skill;
        int count;

        if( userp(me) && !query("can_perform/pixie-jian/jian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
        
        if( !query("reborn/times", me) ) 
                return notify_fail("����δת������������ʩչ" PI "��\n"); 

        if( query("family/family_name", me) != "�������" 
         && member_array("�������", query("reborn/fams", me)) == -1 ) 
                return notify_fail("����δת������������ʩչ" PI "��\n"); 

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(PI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);

        if (! weapon)
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" PI "��\n");
        
        if( weapon && query("skill_type", weapon) != "sword" && 
            query("skill_type", weapon) != "pin" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" PI "��\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 1000)
                return notify_fail("��ı�а����������죬����ʩչ" PI "��\n");

        if (me->query_skill("dodge", 1) < 1000)
                return notify_fail("������Ṧ������죬����ʩչ" PI "��\n");
                
        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" PI "��\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("��û�м�����а����������ʩչ" PI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һת������" + weapon->name() + HIR "������˸����Ȼ�䣬����"
              "��ǧ��Ӱ����$n" HIR "�����ǽ�����ʧ���Ѿõľ�����ѧ����а��Ӱ����\n" NOR;
        
        message_combatd(sort_msg(msg), me, target);

        count = skill;
        addn_temp("apply/attack", count*6, me);
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_dage", count, me);

        addn_temp("pixie-jian/hit_msg", 1, me);

        set_temp("pixie-jian/pfm_jian", 1, me);
        
        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("neili", -800, me);
        if (random(5) != 1)
                me->start_busy(4 + random(4));
        addn_temp("apply/attack", -(count*2), me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_dage", -count, me);
        delete_temp("pixie-jian/hit_msg", me);
        delete_temp("pixie-jian/pfm_jian", me);
        return 1;
}
