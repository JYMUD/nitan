#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "<������>" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int attack;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (member_array("BASE_SKILL", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "BASE_SKILL" )
                        return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");
        }

        if ((int)me->query_skill("SKILL", 1) < 400)
                return notify_fail("��" + to_chinese("SKILL") + "������죬����ʩչ" + name() + "��\n");

        if (member_array("BASE_SKILL", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("BASE_SKILL") != "SKILL")
                        return notify_fail("��û��׼��" + to_chinese("SKILL") + "������ʩչ" + name() + "��\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "<PFM��������>" + "\n" + NOR;

        ap = attack_power(me, "BASE_SKILL");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "BASE_SKILL");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "<PFM��������>" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "<PFMʧ������>" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
