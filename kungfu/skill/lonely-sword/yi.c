// yi.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�þ��С�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("�޽�������ý��⣿\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ������������޷�ʹ�ý��⣡\n");

        if ((int)me->query_skill("lonely-sword", 1) < 120)
                return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�ý��⣡\n");

        if (me->query_skill_mapped("sword") != "lonely-sword")
                return notify_fail("��û�м������¾Ž����޷�ʹ�ý��⣡\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch (random(3))
        {
        case 0:
                msg = HIM "$N" HIM "һ���̳���������Ҳ��֪��Ҫ�����δ���\n" NOR;
                break;

        case 1:
                msg = HIM "$N" HIM "���ֻ������е�" + weapon->name() +
                       HIM "������Ŀ�ģ������κ���ʽ��\n" NOR;
                break;

        default:
                msg = HIM "$N" HIM "бб�̳�һ����׼ͷ֮����˷�����˼��\n" NOR;
                break;
        }

        ap = attack_power(me, "sword") + me->query_skill("sword-cognize");
        dp = defense_power(target, "parry") + target->query_skill("sword-cognize");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           HIR "$n" HIR "ȫȻ�޷����$P"
                                           HIR "��Ī�������������һ�����񣬵�ʱ�ܴ���\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "��Ȼ��֮����û�н�$P"
                       CYN "���з������ϣ����ּܿ�����©���������\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}