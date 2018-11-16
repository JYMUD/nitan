#include <ansi.h>
#include <combat.h>

string name() { return HIY "��¾��� " NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("guyue-chan", 1) < 80)
                return notify_fail("����²���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "guyue-chan")
                return notify_fail("��û�м������²���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<600 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIW "$N" HIW "ŭ��һ���������е�" + wn + HIW "����ú������죬"
              "��Ȼ����$n" HIW "��ȥ��\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$n" HIR "ֻ���ۻ����ң��������Ѳ�����"
                                           "��" + wn + HIR "�����ؿڣ���ʱ���һ����"
                                           "Ѫ��\n" NOR);
                me->start_busy(2);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "���и����ޱȣ�����Ӳ�ӣ�ֻ��\n"
                       "����һ���Ŷ�����С�\n"NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }

        message_combatd(msg, me, target);
        return 1;
}