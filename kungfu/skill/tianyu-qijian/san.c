// This program is a part of NITAN MudLIB
// san.c  ��Ůɢ��

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "��Ůɢ��"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg, pmsg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����Ůɢ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 100)
                return notify_fail("��������潣������죬����ʹ�á�\n");

        if ((int)me->query_skill("xiaowuxiang", 1)<100
                && (int)me->query_skill("bahuang-gong", 1)<100
                && (int)me->query_skill("beiming-shengong", 1)<100)
                return notify_fail("�����ң���ڹ���򲻹���\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û��������ң���ڹ���\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á���Ůɢ������\n");

        msg = CYN "\n$N����Ϣ�������󼲶������ǧ�������������ǵط���$n��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -200, me);
                pmsg = HIR "\nֻ��$N������Ϊһ�ߣ�����$n��\n$nֻ��һ���������Ķ�������ͷһ����Ѫ���������\n\n" NOR;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p�͵���ǰһԾ,������$P�Ĺ�����Χ��\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
