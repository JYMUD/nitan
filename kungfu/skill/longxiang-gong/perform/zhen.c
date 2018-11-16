// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "�桤������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp;
        int damage;
        int i, count;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 390)
                return notify_fail("��������������Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("��û��׼��ʹ�����������������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ��ŭ������������������������ޣ�ȫ���ʱ�"
              "�ŷ����������ڶ���������$N" HIY "\n�ķ�������ʯ�䣬$N" HIY "˫"
              "ȭ��Я���������֮�Ʊ����������������ﳾ�����������ھ�ѧ��\n" NOR;

        msg += HIW
        "        ��      ����           ��        ��           ��    ������������\n"
        "    �����    ��  ��       ��������������������       ��       ��    ��\n"
        "    ��    ��    ��  ��           ��        ��       ����������  ��    ��\n"
        "    �� �� �� ���    ���          ��                 ������  ������ ������\n"
        "  �������             ������������������������  �� �� ��  ����     ��\n"
        "    ��    ��   �����         ��                   �� �� ��  �� ��   ��\n"
        "    �� �� ��    ��  ��        �� ��������������      �� �� �� ��   ����\n"
        "    ��    ��     ���       ��   ��          ��         ��   ��     ��\n"
        "   ��    ��   ���  ���         ��������������         ��  ��  ����������\n\n" NOR;

        msg += HIY "$N" HIY "һ��������������ű�ӿ���˵ڶ���������������������"
               "���಻����������磡ֱ��$N" HIY "\n��ʮ�����������꣬����������"
               "�ŵ�������������ˣ���$n" HIY "��ʱȴ���Ǳ��޿ɱܣ�\n\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if (! userp(target) ||
                    query("max_neili",me) / 2 + random(query("max_neili",me) / 2) > query("max_neili",target) * 5/4) 
                {
                        msg += HIR "$n" HIR "ȫȻ�����赲������$N"
                                HIR "һȭ���÷������صĵ����ڵ��ϡ�\n" NOR;
                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        target->unconcious(me);

                        me->start_busy(1);
                        return 1;
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200,
                                                   HIR "$n" HIR "�������ܣ��ٱ�$N" HIR
                                HIR "һȭ���÷������صĵ����ڵ��ϡ�\n" NOR);
                        count = ap / 10;
                        msg += HIR "$n" HIR "��$p" HIR "����ƣ�һʱ���������ֵ���������������\n" NOR;
                }
        } else
        {
                msg += HIY "$n" HIY "��$p" HIY "����Ѹ��֮�������ѷ�������"
                       "æ��������С�ĵֵ���\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 8; i++)
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
