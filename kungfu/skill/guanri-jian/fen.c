#include <ansi.h>
#include <combat.h>

string name() { return HIR "������" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" +name()+ "��\n");

        if ((int)me->query_skill("guanri-jian", 1) < 150)
                return notify_fail("����ս���������죬����ʩչ" +name()+ "��\n");

        if (me->query_skill_mapped("sword") != "guanri-jian")
                return notify_fail("��û�м������ս���������ʩչ" +name()+ "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ����������ʩչ" +name()+ "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "��ת��������Ȼһ�ơ�" HIR "������" NOR +
              WHT "������������" + weapon->name() + WHT "Я��һ����"
              "������$n" WHT "ȫ��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           (: final, me, target, damage :));

                me->start_busy(3);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ��бԾ�ܿ���\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("guanri-jian", 1);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "ֻ��$n" HIR "һ���Һ���������Ѫ���������"
                "������һ���һ��յ��������졣\n" NOR;
}
