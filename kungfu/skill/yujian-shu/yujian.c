#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("jueji/sword/feisheng", me) )
                return notify_fail( WHT "���޷�����ʹ�á�����������������\n" NOR );

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("sword", 1) < 400)
                return notify_fail("��Ľ����дﲻ���������������ľ��硣\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ�����дﲻ���������������ľ��硣\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ̫�����޷���������������\n");

        if( query("neili", me)<1500 )
                return notify_fail("����������������\n");

        msg = HIW "\n$N" HIW "һ���޺ȣ���������ֻ���ƿ���һ�죬����"
             + weapon->name() + HIW "Я����������֮����$n" HIW "���ȹ�"
              "\n������������������������\n" NOR;

        damage = (int)me->query_skill("sword", 1) +
                 (int)me->query_skill("force", 1) +
                 (int)me->query_skill("parry", 1) +
                 (int)me->query_skill("martial-cognize", 1) / 2;

        damage = damage / 4 + random(damage / 4);

        me->start_busy(2 + random(4));
        set_temp("jueji/sword/feisheng", 1, me);
        call_out("end_perform2", 600, me, weapon, damage); 

        if (random(me->query_skill("force")) > target->query_skill("force") * 3 / 5)
        {
                addn("neili", -1000, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "$n" HIR "����$N" HIR "������ǧ����һ��������"
                                           "֪����мܣ���ʱ�����ش���\n" NOR);
                message_vision(msg, me, target);
                remove_call_out("perform2");
                call_out("perform2", 2, me);
                return 1;
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ��бԾ�ܿ���\n" NOR;
                message_vision(msg, me, target);
                addn("neili", -100, me);
                remove_call_out("perform2");
                call_out("perform2", 2, me, target);
                return 1;
        }
        message_combatd(msg, me, target);

        return 1;
}

int perform2(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
        {
                write(HIW "����ת����������һ����Х�����ڿ���������һȦ����"
                      "�ɻ���������С�\n" NOR);
                call_out("end_perform2", 1, me, weapon, damage); 
                return 1;
        }

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
        {
                write(HIW "��ֹͣʹ�á�����������������\n" NOR);
                call_out("end_perform2", 30, me, weapon, damage); 
                return 1;
        }

        if( query("neili", me)<150 )
        {
                write(HIW "�㽣����;����������Ϣ���㣬ֻ��ֹͣ������\n" NOR);
                call_out("end_perform2", 30, me, weapon, damage); 
                return 1;
        }

        msg = HIW "\n$N" HIW "�������������ɣ�������������תǧ�䣬һ����"
                  "�����������������\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("force", 1) +
                         (int)me->query_skill("parry", 1) +
                         (int)me->query_skill("martial-cognize", 1) / 2;

                damage = damage / 5 + random(damage / 5);

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "ֻ����������һ����" HIW "���ν���" NOR +
                                           HIR "����$n" HIR "����̳�һ��Ѫ��������Ѫ��"
                                           "���������\n" NOR);
                message_vision(msg, me, target);
                remove_call_out("perform2");
                call_out("perform2", 4, me);
                return 1;
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ��бԾ�ܿ���\n" NOR;
                message_vision(msg, me, target);
                addn("neili", -100, me);
                remove_call_out("perform2");
                call_out("perform2", 4, me);
                return 1;
        }
        message_combatd(msg, me, target);

        return 1;
}

void end_perform2(object me)
{
        if (! me) return;
        if( !query_temp("jueji/sword/feisheng", me))return ;
        delete_temp("jueji/sword/feisheng", me);
        tell_object(me, HIW "\n�㾭��������Ϣ���ֿ��Լ���ʹ�á�"
                        "�����������ˡ�\n" NOR); 
}
