// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define YI "��" HIY "����" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, skill;
        int damage;

        skill = me->query_skill("dugu-jiujian", 1);

        if (skill < 90)
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( userp(me) && !query("can_perform/dugu/yi", me) )
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" YI "��\n"); 
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(YI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" YI "��\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian") 
                return notify_fail("��û�м������¾Ž�������ʩչ" YI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch (random(3))
        {
        case 0:
                msg = HIY "$N" HIY "����һ��ָ��$n" HIY "���������$n"
                      HIY "�������ڣ���֮�������������Ѳ⡣\n" NOR;
                break;

        case 1:
                msg = HIY "$N" HIY "���д󿪴��أ������������£�����"
                      "�нԻ�$n" HIY "����������������������\n" NOR;
                break;

        default:
                msg = HIY "$N" HIY "���ֺὣ����$n" HIY "������������"
                      "���е�һ����Ȼ����������˷�����˼��\n" NOR;
                break;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry") +
             target->query_skill("dugu-jiujian");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "sword") * 3 / 2;
                target->receive_damage("jing", damage / 2, me);
                target->receive_wound("jing", damage / 3, me);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100,
                                           HIR "$n" HIR "ȫȻ�޷����$N" HIR "��"
                                           "���еİ��һ�����񣬵����ش���\n" NOR);
                if (! target->is_busy())
                target->start_busy(3 + random(2)); 
                me->start_busy(2);
        } else 
        {
                msg += CYN "��$n" CYN "��Ȼ��֮����û��$N"
                       CYN "���з������ϣ����ּܿ�����©���������\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
