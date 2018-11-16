// This program is a part of NITAN MudLIB
// zhua.c ����ץ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����ץ"; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ץ��ֻ����ս���жԶ���ʹ�á�\n");

        skill = me->query_skill("longzhua-gong", 1);

        if (skill < 135)
                return notify_fail("�����צ���ȼ�����������ʹ�á�����ץ����\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷����á�����ץ����\n");

        if (me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("��û�м�����צ�����޷�ʹ�á�����ץ����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���һ������������$n" HIY "��ǰ���漴����ץ��"
              "$p" HIY "��Ҫ����\n" NOR;

        ap = attack_power(me, "claw") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -180, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "���������ͣ����Զ�ܣ�ֻ��"
                                           "��ǿ���⣬˭֪$P" HIR "���ֺ������۾�"
                                           "һ�㣬����һ����ץ��$p" HIR "��Ҫ������"
                                           "ʱ��Ѫ�ɽ���\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ����������ȫȻ������$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
