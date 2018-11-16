// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "���ػ���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (query("max_neili", me) < 6000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" + name() + "��\n");

        if (me->query_skill("jiuyang-shengong", 1) < 200)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 500)
                return notify_fail("��������������޷�����" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���һ������ʱһ�ɺƵ��ޱȵ����������ڱŷ���˫��"
              "��Ȼ��������$n" HIR "�������ȥ��\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con();
        dp = defense_power(target, "parry") + target->query_con();

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "ֻ����Χ���������ޱȣ��ּ�����������"
                       "�Լ�Ϯ�����ٸ�ͷ��Ŀѣ����֪����εֵ���\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "ֻ��$N" HIY "�����������Լ�Ϯ������"
                       "æǿ������ǿ�ֵ���\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}