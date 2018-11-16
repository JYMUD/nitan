#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "�����" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon, weapon2;
        string w1, w2;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("����������ԣ��޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("��û�м������������壬����ʹ��" + name() + "��\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 140)
                return notify_fail("����������岻����죬��ʹ����" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<400 )
               return notify_fail("��������������������ʩչ" + name() + "��\n"NOR);

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        w1 = weapon->name();
        damage = damage_power(me, "whip");
        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = "\n" HIW "ֻ��$N" HIW "����" + w1
              + HIW "ĺ��һ�����ó�������Ӱ����"
              "ʱ�Ʒ�������" + w1 + HIW "Я��"
              "����֮��ɨ��$n" HIW "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "ֻ����Ӱ���أ��ۻ�����"
                                           "�������޷������ֵ���һ���Һ�����Ѫ��"
                                           "��������\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "�����磬"
                       "˿����Ϊ����Ī�����ʽ����"
                       "������ֵ������⿪����\n" NOR;
        }

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        msg += "\n" HIW "������$N" HIW "һ��"
               "���ȣ�" + w1 + HIW "�͵����"
               "һ����" + w1 + HIW "��ʱ����"
               "һ�����磬�Ѵ�$n" HIW "����"
               "Ϯ����\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��һ���ɣ�ͻȻ�е���"
                                           "һ��" HIR "�ι�֮ʹ���ѱ����д��Ѫ"
                                           "��ģ����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "һ����ߣ���Ԥ��$N"
                       CYN "�д�һ�ţ������������������"
                       "��񿪣�\n" NOR;
        }

        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg += "\n" HIW "$N" HIW "üͷ΢�壬��"
                       "������һ��ֻ����쬡���һ����"
                       "�ֹ���һ�У�" + w1 + HIW "����"
                       "�ǰ㵯��$n" HIW "�󲿣�\n" NOR;

                ap = attack_power(me, "whip");
                dp = defense_power(target, "force");

                if (ap / 2 + random(ap) > dp)
                {
                        w2 = weapon2->name();
                        msg += HIR "ֻ����������һ����" + w1 +
                               HIR "������$p" + w2 + HIR "�ϣ�"
                               "$p" HIR "����һ�飬" + w2 + HIR
                               "��Ҳ�óֲ�ס�����ֵ��ڵ��ϡ�\n"
                               NOR;
                        addn("neili", -50, me);
                        weapon2->unequip();
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "����$p" CYN "������$P" CYN
                               "����ͼ����æб���㿪��\n" NOR;
                        addn("neili", -30, me);
                }
        }
        me->start_busy(2 + random(4));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}