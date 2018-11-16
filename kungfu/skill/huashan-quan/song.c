
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "����ʽ" NOR; }

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

        if ((int)me->query_skill("huashan-quan", 1) < 40)
                return notify_fail("��Ļ�ɽȭ��������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "huashan-quan")
                return notify_fail("��û��׼��ʹ����ʯ����ȭ���޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ŭ��һ������ȭֱ�����������������ǻ�ɽ������" HIG "����ʽ" HIY
               "����ȭ����죬Ϯ��$n" HIY "��\n"NOR;

        ap = attack_power(me, "cuff") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_str()*10;
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                addn("neili", -60, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "ֻ��$P" HIR "һȭֱ����$p" HIR
                                           "��������ȴ�Ѳ�����һȭ���صش������ϣ�\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}