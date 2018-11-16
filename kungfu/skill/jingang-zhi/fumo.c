// This program is a part of NITAN MudLIB
// fumo.c  ��շ�ħ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��շ�ħ��"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����շ�ħ����ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʹ�á���շ�ħ������\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("jingang-zhi", 1) < 150)
                return notify_fail("��Ĵ������ָ��Ϊ������Ŀǰ����ʹ�á���շ�ħ������\n");

        if( query("neili", me)<400 )
                return notify_fail("��������������޷�ʹ�á���շ�ħ������\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("��û�м����������ָ������ʹ�á���շ�ħ������\n");

        msg = HIY "$N" HIY "��������һ����⣬���ȫ����������ʳָ����һ��"
              HIY "���������ն�������ͬ����һ�����$n" + HIY "��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -200, me);
                msg +=  COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55,
                                    HIR "ֻ��$p" HIR "һ���ҽУ��ѱ������ؿ�ҪѨ��"
                                    "$p" HIR "ֻ�����ؿ���Ѫ��ӿ��ȫ����Ѫ"
                                    "�������۵�һ���³�һ����Ѫ���಻���ԣ�\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$N" CYN "����ͼ������"
                       CYN "���Ʈ�����ɣ��������һ������һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}