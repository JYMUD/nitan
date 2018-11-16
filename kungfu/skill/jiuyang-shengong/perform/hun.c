// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "����һ��" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        /*
        if (!SKILLS_D->valid_perform(me, __FILE__))
                return 0;
        */
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("jiuyang-shengong", 1) < 180)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" + name() + "��\n");

        if (query("neili", me) < 300)
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "��ǰһ����˫�ֻ�Ȧ���ĵ�̫��֮�⡣���Ķ�ʱ��"
              "��һ�����ţ���$n" HIR "�����ȥ��\n" NOR;

        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "force") + target->query_con();

        addn("neili", -50, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "Ȼ��$n" HIY "ȫ���ֵ������ڽ�$N" HIY
                       "���������Ų�����\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -200, me);
                me->start_busy(1);
                damage = damage_power(me, "force");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "$n" HIR "��æ������ˣ�����������"
                                           "�ø��죬ֻ��$p" HIR "һ���ҽУ���Ѫ��"
                                           "����\n" NOR);
        }
        message_combatd(msg, me, target);
        return 1;
}
