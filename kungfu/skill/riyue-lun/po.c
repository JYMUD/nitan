// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wp;
        int ap, dp, damage;

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("yuan_man", me) )
                return notify_fail("��������Ͼʩչ" + name() + "��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("��û�м��������ַ�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("riyue-lun", 1) < 120)
                return notify_fail("��������ַ�����㣬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wp = weapon->name();

        msg = HIY "$N" HIY "���ָ߾�" + wp + HIY "������$n" HIY "���£���"
              "�˵���ȫȻ��$n" HIY "�������У�\n" NOR;

        ap = attack_power(me, "hammer") +
             query("str", me)*20;

        dp = defense_power(target, "force") +
             query("con", target)*20;

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "hammer");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��$N" HIR "��ǿ���ޱȵ�"
                                           "�ھ��������ҡ�һΣ��������У�������"
                                           "Ѫ��\n" NOR);
                me->start_busy(2);

        } else
        {
                msg += CYN "ȴ��$p" CYN "�벻���⣬����һ���Ͷ����$P"
                       CYN "���׺�������\n"NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

