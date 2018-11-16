// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("liuyue-jian", 1) < 140)
                return notify_fail("������½�����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "liuyue-jian")
                return notify_fail("��û�м������½��裬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "����һ�󼲶�������΢��������������ɲ�Ǽ佣â���ǣ�"
              "����ӵ�кһ������$n"
              HIW "��\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        skill = me->query_skill("liuyue-jian", 1);
        addn("apply/attack", skill, me);
        addn("apply/damage", skill/2, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("apply/attack", -skill, me);
        addn("apply/damage", -skill/2, me);
        me->start_busy(1 + random(3));

        return 1;
}