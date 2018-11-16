// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "���ʽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 130)
                return notify_fail("�����ɽ�����Ʋ�����죬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "˫��һ��ʩ����ɽ�����ơ����ʽ�����ó�"
              "������Ӱ��������ס$n" HIR "��\n" NOR;

        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$n" HIR "���������ã�ֻ��Ӳ����һ"
                                           "�У���ʱ��$P" HIR "���������������Ѫ"
                                           "��ֹ��\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "����$p" HIC "ǿ��������Ӳ�����ĵ�ס$P"
                       HIC "��һ�ƣ�û���ܵ��κ��˺���\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
