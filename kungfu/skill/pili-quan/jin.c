// ���׾�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return MAG "���׾�" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("pili-quan", 1) < 40)
                return notify_fail("���������ȭ������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "pili-quan")
                return notify_fail("��û��׼��ʹ��������ȭ���޷�ʩչ" + name() + "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һת��������˫ȭ��ʩ�����С�" HIW "���׾�" HIY "����˫ȭѸ���ޱ�"
              "��Ϯ��$n" HIY "��\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                addn("neili", -120, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "ֻ��$P" HIR "��һȭ��$p" HIR
                                           "���˳�ȥ�����ص�ˤ�ڵ��ϣ���Ѫ��ֹ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

