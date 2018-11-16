// This program is a part of NITAN MudLIB
// xiyan.c

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIM "������" NOR; }

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" + name() + "��\n");

        skill = me->query_skill("shenghuo-ling", 1);

        if (! objectp(weapon2 = query_temp("weapon", target)))
                return notify_fail("�Է�û��ʹ�ñ���������ʹ��ʥ���֮" + name() + "��\n");

        if (skill < 140)
                return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" + name() + "��\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" + name() + "��\n");

        if (query("neili", me) < 300)
                return notify_fail("�����������������ʹ��ʥ���֮" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "ͻȻ$N" HIM "�����һЦ��ʹ��ʥ���֮����"
              "�����" + weapon->name() + HIM "�ó�����СȦ"
              "����$n" HIM "��" + weapon2->name() + HIM "����"
              "��ס��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -240, me);
                msg += HIM "$n" HIM "ֻ����ǰ���������Ծ��������ʱֻ��"
                      "ͷ��Ŀѣ������һ�飬����" + weapon2->name() + HIM
                      "�ѱ�$N" HIM "���뻳�У�\n" NOR;
                me->start_busy(2);
                weapon2->move(me, 1);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "����$n" CYN "����$N" CYN "����ͼ�������б�"
                      "�л�����ܲ�͸�磬ʹ��$N" CYN "�޴����֡�\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
