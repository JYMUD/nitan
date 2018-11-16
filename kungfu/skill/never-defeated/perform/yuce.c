// yuce.c

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int skill, i;
        int n, damage;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���߾�ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("���������в�û�����Ű�������ôʩչ���߾���\n");

        if ((skill = me->query_skill("never-defeated", 1)) < 100)
                return notify_fail("��Ĳ����񹦻�򲻹�������ʩչ���߾���\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������ˡ�\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -120, me);
        weapon->add_amount(-1);

        msg = HIC "$N" HIC "��ָһ��һ����ֻ����Х�ƿ���������������һ" +
             query("base_unit", weapon)+weapon->name()+HIC"��������"+
             "����$n" HIC "��\n" NOR;

        me->start_busy(1);
        my_exp = attack_power(me, "throwing");
        ob_exp = defense_power(target, "parry");
        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                msg += HIR + "ֻ����" + weapon->name() + HIR "ȥ��ǡ��������磡$n"
                       HIR + "�������ܣ������˸����У��ҽ�һ"
                       "�������˼�����\n" NOR;
                       
                damage = damage_power(me, "throwing") * 3 / 2;
                target->receive_wound("qi", damage, me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               query("jiali", me)+150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "����$p" CYN "��æһ���������$P" HIG "������" +
                       weapon->name() + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}