// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "����������" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;
        int v, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((level = me->query_skill("chilian-shenzhang", 1)) < 100)
                return notify_fail("��������Ʋ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "chilian-shenzhang")
                return notify_fail("��û��׼���������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "$N" HIC "�����ڹ�������$N" HIC "˫��΢΢����"
              "��ɫ����Ȼ������ת��\nʹ��һ�С�" HIM "����������" HIC
              "�����Ʒ���������$n" HIC "������˫��֮�С�\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "����һ����ȴ��$N" HIR "��"
                      "����������ʱ��Ŵ��ҡ�\n" NOR;
                v = 1;
                addn_temp("apply/attack", level/5, me);
        } else
        {
                msg = HIY "$n" HIY "����$N" HIY "�⼸�е���·����"
                      "�ھ��������Ʒ�Ϭ����Ҳֻ��С�ĵֵ���\n" NOR;
        }
        message_combatd(msg, me, target);

        attack_time += 4 + random(ap / 100);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        if (v)
                addn_temp("apply/attack", -level/5, me);
        me->start_busy(1 + random(4));

        return 1;
}