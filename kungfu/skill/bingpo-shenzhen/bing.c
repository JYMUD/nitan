#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "������" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, n;
        int ap, dp, p, damage;
        string msg, pmsg;
        object weapon;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("����������û�����Ű���������ʩչ" + name() + "��\n");

        if (weapon->query_amount() < 1)
                return notify_fail("������û���룬�޷�ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("bingpo-shenzhen", 1)) < 120)
                return notify_fail("��ı������벻����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if( query_temp("bingpo", target) )
                return notify_fail("�Է��Ѿ�������ľ��У������Ƿ���һ"
                                   "�����Ͽ�����ɣ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -120, me);
        weapon->add_amount(-1);

        msg = HIY "ֻ��$N" HIY "����΢��������һת��һ�С�" HIW "������"
              HIY"����������" + weapon->name() + HIY "�͵������ɲ��\n"
              "�䣬�������죬" + weapon->name() + HIY "��ͬһ�����ǻ�����"
              "Ϯ��$n��\n" NOR;

        ap = attack_power(me, "throwing");
        dp = defense_power(target, "dodge");
        level = skill;

        if (ap + random(ap / 2) > dp)
        {
                damage = damage_power(me, "throwing");
                if (target->query_skill("parry") < me->query_skill("throwing"))
                {

                        msg += HIR "ֻ��$n" HIR "�ҽ�һ����" + weapon->name() + HIR
                               "�Ѿ�����Ҫ����ֻ���˿ڴ�͸�������⣬�پ�ȫ����"
                               "��������\n"NOR;

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/ 3, me);
                        set_temp("bingpo", 1, target);
                        addn_temp("apply/attack", -level/5, target);
                        addn_temp("apply/dodge", -level/5, target);
                        addn_temp("apply/parry", -level/10, target);
                        target->set_weak(3, 0);

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+180);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                 msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        message_combatd(msg, me, target);

                        tell_object(target, RED "������ҪѨ�ܵ���������ȫ����"
                                            "���᲻�ϰ��������\n" NOR);
                        tell_object(me, HIC "����֪�ղ������Ѵ��жԷ�Ҫ��������������Ц��\n" NOR);
                        call_out("back", 2 + random(skill / 15), target, level);
                } else
                {
                        msg += HIR "$n" HIR "�ۼ�����Ϯ�����������������"
                               "Ȼ����һ�����ˡ�\n" NOR, me, target;

                        target->receive_damage("qi", damage/2);
                        target->receive_wound("qi", damage/4);
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)/2);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        message_combatd(msg, me, target);

                        tell_object(target, RED "��ֻ��ȫ����һ���ʹ��֪���Լ�"
                                            "�䱻���У���ȴ�Ǳܿ���Ҫ����\n" NOR);
                        me->start_busy(1 + random(2));
                }
        } else
        {        msg += CYN "����$n" CYN "�����ɣ�С�����ܣ��ò����ױܿ���"
                                 CYN "$N" CYN "Ѹ�����Ĺ�����\n" NOR;
                 message_combatd(msg, me, target);
                 me->start_busy(3);
        }
        return 1;
}

void back(object target, int level)
{
        if (objectp(target))
        {
                addn_temp("apply/attack", level/5, target);
                addn_temp("apply/dodge", level/5, target);
                addn_temp("apply/parry", level/10, target);
                // tell_object(target, HIY "���������������һ˿˿�Ļָ��ˡ�\n" NOR);
                delete_temp("bingpo", target);
        }
}
