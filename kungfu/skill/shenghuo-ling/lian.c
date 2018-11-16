// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "������" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenghuo-ling", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" + name() + "��\n");

        if (skill < 150)
                return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" + name() + "��\n");

        if (query("max_neili", me) < 1600 )
                return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" + name() + "��\n");

        if (query("neili", me) < 350 )
                return notify_fail("�����������������ʹ��ʥ���֮" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "shenghuo-ling")
                return notify_fail("��û�м���ʥ���������ʹ��ʥ���֮" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����ͷ���$n" HIW "��ǰ����Ȼʹ��ʥ��"
              "�֮���������" + weapon->name() + NOR + HIW "����"
              "��������ʽ�����ޱȡ�\n" NOR;

        damage = damage_power(me, "sword");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");


        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
                       damage, 50, (: final, me, target, damage :));

        }
        else
        {
                addn("neili", -100, me);
                msg += CYN "$n" CYN "����ǰ�����������æ����������ǿ"
                      "�ֵ���������������ò�����������$N" CYN "��"
                      "����Χ֮�⡣\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int damage)
{

       target->receive_damage("jing", damage / 2, me);
       target->receive_wound("jing", damage / 4, me);
       target->start_busy(1);

       return HIR "$n" HIR "ֻ����ǰ���������ͻ"
              "Ȼ$N" HIR "˫�ֳ������Լ���ǰ������̫��Ѩ��"
              "ʱһ���ʹ��\n" NOR;
}
