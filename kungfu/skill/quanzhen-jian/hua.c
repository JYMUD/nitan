// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "һ��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;
        int is_yunv = 0;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("��ȫ�潣��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("������칦������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��û�м������칦������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ��������������ȫȻ�˵����ϣ�" + weapon->name() +
              HIW "������ʱ" HIM "��â" HIW "��ҫ������������������$n"
              HIW "��\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (stringp(target->query_skill_mapped("sword")) &&
            target->query_skill_mapped("sword") == "yunv-jian" &&
            query_temp("weapon", target) &&
            query("skill_type", query_temp("weapon", target)) == "sword")
        {
                dp += target->query_skill("yunv-jian", 1);
                is_yunv = 1;
        }

        me->start_busy(3);
        addn("neili", -200, me);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "��ʱֻ��$n" HIR "һ���ҽУ�������"
                                           "�����Ͻ����������Ѫ����\n" NOR);
                message_combatd(msg, me, target);

                if (ap / 2 + random(ap) > dp)
                {
                        count = me->query_skill("xiantian-gong", 1) / 2;
                        addn_temp("apply/attack", count, me);
                        message_combatd(HIY "$N" HIY "��$n" HIY "����һ��֮����"
                                        "����������ʱ����ǰԾ���������������"
                                        "\n" NOR, me, target);

                        for (i = 0; i < 3; i++)
                        {
                                if (! me->is_fighting(target))
                                        break;
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }
                        addn_temp("apply/attack", -count, me);
                }
        } else
        {
                if (is_yunv)
                        msg += CYN "ȴ��$n" CYN "΢΢һЦ������һ�С���Ů�����������ɵص�ס��$N�Ľ��С�\n" NOR;
                else
                        msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}
