#include <ansi.h>
#include <combat.h>

#define HAI "��" HIG "�ຣ�ޱ�" NOR "��"

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
                return notify_fail(HAI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "staff" )
                        return notify_fail("�������õĲ����ȣ���ôʩչ" HAI "��\n");
        } else
        {
                if (me->query_skill_prepared("finger") != "bluesea-force")
                        return notify_fail("�㲢û��׼��ʹ����"
                                           "�����������ʩչ" HAI "��\n");
        }

        if ((int)me->query_skill("bluesea-force", 1) < 260)
                return notify_fail("����Ϻ�����������죬����ʩչ" HAI "��\n");

        if( query("max_neili", me)<3700 )
                return notify_fail("���������Ϊ���㣬����ʩչ" HAI "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" HAI "��\n");
                
        if (weapon && me->query_skill_mapped("staff") != "bluesea-force")
                return notify_fail("��û��׼��ʹ���Ϻ�����������ʩչ" HAI "��\n");

        if (! weapon && me->query_skill_prepared("finger") != "bluesea-force")
                return notify_fail("��û��׼��ʹ���Ϻ�����������ʩչ" HAI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        /*
        if (target->query_condition("no_exert"))
                return notify_fail("�Է������Ѿ��޷������������ŵ������ɡ�\n");
        */

        if( query_temp("weapon", me) )
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        msg = HIB "$N" HIB "����˫�ۣ����һ����һ�����˾��ŷ�ʯ����ΰ�Ϯ��$n" HIB "���Է�����δ��֮�ʣ������������졣\n"
              HIB "��$N" HIB "��" + name + HIB "�����������������Ϯ$n" HIB "������Ѩ������Ѩ������Ѩ������Ѩ����\n\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -500, me);
        } else
        {
                msg += CYN "$n" CYN "������һ�����ӷ���Ծ�����ɣ�"
                       "���Ҷ㿪����һ�С�\n" NOR;
                me->start_busy(3);
                addn("neili", -350, me);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_condition("no_exert")) return "";
        target->apply_condition("no_exert", 30);
        call_out("hai_end", 15 + random(ap / 20), me, target);
        return HIY "$n" HIY "ֻ����ǰ��ɳ��ʯ��Ŀ�����ӣ���������ҪѨ"
               "��ʹ������Ѫ�������������\n$p��Ȼ��һ��������"
               "�����õ���֮�ڿ������ȣ�ȫȻ�޷�������\n" NOR;
}

void bian_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}