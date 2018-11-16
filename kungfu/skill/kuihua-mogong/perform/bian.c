#include <ansi.h>
#include <combat.h>

#define BIAN "��" HIG "�ޱ��޼�" NOR "��"

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
                return notify_fail(BIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("�������õĲ��ǽ�����ôʩ"
                                           "չ" BIAN "��\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ�"
                                           "��ħ�������ʩչ" BIAN "��\n");
        }

        if ((int)me->query_skill("kuihua-mogong", 1) < 260)
                return notify_fail("��Ŀ���ħ��������죬����ʩչ" BIAN "��\n");

        if( query("max_neili", me)<3700 )
                return notify_fail("���������Ϊ���㣬����ʩչ" BIAN "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" BIAN "��\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("��û�м�������ħ��Ϊ�����ڹ�������ʩչ" BIAN "��\n");
                
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" BIAN "��\n");

        if (! weapon && me->query_skill_prepared("finger") != "kuihua-mogong")
                return notify_fail("��û��׼��ʹ�ÿ���ħ��������ʩչ" BIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( query_temp("no_perform", target) )
                return notify_fail("�Է������Ѿ��޷������������ŵ������ɡ�\n");

        if( query_temp("weapon", me) )
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIR "$N" HIR "һ����Х��������Ȼ��ת������" + name +
              HIR "��ʱ������������������ǧ������룬�������$n" HIR "��\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
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
        int t = 3 + random(4);
        target->apply_condition("no_perform", t);
        call_out("bian_end", t, me, target);
        return HIR "$n" HIR "ֻ����ǰ���������������漴ȫ��һ��"
               "��ʹ������Ѫ�������������\n$p��Ȼ��һ��������"
               "�����������������ƻ�ɢһ�㣬ȫȻ�޷����ơ�\n" NOR;
}

void bian_end(object me, object target)
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
                target->clear_condition("no_perform");
        }
        return;
}