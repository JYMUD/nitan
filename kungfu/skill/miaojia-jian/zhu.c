#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "��������" NOR; }

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
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 120)
                return notify_fail("����ҽ���������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150 )
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("��û�м�����ҽ���������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��Ȧ����" + weapon->name() + HIY "ʩ���������项б"
              "������������ʱ�³�һ����â�����������$n" + HIY "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "��״��æ�񵲣�����������"
                                           "������ʱֻ��ȫ��һ�飬������͸�ض�����\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "����" CYN "$n" CYN "һ����"
                       "Ц������һԾ���𣬱ܿ���" CYN
                       "$N" CYN "�����Ľ�����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}