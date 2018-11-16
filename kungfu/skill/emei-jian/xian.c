#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "������" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("emei-jian", 1) < 60)
                return notify_fail("��Ķ��ҽ���������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "emei-jian")
                return notify_fail("��û�м������ҽ������޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�粽��ǰ������" + weapon->name() +
              HIY "����ü������ת��ɣ����������ֱ����$n"
              HIY "��\n" NOR;

        addn("neili", -75, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
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
        return  HIR "��ʱֻ�����͡���һ����$n" HIR "�Ը�������"
                "����һ��������Ѫ���졣\n" NOR;
}
