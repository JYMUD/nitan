#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "staff")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("yinhu-zhang", 1) < 100)
                return notify_fail("�������ȷ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "yinhu-zhang")
                return notify_fail("��û�м��������ȷ�������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n$N" HIM "һ�����ȣ���Ȼ���ڿն���ʩ�����С�" HIW "����"
              "��" HIM "��������" + weapon->name() + HIM "������������ƾ��˵�"
              "Ϯ��$n" HIM "��\n" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "��ȫ�޷�����������ʵ��ֻ"
                                           "�����ء���һ�����ѱ�$N" HIR "���м��\n" NOR);
                me->start_busy(3);
                addn("neili", -180, me);
        } else
        {
                msg = CYN "����$n" CYN "�����мܣ������ұܣ��ò���"
                       "�׵ֵ�ס��$N" CYN "�Ĺ�����\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}