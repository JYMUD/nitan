// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

#define XUAN "��" HIW "̫������" NOR "��"
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/taixuan-gong/xuan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
        if( query("neili", me)<800 )
                return notify_fail("��������������޷�ʩչ" XUAN "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ��������ʹ��" XUAN "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" XUAN "��\n");

        if ((lvl = (int)me->query_skill("taixuan-gong", 1)) < 240)
                return notify_fail("���̫�����������������޷�ʹ��" XUAN "��\n");

        // δѧ����μ�������ֻ�ܼ���Ϊȭ��ʩչ ̫������
        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             weapon=query_temp("weapon", me);
             if (objectp(weapon))
                     return notify_fail("�㻹û��ѧ���������̫������������������ֻ�ܿ���ʩչ��\n");

             if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                 || me->query_skill_prepared("unarmed") != "taixuan-gong")
                       return notify_fail("��û��׼��̫�������޷�ʹ��" XUAN "��\n");

        }
        else // �Ѿ�ѧ������̫������������
        {
             weapon=query_temp("weapon", me);
             // ��û�г�����ʱ�ж�ʩչ������Ҫ׼��Ϊȭ��
             if (! objectp(weapon))
             {
                    if (me->query_skill_mapped("unarmed") != "taixuan-gong"
                        || me->query_skill_prepared("unarmed") != "taixuan-gong")
                              return notify_fail("��û��׼��̫�������޷�ʹ��" XUAN "��\n");
             }          
             // �ֳ�����������Ϊ�����߽�
             else if( objectp(weapon) && query("skill_type", weapon) != "sword"
                       && query("skill_type", weapon) != "blade" )
                              return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" XUAN "��\n");

             if (objectp(weapon) && me->query_skill_mapped("sword") != "taixuan-gong"
                  && query("skill_type", weapon) == "sword" )
                              return notify_fail("�㻹û�м���̫�������޷�ʩչ" XUAN "��\n");
             
             else if( objectp(weapon) && query("skill_type", weapon) == "blade"
                      && me->query_skill_mapped("blade") != "taixuan-gong")
                              return notify_fail("�㻹û�м���̫�������޷�ʩչ" XUAN "��\n");                              
                         
        }
        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n��ʱ��$N" HIW "ֻ��˼����ӿ����������˫�ۣ��ٲ����$n"
              HIW "����мܣ�ֻ��ʩ�й�������ʱ���͵�ʯ���ϵ�ǧ������"
              "ʽ��ת���Ѵ�$N" HIW "�ĵ״������㣬������$n" HIW "Ϯȥ��\n" NOR;

        message_combatd(sort_msg(msg), me, target);
        
        addn("neili", -600, me);
        addn_temp("apply/damage", lvl, me);
        addn_temp("apply/unarmed_damage", lvl, me);
        addn_temp("apply/attack", lvl, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                if (! objectp(weapon))
                COMBAT_D->do_attack(me, target, 0, i * 2);
                else
                COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        addn_temp("apply/unarmed_damage", -lvl, me);
        addn_temp("apply/attack", -lvl, me);
        addn_temp("apply/damage", -lvl, me);
        me->start_busy(2 + random(5));
        return 1;
}
