// This program is a part of NITAN MudLIB
// jiutian.c ����ʽ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����ʽ"; }

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
                return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 120)
                return notify_fail("��������Ʒ�������죬����ʹ�á�����ʽ����\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߣ��������á�����ʽ����\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������������ʹ�á�����ʽ����\n");

        msg = HIC "$N" HIC "˫��һ�񣬻���������Ӱ����������ס$n" HIC "��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$p" HIR "���Σ�ֻ��Ӳ��һ�У������$P"
                                           HIR "���������������Ѫ��ֹ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "ǿ��������Ӳ�����ĵ�ס$P"
                       HIC "��һ�ƣ�û���ܵ��κ��˺���\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}