#include <ansi.h>
#include <combat.h>

string name() { return HIY "���汩��" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon, weapon2;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jinwu-blade", 1) < 120)
                return notify_fail("��Ľ��ڵ���������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "jinwu-blade")
                return notify_fail("��û�м������ڵ������޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�����������ȫ��֮��ע��" + weapon->name() +
              HIY "����˳�����£���ʱһ�������ĵ�âֱ��$n" HIY "��ȥ��\n"
              NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if( objectp(weapon2=query_temp("weapon", target) )
            && query("skill_type", weapon2) == "sword"
           && target->query_skill_mapped("sword") == "xueshan-jian")
        {
                msg += HIY "$n" HIY "��æ��æ��ѩɽ���������ֵ�����֪$N"
                       HIY "��������ѩɽ�������ǰ㣬" + weapon->name() +
                       HIY "��â��ʱ\n�ֱ�����������ȫ����$n" HIY "����"
                       "�н��У�\n" NOR;
                ap += ap / 2;
        }

        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "��$n" HIC "ȴ������㣬һ˿���ң�"
                       "ȫ�񽫴��л��⿪����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "ֻ��$n" HIR "һ���ҽУ�����һ���������У��˿�"
                "��ɼ��ǣ���Ѫ�Ĵ��ɽ���\n" NOR;
}
