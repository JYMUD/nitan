// This program is a part of NITAN MudLIB
// sanjue.c  ��Ħ�� ��Ħ������

#include <ansi.h>

inherit F_SSERVER;
string name() { return "��Ħ������"; }

int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����Ħ��������ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_dex() < 30)
                return notify_fail("�����������Ŀǰ������ʹ�����������\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("dodge") < 200)
                return notify_fail("����Ṧ��Ϊ����������ʹ�ô�Ħ��������\n");

        if (me->query_skill("sword") < 200)
                return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�ô�Ħ��������\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������ʹ�ô�Ħ��������\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("��û�м�����Ħ��������ʹ�ô�Ħ��������\n");

        msg = HIC "$N" HIC "ʹ����Ħ���ľ�������Ħ��������������Ȼ�ӿ죡\n" NOR;
        message_combatd(msg, me);

        addn("neili", -75, me);

        // The first attack
        addn_temp("apply/attack", 1000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // The second attack
        addn_temp("apply/attack", 2000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // The third attack
        addn_temp("apply/attack", 3000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // Back
        addn_temp("apply/attack", -6000, me);

        me->start_busy(1 + random(2));

        return 1;
}
