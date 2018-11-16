// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "������" HIR "Ѫ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;

        if (me->query_skill("daojian-guizhen", 1) < 200)
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        type=query("skill_type", weapon);

        if (me->query_skill(type, 1) < 250)
                return notify_fail("���" + to_chinese(type) + "̫�"
                                   "����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("��û�м����������棬����ʩչ" + name() + "��\n");

        if (me->query_skill("daojian-guizhen", 1) < 250)
                return notify_fail("��Ľ�����ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����" + weapon->name() + HIW "���һ��"
              "������" NOR + WHT "���ҵ���" HIW "������" NOR + WHT
              "��ҽ���" HIW "������ʩ������ʱ��\n���㣬����ҹ��"
              "���գ�����ǵ�����$n" HIW "������һ�С�" HIW "����"
              "��" HIR "Ѫ" HIW "����\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$n" HIW "ֻ���������⽣Ӱ���Լ���"
                       "�����ٸ��ۻ����ң��ĵ׺�����Ȼ������\n" NOR;
                count = ap / 15;
                set_temp("daojian-guizhen/max_pfm", 1, me);
        } else
        {
                msg += HIG "$n" HIG "ͻȻ�����Լ����ܽԱ�����"
                       "��Ӱ����Χ����֪�����æС���мܡ�\n" NOR;
                count = ap / 30;
        }
        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 100);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        delete_temp("daojian-guizhen/max_pfm", me);
        me->start_busy(2 + random(2));
        return 1;
}
