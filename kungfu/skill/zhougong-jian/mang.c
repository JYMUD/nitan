// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��â" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        object ob;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("zhougong-jian", 1) < 140)
                return notify_fail("����ܹ������̫ǳ������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ̫ǳ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("���������Ϊ̫ǳ������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        damage = damage_power(me, "sword");

        msg = HIW "$N" HIW "һ����Х������" + weapon->name() + HIW "��"
                  "�ջ��������ⶸȻ����������²�������â��һ�������ƿ�"
                  "��ֱ����$n��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "$n" HIR "һ���ҽУ������Ľ����ѻ�"
                                           "�����ţ������ϴ̳�����Ѫ������Ѫ��Ȫ"
                                           "ˮ��ӿ����\n" NOR);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ��бԾ�ܿ���\n" NOR;
        }

        msg += HIW "\n$N" HIW "��$n" HIW "Ӧ�Ӳ�Ͼ��һ����Ц�����л�����"
              "����һ�Ǹ��������Ľ�â�ɽ��ⵯ����������ֱ��$n" HIW
              "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "ֻ�������͡�һ������������$n" HIR
                                           "�ؿڣ�����һ����ڴ��Ѫ����$n" HIR
                                           "����һ������Ҳ�޷�վ��\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ǿ��ȫ���ʹ��������һԾ���ܿ���$N"
                       CYN "��ǿ���ɱ�š�\n" NOR;
        }
        me->start_busy(2 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}
