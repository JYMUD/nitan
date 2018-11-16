#include <ansi.h>
#include <combat.h>

#define HUAN "��" HIG "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/yinyang-ren/huan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade") )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" HUAN "��\n");

        if (me->query_skill("yinyang-ren", 1) < 180)
                return notify_fail("��������з���Ϊ����������ʩչ" HUAN "��\n");

        if (me->query_skill("dodge") < 220)
                return notify_fail("��������з���Ϊ����������ʩչ" HUAN "��\n");

        if( query("neili", me)<270 )
                return notify_fail("�����������������ʩչ" HUAN "��\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
            && me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("��û�м��������з�������ʩչ" HUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��Хһ��������" + weapon->name() + HIY "����"
              "�����⻷����Ȼ���â���ǣ���������$n" HIY "��\n" NOR;

        // ��������������sword��blade���ж�apֵ��
        if (me->query_skill_mapped("sword") == "yinyang-ren")
                ap = me->query_skill("sword");
        else 
                ap = me->query_skill("blade");

        dp = target->query_skill("dodge");
        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "���$n" HIR "��$N" HIR "���˸����ֲ�����$n"
                       HIR "��æ�мܣ����нпࡣ\n" NOR;
                count = ap / 12;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "�⼸�������ޱȣ�������"
                       "����ֻ�ÿ���мܡ�\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}