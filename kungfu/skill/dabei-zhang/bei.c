#include <ansi.h>
#include <combat.h>

#define BEI "��" HIW "���ﾨ�δ����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;
        /*
        if( userp(me) && !query("can_perform/dabei-zhang/bei", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
        */
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BEI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(BEI "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("���ڹ���Ϊ����������ʩչ" BEI "��\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("��������Ϊ����������ʩչ" BEI "��\n");

        if ((int)me->query_skill("dabei-zhang", 1) < 220)
                return notify_fail("������ƻ�򲻹�������ʩչ" BEI "��\n");

        if (me->query_skill_mapped("strike") != "dabei-zhang")
                return notify_fail("��û�м��������ƣ�����ʩչ" BEI "��\n");

        if (me->query_skill_prepared("strike") != "dabei-zhang")
                return notify_fail("��û��׼�������ƣ�����ʩչ" BEI "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������������ʩչ" BEI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��Ȼһ����Х��ʩ����" HIG "���ﾨ�δ����"
              HIW "����˫�Ʒ�����������Ӱ����������$n" HIW "��\n" NOR;  

        ap = attack_power(me, "strike") + me->query_int();

        dp = defense_power(target, "force") + target->query_int();

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "$n" HIR "���Ʋ�͸������ʵ��$N" HIR
                                           "˫������$p" HIR "ǰ�أ������꿦�ꡱ��"
                                           "�����������߹ǡ�\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "�������ƷǷ�������"
                       "�����мܣ�����������Ծ������\n" NOR;
                message_combatd(msg, me, target);
        }

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        me->start_busy(4 + random(3));
        return 1;
}
