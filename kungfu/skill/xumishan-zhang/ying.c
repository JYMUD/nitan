// This program is a part of NITAN MudLIB
// ying.c ����ɽ�ơ�Ⱥɽ��Ӱ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "Ⱥɽ��Ӱ"; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ⱥɽ��Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á�Ⱥɽ��Ӱ����\n");

        if ((lvl = (int)me->query_skill("xumishan-zhang", 1)) < 150)
                return notify_fail("�������ɽ���Ʋ�����죬����ʹ�á�Ⱥɽ��Ӱ����\n");

        if( query("neili", me)<500 )
                return notify_fail("����������̫��������ʹ�á�Ⱥɽ��Ӱ����\n");

        if (me->query_skill_prepared("strike") != "xumishan-zhang")
                return notify_fail("������û��׼��ʹ������ɽ�ƣ�����ʹ�á�Ⱥɽ��Ӱ����\n");

        msg = HIY "$N" HIY "����ʹ������ɽ���Ƶľ��С�Ⱥɽ��Ӱ����˫��"
              "ƽƽ��$n" HIY "��ȥ��$n" HIY "��ʱ����һ����ɽ������"
              "�������Լ�ӿ����\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ʱ���ú���������ȫȻ����"
                       "���������ƣ�ֻ��ƴ���˶��ֵ���\n" NOR;
                count = ap / 20;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "����һ����������ֵ�������������"
                       "�ھ��κ���֮�У����ҵ�����ȴ�ǲ�����\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}
