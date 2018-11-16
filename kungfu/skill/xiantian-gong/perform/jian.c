#include <ansi.h>
#include <combat.h>

string name() { return HIW "���칦" HIR "Ǭ��" HIY "����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, i, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 280)
                return notify_fail("������칦��Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("sun-finger", 1) < 280)
                return notify_fail("��һ��ָ��������죬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("��û�м���һ��ָΪָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong"
           && me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("��û��׼�����칦��һ��ָ������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "��ʱֻ��$N" HIY "����" HIW "��������" HIY "����Ϊ" HIR
              "�����ھ�" HIY "����ָ�⣬��һ��ָ���ַ�����$n" HIY "ȫ����"
              "��ҪѨ��\n" NOR;

        ap = attack_power(me, "force") + me->query_skill("finger") +
             me->query_skill("unarmed");
        dp = defense_power(target, "force") + target->query_skill("dodge") +
             target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                damage = damage_power(me, "finger");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 500,
                                           HIR "$n" HIR "ֻ��ȫ��һ�ȣ�$P" HIR "��"
                                           HIW "���칦" HIR "Ǭ��" HIY "����" HIR
                                           "����ʱ������룬�������ú�¯�����һ��"
                                           "��Ѫ��\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "��ָ������ӿ������"
                       "�����мܣ�����������Ծ������\n" NOR;
                message_combatd(msg, me, target);
        }

        msg = HIR "������$N" HIR "ʮָ�׷ɣ����������������ν�����$n" HIR "�����"
              "���Ա����������֡�\n"NOR;
        message_combatd(msg, me, target);

        addn_temp("apply/attack", ap/10, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -ap/10, me);
        addn("neili", -600, me);
        me->start_busy(1 + random(3));
        return 1;
}
