// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "����һ��" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("��������Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<600 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "Ĭ���ڹ���ʩչ��" + name() + HIC "��ȫ����ת��������"
              "Խ��Խ�죬��\n����һ�����磬��Ȼ�䣬$N" HIC "�Ѿ�������"
              "�÷�����" HIC "$n��\n"NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                           HIR "$p" HIR "ֻ��һ������Ӱ�ж�Ȼ�ֳ�$P"
                                           HIR "��˫ȭ��������������ܣ������ػ��У�\n��"
                                           "���������ڲ��ݣ�������Ѫ����������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ��û"
                       "���ܵ��Ի�������һ�ߡ�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
