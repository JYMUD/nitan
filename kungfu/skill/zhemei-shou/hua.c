// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

string name() { return HIR "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, p;
        int lv, cost_neili;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("beiming-shengong", 1) < 220
        &&  (int)me->query_skill("xiaowuxiang", 1) < 220
        &&  (int)me->query_skill("bahuang-gong", 1) < 220)
                return notify_fail("��ı�ڤ�񹦻�򲻹�������ʩչ" + name() + "��\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 220)
                return notify_fail("����ң��÷�ֵȼ�����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "��������һ���������ֻӳ�����Ե��ʱϼ�����������"
              "��ɫ�����$n" HIM "ϯ�������\n" NOR;

        ap = attack_power(me, "hand") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -500;
                if (lv >= 240)cost_neili = -470;
                if (lv >= 260)cost_neili = -440;
                if (lv >= 280)cost_neili = -400;
                if (lv >= 300)cost_neili = -360;
                if (lv >= 320)cost_neili = -320;
                if (lv >= 340)cost_neili = -300;
                if (lv >= 360)cost_neili = -270;
                if (lv >= 400)cost_neili = -200;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIM "ֻ��$n" HIM "һ����Х��$N" HIM "����ɫ��"
                               "���Ѿ���ע��$p" HIM "���ڣ���ʱ��$p" HIM "��"
                               "Ϊһ̲Ѫˮ��\n" NOR "( $n" RED "���˹��أ���"
                               "��������в�����ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                        addn("neili", cost_neili, me);
                        me->start_busy(1);
                } else
                {
                        damage = damage_power(me, "hand");
                        damage+=query("jiali", me);
                        damage+=query_temp("apply/unarmed_damage", me);
                        damage+=query_temp("apply/damage1", me);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg += HIM "$n" HIM "ֻ��΢΢һ㶣�$N" HIM "����ɫ�ƾ��������"
                               "�룬$p" HIM "���������ú�¯һ�㣬��Ż������Ѫ��\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        addn("neili", cost_neili, me);
                        me->start_busy(3);
                }
        } else
        {
                msg += CYN "$p" CYN "��״��ʧɫ����ȫ���Ʋ�͸$P"
                       CYN "���а��أ���������Ծ����������������\n" NOR;
                addn("neili", -200, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {
                target->receive_damage("qi", 100, me);
                target->unconcious(me);
        }

        return 1;
}