#include <ansi.h>
#include <combat.h>

string name() { return HIC "Ӱ��ɻ�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        mapping p;
        int i, af, lvl, count;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((lvl = (int)me->query_skill("lanhua-shou", 1)) < 140)
                return notify_fail("��������Ѩ�ֲ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("��û�м���������Ѩ�֣�����ʩչ" + name() + "��\n");

        if (! mapp(p = me->query_skill_prepare())
           || p["hand"] != "lanhua-shou")
                return notify_fail("��û��׼��������Ѩ�֣�����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "΢һ����˫��������״����������һ�����ľ�����ʱֱ��$n"
              HIC "ȫ�����ҪѨ��\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ʱ�����ۻ����ң�ȫȻ�ֱ�"
                       "������α��ֻ��ƴ���˶��ֵ���\n" NOR;
                count = lvl / 5;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIY "����$n" HIY "��������������ֵ���˿"
                       "��������Ӱ�ĸ��ţ���\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        af = member_array("hand", keys(p));

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                set_temp("action_flag", af, me);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(random(3));
        addn_temp("apply/attack", -count, me);
        return 1;
}
