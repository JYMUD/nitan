// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return CYN "ѩ��ǧɽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        string *limbs, limb;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 150)
                return notify_fail("������ѩɽ�ƻ�򲻹�������ʩչ" +name()+ "��\n");

        if (me->query_skill_mapped("strike") != "shentuo-zhang")
                return notify_fail("��û�м�������ѩɽ�ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "shentuo-zhang")
                return notify_fail("��û��׼������ѩɽ�ƣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����Ц������һ����һ�С�ѩ��ǧɽ��������������ŭ"
              "����ӿ����������$n��\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                pmsg = HIR "��ʱֻ�������꡹һ�����죬$n" HIR "��"
                        "�ؿ��߹Ǿ�Ȼ���˼�����\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45, pmsg);

                me->start_busy(1);
                addn("neili", -50, me);
        } else
        {
                msg += CYN "����$n" CYN "������$P"
                       CYN "����ͼ�����μ������㿪����һ�ơ�\n"NOR;
                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
