#include <ansi.h>
#include <combat.h>

string name() { return HIR "һָ������" NOR; }

inherit F_SSERVER;

string *xue_name = ({
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ",
"�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ", "����Ѩ", "����Ѩ", "���Ѩ",
"�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

int perform(object me, object target)
{
        int damage, lvl;
        string msg, wp;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("jingang-zhi", 1) < 200)
                return notify_fail("��������ָ������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("��û�м����������ָ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("��û��׼���������ָ������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        damage = damage_power(me, "finger");
        //lvl = (int)me->query_skill("jingang-zhi", 1);
        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        msg = HIW "ͻȻ��";

        msg += "$N" HIW "������ָ����" HIR "һָ������" HIW "���������ʱһ��"
               "����������ֱϮ$n" HIW "�ؿڣ�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

                target->start_busy(ap/100 + 2);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }


        me->start_busy(2 + random(3));
        addn("neili", -800, me);
        message_combatd(msg, me, target);

        return 1;
}
