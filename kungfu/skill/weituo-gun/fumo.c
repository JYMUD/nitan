// This program is a part of NITAN MudLIB
// fumo.c Τ�з�ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "Τ�з�ħ"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Τ�з�ħ��ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "club" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("weituo-gun", 1) < 135)
                return notify_fail("���Τ�ӹ�����Ϊ������Ŀǰ����ʹ��Τ�з�ħ��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����������������ʹ��Τ�з�ħ��\n");

        if (me->query_skill_mapped("club") != "weituo-gun")
                return notify_fail("��û�м���Τ�ӹ���������ʹ��Τ�з�ħ��\n");

        if( query("shen", me)<10000 )
                return notify_fail("���������㣬�������Τ�з�ħ�ľ��衣\n");

        msg = HIY "$N" HIY "��ɫ��ͣ�����һ�ɴ���֮�⣬���е�" + weapon->name() +
              HIY "������������Գ����Τ������������䣬����ס$n" + HIY "��\n" NOR;

        if (target->is_bad())
        {
                ap=query("shen", me)/1000;
                if (ap > 100) ap = (ap - 100) / 4 + 100;
                if (ap > 200) ap = (ap - 200) / 4 + 200;
                if (ap > 300) ap = (ap - 300) / 4 + 300;
                if (ap > 500) ap = 500;
                msg += HIR "$n" HIR "ƽ�������٣����˴���˾������в�����Ȼ��\n" NOR;
        } else
                ap = 0;

        ap += attack_power(me, "club");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "club");
                damage+= query("jiali", me);
                addn("neili", -500, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 150,
                                           HIR "���ֻ��$p" HIR "һ���ҽУ���$P"
                                           "һ���Ӵ���Ҫ��������һ�����̣����Ƕ�����Ѫ����\n" NOR);
                me->start_busy(1 + random(2));

        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "ǿ������û�б�$P"
                       CYN "���Ի�Ӳ�����ļ�ס��$P" CYN "��һ�У�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}