#include <ansi.h>
#include <combat.h>

#define CHONG "��" HIY "��̹���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if( userp(me) && !query("can_perform/qishi-ji/chong", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHONG "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "club" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" CHONG "��\n");

        if (me->query_skill("qishi-ji", 1) < 100)
                return notify_fail("��ʥ��ʿ���Ϊ����������ʩչ" CHONG "��\n");

        if (me->query_skill_mapped("club") != "qishi-ji")
                return notify_fail("��û�м���ʥ��ʿꪣ�����ʩչ" CHONG "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʩչ" CHONG "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" CHONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ��������" + weapon->name() + HIY "������"
              "�̣����ƻ���������⣬��������$n" HIY "��\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(6));

        return 1;
}
