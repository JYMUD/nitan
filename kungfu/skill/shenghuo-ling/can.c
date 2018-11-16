// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��Ѫ��" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int damage, skill, ap, dp;
        int l;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target) target = offensive_target(me);

        skill = me->query_skill("shenghuo-ling", 1);

        if (! (me->is_fighting()))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" +
                                   name() + "��\n");

        if (skill < 220)
                return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ����"
                                   "��֮" + name() + "��\n");

        if (me->query_skill("force") < 350)
                return notify_fail("����ڹ���򲻹�������ʹ��ʥ���֮" +
                                   name() + "��\n");

        if (query("max_neili", me) < 5000)
                return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" +
                                   name() + "��\n");

        if (query("neili", me) < 400)
                return notify_fail("�����������������ʹ��ʥ���֮" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "shenghuo-ling")
                return notify_fail("��û�м���ʥ������޷�ʹ��" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����Х������" + weapon->name() +
              HIR "һת��������ʱ��ù����ޱȣ������벻���ķ�"
              "λ����$n" HIR "��\n" NOR;

        // ���ʥ�������߱��� max_hit����������˺���
        // ԭ���и���˺��ѿ�͸�����������Գ������ӹ�
        // ����Ч�ʷǳ���
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ȫ�޷���͸$N" HIR "������ʵ�����ɵ���"
                       "�����⣬��ʽһ�ͣ���ʱ�����ٳ���\n" NOR;
                count = ap / 6;
                addn_temp("shenghuo-ling/max_hit", 1, me);
        } else
        {
                msg += HIY "$n" HIY "��$N" HIY "������ӿ���ĵ�һ��������"
                       "��С�Ľ��С�\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);

        l = skill / 50;
        if (l > 15) l = 15;
        for (i = 0; i < l; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        delete_temp("shenghuo-ling/max_hit", me);
        me->start_busy(1 + random(4));
        return 1;
}