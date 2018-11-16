// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, shd, jia, layer, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 300)
                return notify_fail("��������������Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("��û��׼��ʹ�����������������ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        layer = me->query_skill("longxiang-gong", 1) / 30;

        if (layer > 13) layer = 13;

        msg = HIY "$N" HIY "��ת�����������" + chinese_number(layer) + "��"
              "������˫ȭЯ�š�" HIR "ʮ��ʮ��" HIY "��֮����$n" HIY "����"
              "\n������ȭ����������������ﳾ�����������ھ�ѧ��" HIW "����"
              "��" HIY "����\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                if( query_temp("shield", target) )
                {
                        shd=query_temp("apply/armor", target);

                        addn_temp("apply/armor", -shd, target);
                        delete_temp("shield", target);

                        msg += HIW "$N" HIW "���ӿ������Ȼ���������ˣ���ʱ��$n"
                               HIW "�Ļ��������ݻٵõ�Ȼ�޴棡\n" NOR;
                }
                jia=query("jiali", me);
                damage = damage_power(me, "unarmed");
                damage+= jia;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                               HIR "$n" HIR "�������ܣ��ٱ�$N" HIR
                                               "˫ȭ�������У������������룬��"
                                               "������������\n" NOR);

                me->start_busy(5);
                addn("neili", -800, me);
        } else
        {
                me->start_busy(5);
                addn("neili", -500, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
