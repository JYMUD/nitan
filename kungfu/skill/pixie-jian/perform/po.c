#include <ansi.h>
#include <combat.h>

string name() { return HIW "��Ԫ����" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", });

int perform(object me, object target)
{
        int damage;
        string msg, name;
        object weapon;
        int lvl, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);

        if (! objectp(weapon))
                return notify_fail("��û��ʹ�ñ������޷�ʩչ" + name() + "��\n");

        if( weapon && query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "pin" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("pixie-jian", 1) < 180)
                return notify_fail("��ı�а����������죬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2600 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ" + name() + "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        /*
        if( query_temp("no_perform", target) )
                return notify_fail("�Է������Ѿ��޷������������ŵ������ɡ�\n");
        */

        if( query_temp("weapon", me) )
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIW "$N" HIW "һ����ߣ�˫����͸��һ˿������" + name +
              HIW "����ǧ�ٸ����ƣ��ó�������ɫ�ʣ�\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        dp = defense_power(target, "parry") +
             target->query_skill("dodge");

        if (ap / 2 + random(ap*2) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, random(15) + 100,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "��֮��ȫȻ�޷��мܣ���æ"
                       "���������ߣ��㿪����һ�С�\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_conditon("no_perform")) return "";
        target->apply_condition("no_perform", 30);
        remove_call_out("poyuan_end");
        call_out("poyuan_end", 10 + random(ap / 30), me, target);
        return HIR "$n" HIR "ֻ����ǰ��âһ���������漴ȫ��һ��"
               "��ʹ������Ѫ�������������\n$p��Ȼ��һ��������"
               "�����������������ƻ�ɢһ�㣬ȫȻ�޷����ơ�\n" NOR;
}

void poyuan_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->delete_condition("no_perform");
        }
        return;
}
