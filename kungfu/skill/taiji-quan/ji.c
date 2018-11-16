#include <ansi.h>
#include <combat.h>

string name() { return HIW "���־�" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("���̫��ȭ�ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("��û�м���̫��ȭ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "taiji-quan")
                return notify_fail("������û��׼��ʹ��̫��ȭ���޷�ʹ��" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "ʹ��̫��ȭ�������־����ҽ�ʵ������飬ճ��ճ"
              "�棬�����Ѵ�ס$n" HIW "���󣬺ᾢ������\n" NOR;

        damage = damage_power(me,"cuff");
        damage+= query("jiali", me);

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -30, me);
                me->start_busy(2);
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK,
                       damage, 70, HIR "$n" HIR "�Բ�������$N" HIR
                       "��ôһ����ֻ��ȫ������������������󺣣���Ӱ"
                       "���١�\n" NOR);
        }
        else
        {
                addn("neili", -10, me);
                msg += CYN "$n" CYN "��״���һ������æ�������������"
                       "���ڱܿ���$N" CYN "��һ����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}