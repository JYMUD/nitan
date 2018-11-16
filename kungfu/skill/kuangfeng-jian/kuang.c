// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "�������"; }

int perform(object me, object target)
{
        string msg;
        int extra, damage, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target
        ||  ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail("�����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !weapon=query_temp("weapon", me) )
                return notify_fail("��ûװ������ô��\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õı������ԣ�\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("��Ŀ��콣����������ʹ���� [ ������� ] ��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ľ���������죬ʹ���� [ ������� ] �ľ��У�\n");

        extra = me->query_skill("kuangfeng-jian", 1);

        msg = HIY "$N" HIY "��бб�̳�������ɹɽ������ν����ս�������һ˲�䣬��ر�ã���Ӱ��������С��\n"
              "�����������ŷ磬���ﺬ�Ž�Ӱ���ǽ����������������ɫ��������ǵ�Ϯ��$n��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "ֻ�������к��һ�£�"
                                           "�������󵹷ɳ�ȥ�������ڵأ��������ۡ�������һ����Ѫ���\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "����$p" CYN "������$P" CYN "�ĺݶ���ͼ�����������������㿪��$P" CYN "����һ�����µĹ�����\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}