// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "˭������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��" + name() + "��\n");

        if ((lvl = (int)me->query_skill("yitian-zhang", 1)) < 120)
                return notify_fail("������������Ʋ�����죬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("����������̫��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "yitian-zhang")
                return notify_fail("��û�м������������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "yitian-zhang")
                return notify_fail("��û��׼��ʹ�����������ƣ�����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "������ͨ�������������ƶ�ʮ����һ���ǳɣ�˫��"
              "Я������ɽ����֮������$n" HIY "��\n\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ʱ���ú���������ȫȻ����"
                       "���������ƣ�ֻ��ƴ���˶��ֵ���\n" NOR;
                count = ap / 15;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "����һ����������ֵ�������������"
                       "�ھ��κ���֮�У����ҵ�����ȴ�ǲ�����\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 10; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}
