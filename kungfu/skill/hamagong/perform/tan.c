#include <ansi.h>
#include <combat.h>

string name() { return HIR "���䶾ҩ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        lvl = me->query_skill("hama-gong", 1);
        lvp = me->query_skill("poison");

        if (lvl < 160)
                return notify_fail("��ĸ�󡹦������죬����ʩչ" + name() + "��\n");

        if (lvp < 180)
                return notify_fail("��Զ������˽ⲻ��������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���Ϣ���㣬����ʩչ" + name() + "��\n");

        // ����NPC����ֱ��ʩչ
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("���������(hand)Щ��ҩ����ʩչ" + name() + "��\n");

        if (objectp(du) && ! mapp(query("poison", du)))
                return notify_fail("���������õ�" + du->name() + NOR "��"
                                   "�Ƕ�ҩ������ʩչ" + name() + "��\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("��" + du->name() + NOR "�����ȥ����"
                                   "����̫�ðɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "����";

        msg = HIR "$N" HIR "Ĭ���ڹ���ʩ����󡹦���С�" HIR "���䶾ҩ"
              HIR "����������" + name + HIR "��ಡ��ص���$n" HIR "��\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // �����ж�����������Է�������������Ч
        if (an / 2 + random(an) < dn)
        {
                msg += WHT "Ȼ��$n" WHT "ȫȻ���������ϣ�����һ�����ѽ�$N"
                       WHT "����������䡣\n" NOR;
                me->start_busy(2);
                addn("neili", -150, me);
        } else
        {
                ap = me->query_skill("force") +
                     me->query_skill("poison") * 3 / 4;

                // ������NPC��������֣��ټ������״��
                if (userp(me))
                        dp = target->query_skill("dodge") +
                             target->query_skill("martial-cognize");
                else
                        dp = target->query_skill("dodge") +
                             target->query_skill("parry");

                damage = pos / 2 + random(pos / 2);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIR "$n" HIR "һ�������������Ѿ��������ڣ���ʱʹ�಻����\n" NOR;

                        COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 35, " ");

                        target->affect_by("bt_poison",
                        ([ "level"    : lvp + random(lvp / 2),
                           "id":query("id", me),
                           "duration" : 20 + random(lvp / 30) ]));

                        target->receive_damage("jing", damage / 2, me);
                        target->receive_wound("jing", damage / 3, me);

                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "����$n" CYN "���Ʋ����æ��Ų���Σ���"
                               "�ڱܿ���$N" CYN "�����Ķ��衣\n" NOR;
                        me->start_busy(3);
                        addn("neili", -100, me);
                }
        }
        message_combatd(msg, me, target);

        // ���Ķ�ҩ����
        if (objectp(du))
        {
                if (du->query_amount())
                {
                        du->add_amount(-1);

                        if (du->query_amount() < 1)
                                destruct(du);
                } else
                        destruct(du);
        }
        return 1;
}
