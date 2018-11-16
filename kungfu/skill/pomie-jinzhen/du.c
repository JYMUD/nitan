#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return YEL "����ɽ�" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me) )
            || query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű�����\n");

        if (weapon->query_amount() < 30)
                return notify_fail("������Ҫ���ж�ʮö��������ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("pomie-jinzhen", 1)) < 150)
                return notify_fail("���������벻����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = YEL "ֻ��$N" YEL "����һ�ʩ����" HIR "����ɽ�" NOR +
              YEL "��������" + weapon->name() + YEL "�缱�籩�����$n"
              YEL "��ȥ��\n" NOR;

        my_exp=attack_power(me, "throwing");
        ob_exp=defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                n = 4 + random(4);
                if (random(my_exp) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 2) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 4) > ob_exp) n += 4 + random(8);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += HIR "��ʱ��һƬ��â����$n" HIR "�ķ�������һ��"
                       "�ҽУ�" + chinese_number(n) + "����Ѫ�ɽ�����"
                       "��\n" NOR;

                target->receive_damage("qi", skill + random(skill), me);
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)*2+300+n*15);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "����$n" CYN "˿�����Ҵ��⣬����������"
                       "�ܣ��㿪�����еİ�����\n" NOR;
                message_combatd(msg, me, target);
        }
        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}