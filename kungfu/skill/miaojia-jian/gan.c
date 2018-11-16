// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIY "���Ǹ���" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 200)
                return notify_fail("����ҽ���������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<600 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("��û�м�����ҽ���������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIY "$N" HIY "��������������" + wn + HIY "�ų�����⻪����Ȼ���ƿ�"
              "�����죬" + wn + HIY "��������������ǰ���$n" HIY "��ȥ��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "��ʱ��ʧɫ��ֻ���ؿڴ�"
                                           "һ�����Ǳ�" + wn + HIR "��Ȼ�Ѿ�����͸"
                                           "��������һ��Ѫ�꣡\n" NOR);
                addn("neili", -500, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$n" HIC "��" + wn + HIC "������ӿ����֪��"
                       "���ɵ����������������ߣ����ڶ���������\n" NOR;
                addn("neili", -500, me);
        }

        if (userp(me) && (int)me->query_skill("miaojia-jian", 1) < 260)
        {
                msg += HIY "ֻ��" + wn + HIY "���Ʋ���������ǰ�ɳ���"
                       "�ɣ�����û�����С�\n" NOR;
                weapon->move(environment(me));
        } else
                msg += HIY "Ȼ��$N" HIY "����һչ����ʱԾ�����ɣ���"
                       "����磬�������" + wn + HIY "�ֳ������С�\n" NOR;

        message_combatd(msg, me, target);
        return 1;
}