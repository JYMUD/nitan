// This is player's own perform (Write by Lonely@nt2)
//Createby��ˮ��(Rain)atWed Aug 20 00:34:46 2014
// һ���ɿ�(yidao)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "һ���ɿ�" NOR; }

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

        if (member_array("blade", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "blade" )
                        return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");
        }

        if ((int)me->query_skill("mad-blade", 1) < 400)
                return notify_fail("��" + to_chinese("mad-blade") + "������죬����ʩչ" + name() + "��\n");

        if (member_array("blade", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("blade") != "mad-blade")
                        return notify_fail("��û��׼��" + to_chinese("mad-blade") + "������ʩչ" + name() + "��\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N��������ֱֱ���������޻������ԣ�ȴȥ�Ƽ��죬��δ�����ȼ���$n����������" + "\n" + NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "ֻ��$nһ���ҽУ��ؿڸ�����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p���Ʋ�������ˣ����ձܹ�$P�����ɱ�У����������У������ѿ���һ������ӣ�" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
