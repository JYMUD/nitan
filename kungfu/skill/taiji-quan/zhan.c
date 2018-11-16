// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "ճ�־�" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("���̫��ȭ�ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("��û�м���̫��ȭ������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��������˫�ֳ�Բ�λ�������"
              "����̫��ȭ��Բת���ϡ����ֵľ��⡣ֻ\n��$N"
              HIW "�漴ƽȦ����Ȧ����Ȧ��бȦ��һ������һ"
              "����һ����̫��ԲȦ��ʱ��\n��$n" HIW "����"
              "�˷���\n" NOR;

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "��ʱ�㱻�׵õ���ײײ����"
                                           "�����������㲻�ȣ������оƻ��ԡ�\n"
                                           NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(3 + ap / 80);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ͼ������Ĳ��У�û¶�������"
                       "��\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}