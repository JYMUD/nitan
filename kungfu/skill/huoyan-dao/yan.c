// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "�������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" + name() + "��\n");

        if (skill = me->query_skill("huoyan-dao", 1) < 150)
                return notify_fail("��Ļ��浶��Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<600 || query("max_neili", me)<2000 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("��û�м������浶���޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("��û��׼�����浶���޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") == "dashou-yin")
                return notify_fail("ʩչ" + name() + "ʱ���浶���˺����ڴ���ӡ������\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ��ŭ�����������ע�뵥�ƣ���Ե��ʱ����һ�����ף��Ӷ�������$n"
              HIR "��ȥ��\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -500, me);

        addn_temp("apply/attack", skill/2, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/2, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/2, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/2, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/2, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // ������������
        addn_temp("apply/attack", -skill*5/2, me);

        me->start_busy(1 + random(3));

        return 1;
}

