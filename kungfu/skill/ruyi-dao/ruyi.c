// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("����������ԣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<250 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill("ruyi-dao", 1) < 100)
                return notify_fail("������⵶���������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "ruyi-dao")
                return notify_fail("��û�м������⵶��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ʹ����ң����������������������Ȼ����ޱȣ����Ī�⣡\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);
        skill = me->query_skill("ruyi-dao", 1);
        addn_temp("apply/attack", skill/2, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -skill/2, me);
        me->start_busy(1 + random(3));

        return 1;
}
