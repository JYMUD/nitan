// This program is a part of NITAN MudLIB
// zhua.c ������צ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "������צ" NOR; }

string final(object me, object target);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("sanyin-zhua", 1) < 80)
                return notify_fail("����������צ������죬�޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("��û�м����������צ���޷�ʹ��" + name() + "��\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("��û��׼��ʹ���������צ���޷�ʹ��" + name() + "��\n");

        if( query("neili", me)<350 )
                return notify_fail("���������㣬�޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "ͻȻһ���ֽУ���������Ѫ���漴����һ����ץ��$n"
              HIR "��Ҫ����\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           (: final, me, target :));
                me->start_busy(2);
        } else
        {
                addn("neili", -50, me);
                msg += HIR "����$p" HIR "������$P" HIR "����ʽ��"
                       "�����мܣ���ס��$P" HIR "�Ķ��С�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target)
{
        int lvl;

        lvl = me->query_skill("claw");
        target->affect_by("sanyin",
                       (["level":query("jiali", me)*2+random(query("jiali", me)*3),
                          "id":query("id", me),
                          "duration" : lvl / 40 + random(lvl / 40) ]));

        return HIR "$p" HIR "����ʧ�룬��æ���ˣ�Ȼ��û"
               "�ܱܿ�����$P" HIR "��һצץ����Ѫ���죡\n" NOR;
}
