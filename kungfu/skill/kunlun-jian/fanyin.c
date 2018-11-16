#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, jing_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return notify_fail("��ĵ��ټ������Ҳ�������, ��������������������\n");

        if (me->query_skill("kunlun-jian", 1) < 120)
                return notify_fail("������ؽ����ȼ�����, ��������������������\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ�����޷��ﵽʹ�á���������������ľ��磡\n");

        if( query("neili", me)<300 )
                return notify_fail("����������������㡸���������������������\n");

        msg = MAG "$N΢΢һЦ�����ֺ��ս�����������ָ��׼" + weapon->name() + NOR + MAG"�������ᵯ��������΢��������������\n��ʱ����һ����������......\n" NOR;

        skill = me->query_skill("kunlun-jian",1);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                jing_wound = damage_power(me, "sword") +
                           (int)me->query_skill("tanqin-jifa", 1) * 2;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, jing_wound, 96,
                                           MAG "$n��ʱֻ������������������һ��̽�˫����ɲ�Ǽ�ͷ��Ŀѣ��ȫ���ʹ��\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += HIG "����$n��æ���ľ�������������˿������$N�����ĸ��š�\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
