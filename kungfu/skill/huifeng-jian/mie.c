// mie.c  �ط�����������𽣡�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("��û�м����ط�����������޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 120)
                return notify_fail("��Ļط��������������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻹����޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
               return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���г�����âԾ�������Ⱪ�����ó�������ɫ�ʣ����⽥"
              "���ƽ�$n" HIR "��\n$n" HIR "�������콣�⣬�����Ծ������ֻ��һɲ"
              "��$N" HIR "���콣Ӱ��Ϊһ��ֱ\n��$n" HIR "ǰ�أ�������ף�ֻ��һ"
              "����\n" NOR;


        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "ȫȻ�޷���ܣ�" + weapon->name() +
                                           HIR "�˶�����������$p" HIR "���ؿڣ���Ѫ��ʱ�ɽ�"
                                           "������\n" NOR);
                addn("neili", -150, me);
        } else
        {
                me->start_busy(3);
                msg += YEL "����$p" YEL "����һЦ��������ת����"
                       "����ָ��������$P" YEL "�Ľ��ϣ�" + weapon->name() +
                       YEL "��$p" YEL "��໮�����о����ա�\n"NOR;
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
