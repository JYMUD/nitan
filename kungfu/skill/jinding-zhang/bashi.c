// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "��ʽ��һ" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int count,d_count,qi, maxqi, skill;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jinding-zhang", 1) < 100)
                return notify_fail("��Ľ����Ƶ���ϰ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "jinding-zhang")
                return notify_fail("��û�м��������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "jinding-zhang")
                return notify_fail("������û��׼��ʹ�ý����ƣ�����ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��������һ����������ȫ��Ĺ�����"
              "˫�������ĳ���ֻ���ù���һ���죡\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage += (int)me->query_skill("linji-zhuang", 1);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "ֻ��������ӰƮ������������$n" HIR
                                           "ȫ�������λ��$n" HIR "��ʱ����������"
                                           "�ƣ�\n" NOR);
                addn("neili", -100, me);
                me->start_busy(2);
         } else
         {
                msg += CYN "����$p" CYN "�͵����һԾ��������$P"
                       CYN "�Ĺ�����Χ��\n" NOR;
                me->start_busy(3);
         }
         message_combatd(msg, me, target);
         return 1;
}
