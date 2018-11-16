// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���־�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;

        weapon=query_temp("weapon", me);

        if (! target)
                return notify_fail("��Ҫ�������ߣ�\n");

        if (! target->is_snake())
                return notify_fail("�����Щ���ǲ����ߣ���Ϲ��ʲô��\n");

        if (! living(target))
                return notify_fail("��������ʱ���ᶯ���ˣ��㲻���ٴ��ˡ�\n");

        if ((int)me->query_skill("shedu-qiqiao", 1) < 20)
                return notify_fail("����߶����ɻ�������죬���ܴ��ߡ�\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ�����Ϊ���������ܴ��ߡ�\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ����������ˡ�\n");

        if (weapon)
                msg = HIC "\n$N" HIC "�趯���е�" + weapon->name() +
                      HIC "������" + target->name() + HIC "���ߴ��"
                      "�˹�ȥ��\n" NOR;
        else
                msg = HIC "\n$N" HIC "���˫ָ����ָ��磬Ѹ���ޱȵ�"
                      "����" + target->name() + HIC "���ߴ���˹�ȥ"
                      "��\n" NOR;

        lvl = (int) me->query_skill("shedu-qiqiao", 1) +
              (int) me->query_skill("dodge");
        lvl = lvl * lvl / 10 * lvl;

        if( lvl/2+random(lvl)<query("combat_exp", target) )
        {
                msg += HIY "���ֻ����ž����һ����������" + target->name() +
                       HIY "���ߴ��ϡ�\n" NOR;
                lvl = (int) me->query_skill("force");
                lvl = lvl * 13 / 10;
                lvl = lvl * lvl / 10 * lvl;
//                if ( lvl / 2 + random(lvl) > (int) target->query("combat_exp") )
                if( lvl/2+random(lvl)<query("combat_exp", target) )
                {
                        msg += HIM "ֻ��" + target->name() + HIM
                               "��������ζ����£��Ͳ��ٶ����ˡ�\n" NOR;
                        message_combatd(msg, me);
                        target->unconcious(me);
                } else
                {
                        msg += HIR + "�����뵽" + target->name() +
                               HIR "������һ������Ȼ�������£���ʱһ����"
                               "��ֱ����$N" HIR "��\n\n" NOR;
                        message_combatd(msg, me);
                        target->kill_ob(me);
                }
        } else
        {
                msg += WHT "Ȼ��" + target->name() + WHT "����һ�������˹�ȥ��\n\n" NOR;
                message_combatd(msg, me);
                target->kill_ob(me);
        }
        addn("neili", -50, me);
        me->start_busy(2);

        return 1;
}