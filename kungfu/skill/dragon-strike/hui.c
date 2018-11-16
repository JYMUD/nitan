// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "�����л�" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("��������Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dragon-strike", 1) < 240)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һ��
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);

        message_combatd(sort_msg(HIW "\n��Ȼ��$N" HIW "���μ���������һ�������ֺ���һ�ƣ���"
                     "��$n" HIW "��ȥ�����ǽ���ʮ���ơ�" NOR + HIY "�����л�" NOR
                     + HIW "��һ�У���������֮��˵���㵽������ɽ����֮����$n" HIW
                     "��ӿ��ȥ������ʯ���쾪�������ޱȡ�\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 65,
                                          HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                          "һ�����ѻ����Լ���ǰ����������������"
                                          "�����С�\n:����@?");

                message_combatd(msg, me, target);

        } else
        {
                msg = HIC "$p" HIC "����˫�ۣ�����Ӧ�ԣ��������࣬$P"
                      HIC "��������ţ�뺣������жȥ��\n" NOR;
                message_combatd(msg, me, target);
        }

        // �ڶ���
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;

        message_combatd(sort_msg(HIW "\n$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "������֮��"
                     "��������ǰ�ƣ������������ϲ�������һ�С�" NOR + HIY "������"
                     "��" NOR + HIW "����������������ŭ����ӿ���Ʋ��ɵ�����ʱ$n"
                     HIW "�����Ϣ���ͣ����㲻�ȡ�\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 65,
                                           HIR "ֻ��$p" HIR "һ���Һ�����$P" HIR
                                           "һ�ƻ�����ǰ�������꿦�ꡱ���˼�����"
                                           "�ǡ�\n:����@?");

                message_combatd(msg, me, target);
        } else
        {
                msg = HIC "$p" HIC "����˫�ۣ�����Ӧ�ԣ��������࣬$P"
                      HIC "��������ţ�뺣������жȥ��\n" NOR;
                message_combatd(msg, me, target);
        }

        // ������
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        message_combatd(sort_msg(HIW "\n������$N" HIW "һ�����ȣ�����бб�ӳ���ǰ������δ��"
                     "�����������ֵ�����Ȼ�ֹ���һ�С�" NOR + HIY "�����л�" NOR
                     + HIW "�����Ƽз��ƣ��������񣬱���һ��������ǽ����ǰ�����"
                     "ȥ��$n" HIW "ֻ����Ѫ��ӿ����Ϣ���ǡ�\n" NOR), me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                           HIR "���$p" HIR "����������$P" HIR
                                           "���ƾ���ʱ���ض��������ۡ������һ��"
                                           "����Ѫ��\n:����@?");

                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                addn("neili", -400-random(600), me);
                return 1;
        } else
        {
                msg = HIC "$p" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ��ѳ�$P" HIC "����֮�⡣\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                addn("neili", -400-random(600), me);
                return 1;
        }
        message_combatd(msg, me, target);
        return 1;
}
