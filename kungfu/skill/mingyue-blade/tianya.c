// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "����"HIW"����" NOR; }

inherit F_SSERVER;

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
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("mingyue-blade", 1) < 200)
                return notify_fail("���������µ�������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<600 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("��û�м����������µ�������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "���е� " + weapon->name() +  HIC "��Ȼ̽�����仯��ͻȻ�վ���$nһʱ���飬���ζ�ʱ��$N��" + weapon->name() + HIC"��ס��\n"
                  "ֻ��$Nһ������ĺ�����" + weapon->name() + HIC"��$nͷ��λ������������\n "NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           HIR "$n" HIR "��ʱ��ʧɫ������ľ��,���޿ɱܣ�"
                                           "��ʱ������Ѫ��ģ������Ѫ������\n" NOR);
                addn("neili", -500, me);
                addn("shen", -100, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$p" HIC "��$P������ӿ����֪�����ɵ����������������ߣ����ڶ���������\n" NOR;
                addn("neili", -400, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
