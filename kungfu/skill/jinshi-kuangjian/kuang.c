// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("jinshi-kuangjian", 1) < 120)
                return notify_fail("������ǽ�����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<250 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "jinshi-kuangjian")
                return notify_fail("��û�м������ǽ���������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�ۼ���ȫ��������ʱ����һ����ɫӰ�ӣ�һ�㽣â������$n"
              HIR "��ǰ���󣬿��ٹ���$n��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "�޼᲻�ݵĽ�����͸��" + weapon->name() + HIR "������ʹ$n"
                                           HIR "������ֹ��ȫ���������$n" HIR "��δ��Ӧ����ʱ�����ش�����Ѫ�ɽ���\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -60, me);

                msg += CYN "����$p" CYN "�������ң�������������񵲿���$P"
                       CYN "�Ľ��С�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
