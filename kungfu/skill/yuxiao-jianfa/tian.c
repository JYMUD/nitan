#include <ansi.h>

#include <combat.h>

string name() { return HIC "��������" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("��û�м������｣��������ʩչ" + name() + "��\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 120)
                return notify_fail("�����｣���ȼ�����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 120)
                return notify_fail("��̲�����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "һ����Х������" + weapon->name() +
              HIC "����������������ֹ����Ӱ��ҹĻ������$n" HIC "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -120, me);
                qi_wound = damage_power(me, "sword");
                qi_wound+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 70,
                                           HIR "$n" HIR "��ʱ������ǰ�����������˫������"
                                           "������ȫ���������һ�㣡\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += CYN "����$n" CYN "���ľ��������ֻ�������$N"
                       CYN "������Ʋ��һ�ߡ�\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}