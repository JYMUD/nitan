// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "��ս���" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��" + name() + "��\n");

        if ((int)me->query_skill("canhe-zhi", 1) < 160)
                return notify_fail("��Ĳκ�ָ��Ϊ���ޣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("������û��׼��ʹ�òκ�ָ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "˫�ֺ�ʮ��΢΢һЦ���ĵ��黨֮�⡣ʳָ����ָ"
              "����һ������ʱһ����������������$n" HIY "Ϯȥ��\n" NOR;

        ap=attack_power(me, "finger") + me->query_skill("force", 1);
        dp=defense_power(target, "force") + target->query_skill("buddhism",1);
        me->start_busy(2);

        if ((int)target->query_skill("buddhism", 1) >= 200
            && random(5) == 1)
        {
                addn("neili", -400, me);
                me->start_busy(3);
                msg += HIY "����$n" HIY "Ҳ����¶Ц�ݣ���������һ����˳��"
                       "���ϣ��ٽ�$N" HIY "��ָ�����Ŵ�����\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           (: final, me, target, damage :));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 6, me);
        target->receive_wound("jing", damage / 10, me);
        return  HIR "ֻ�������͡�һ����ָ������$n" HIR
                "��ǰ����һ��Ѫ��ģ���Ĵ󶴣�͸����롣\n" NOR;
}