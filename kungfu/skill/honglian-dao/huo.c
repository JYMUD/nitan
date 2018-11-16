#include <ansi.h>
#include <combat.h>

#define HUO "��" HIR "���ǻ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if( userp(me) && !query("can_perform/honglian-dao/huo", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" HUO "��\n");

        if ((int)me->query_skill("force") < 120 )
                return notify_fail("����ڹ���򲻹�������ʩչ" HUO "��\n");

        if ((int)me->query_skill("honglian-dao", 1) < 80)
                return notify_fail("���������������죬����ʩչ" HUO "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ����������ʩչ" HUO "��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʩչ" HUO "��\n");

        if (me->query_skill_mapped("blade") != "honglian-dao")
                return notify_fail("��û�м�����������������ʩչ" HUO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "ʩ��������������������" + weapon->name() +
              HIR "��ת��ɣ�����������ϯ��$n" HIR "����\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -80, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(4));
        return 1;
}