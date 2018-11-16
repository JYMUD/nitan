// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return  HIR "������" NOR; }

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, foc, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if( query_temp("long_tun", me) )
                return notify_fail(name() + "�޷�����ʩչ��\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 180)
                return notify_fail("��������������Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("��û��׼��ʹ�����������������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "˫�����ҷ��ţ��������죬��ʩ���������������ѧ��"
              HIR "������" HIY "������ʱ��\nХ������������һ�������ޱȵ��"
              "��$N" HIY "˫�Ƽ�ӿ�����ƹ���$n" HIY "��ȥ��\n" NOR;

        set_temp("long_tun", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 50);

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                foc = target->query_skill("force");
                damage = damage_power(me, "unarmed") + random(foc);
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                               HIR "$n" HIR "һ����������$N" HIR "���"
                                               "���������ţ������������Ĵ��Ҵܣ��Ҳ���"
                                               "�ԡ�\n" NOR);

                me->start_busy(4);
                addn("neili", -300, me);
        } else
        {
                me->start_busy(5);
                addn("neili", -200, me);
                msg += CYN "����$p" CYN "��$P" CYN "�������ƷǷ�����"
                       "æ���������ߣ����ڶ�ܿ�����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("long_tun", me) )
        {
                delete_temp("long_tun", me);
                tell_object(me, "�㾭��������Ϣ���ֿ��Լ���ʩչ" + name() + "�ˡ�\n");
        }
}

