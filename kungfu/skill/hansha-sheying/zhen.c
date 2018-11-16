#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ӱ��" NOR; }

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű���������ʩչ" + name() + "��\n");

        if (weapon->query_amount() < 10)
                return notify_fail("����Ҫ��ʮö��������ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("hansha-sheying", 1)) < 120)
                return notify_fail("��ĺ�ɳ��Ӱ������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIR "ֻ�������쬡�������һ�ɾ����$N" HIR "�����������$N" HIR
             "����" + weapon->name() + HIR "���������$n" HIR "���ֹ�ȥ��\n";

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                n = 1 + random(2);
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);

                msg += "���$p" HIR "��Ӧ����������$P" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "��\n" NOR;

                damage = damage_power(me, "throwing");
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += NOR + CYN "����$p" CYN "�����$P" CYN "����������" +
                       weapon->name() + NOR + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}