// ziwu.c �����׹�צ - ��������צ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "��������צ" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��"+name()+"��\n");

        if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 140)
                return notify_fail("��ľ����׹�צ��������죬����ʹ��"+name()+"��\n");

        if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao")
                return notify_fail("��û��׼�������׹�צ���޷�ʹ��"+name()+"��\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�ö�������צ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch(query("character", me) )
        {
        case "�ĺ�����":
                msg = HIR "$N" HIR "�����Ц����ָ΢΢������ٿ�ĳ�$n"
                      HIR "ͷ��ץ�¡�\n" NOR;
                break;

        case "���ռ�թ":
                msg = HIR "$N" HIR "��Ц��������ָ΢΢������צ������$n"
                      HIR "ͷ��ץ�¡�\n" NOR;
                break;

        case "��������":
                msg = HIR "$N" HIR "������������ָ΢΢������צ��������$n"
                      HIR "ͷ��ץ�¡�\n" NOR;
                break;

        default:
                msg = HIR "$N" HIR "��ָ΢΢������צ���벻�������$n"
                      HIR "ͷ��ץ�¡�\n" NOR;
                break;
        }

        addn("neili", -100, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        damage = damage_power(me, "claw");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage,115,
                                           HIR "$p" HIR "��æ��ͷ��Ȼ��$N" HIR
                                           "�������úÿ죬������$p" HIR "��ͷ��"
                                           "��ʱ��Ѫ���졣\n" NOR);
        } else
        {
                addn("neili", -150, me);
                me->start_busy(3);
                msg += HIC "$p" HIC "���в��ã���æ��ͷ������$N"
                       HIC "�ֱ��������죬��Ȼ������Ѹ���ޱȵ�ץ��$p��\n" NOR;
                dp = defense_power(target, "dodge");

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                                   HIR "$n" HIR "�����ϵ�$N" HIR
                                                   "������˱��У�������������ͷ��$P"
                                                   HIR "ץ�˸���Ѫ���졣\n" NOR);
                } else
                        msg += CYN "$n" CYN "�������룬���м�ƮȻ���ˣ���$P"
                               CYN "��һ���޹�������\n" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}
