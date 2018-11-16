#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "�۰�Ⱥɽ" NOR; }

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

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("chuangwang-dao", 1) < 40)
                return notify_fail("��Ĵ��������������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "chuangwang-dao")
                return notify_fail("��û�м�����������������ʩչ" + name() + "��\n");

        if( query("neili", me)<50 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ��ŭ�ȣ�����" + weapon->name() +  HIY "�����ն"
              "�����������ʱ����������$n" HIY "��\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
                                           HIR "$n" HIR "�������ɣ����뱻$N" HIR
                                           "һ�����У���ʱһ���Һ���Ѫ���岽��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "΢΢һЦ�����ӳ�һ��ƫ�������㿪$P"
                       CYN "��һ����\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}