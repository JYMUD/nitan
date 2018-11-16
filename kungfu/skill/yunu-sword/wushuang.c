// wushuang.c ��Ů���� ��˫�޶�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��˫�޶�"; }

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me, object target)
{
        object weapon;
        int damage;
        int skill;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��˫�޶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("yunu-sword", 1) < 80)
                return notify_fail("�����Ů����������죬����ʹ�á���˫�޶ԡ���\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ�������죬����ʹ�á���˫�޶ԡ���\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        if( query_temp("hsj_wu", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        msg = HIY "$N" HIY "˫������" + weapon->name() + HIY
              "����â������һʽ����˫�޶ԡ���Ԧ�����Ҿ��׵���$n"
              HIY "��̣�\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "sword");
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "����$N" HIR "��һ������ۣ�ȫȻ��"
                                           "���ֵ���һ���֮���Ѿ�����һ���̵���Ѫ�ɽ���" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ������һԾ�����˿�ȥ��" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}
