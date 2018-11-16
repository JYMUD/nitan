// This program is a part of NITAN MudLIB
// jingmo.c ��ħһָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��ħһָ"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("����ħһָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("yizhi-chan", 1) < 120)
                return notify_fail("���һָ����������죬���ڻ��޷�ʹ�á���ħһָ����\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻹�������ʩչ����ħһָ����\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������޷����á���ħһָ����\n");

        if (me->query_skill_mapped("finger") != "yizhi-chan")
                return notify_fail("��û�м���һָ�����޷�ʹ�þ�ħһָ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���һ������ָ������һ��������ɱ������$n"
              HIY "�����ƻֺ�֮����\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "ֻ��$p" HIR "������������$P"
                                           HIR "��һָ��������ǰ�����ɵ�����"
                                           "�ҽУ��ؿ���Ѫֱ����\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "��æԾ�����㿪��$P"
                       CYN "��һָ��\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}