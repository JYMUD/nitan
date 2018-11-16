#include <ansi.h>
#include <combat.h>

string name() { return HIR "�ƻ�" NOR; }

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

           if( !objectp(weapon=query_temp("handing", me)) || 
  (query("id", weapon) != "tang hua" &&
           query("skill_type", weapon) != "throwing") )
   return notify_fail("����������û�����Ű����ƻ�������ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 180)
                return notify_fail("������Ű���������죬����ʩչ" + name() + "��\n");

/*
        if( query("tangmen/yanli", me)<80 )
                return notify_fail("�������̫���ˣ�Ŀ�겻��ȷ���޷�ʩչ" + name() + "��\n");
*/

        if ((int)me->query_skill("boyun-suowu", 1) < 180)
                return notify_fail("��Ĳ�����������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -100, me);

        msg = HIR "\n$N" HIR "����ͻȻ����һ֧�����������ޣ�$n" HIR "�����е���ˣ�\n$N" HIR "��$n" HIR "һЦ��һ������$n"HIR "��ȥ��\n" +
              HIG "ֻ���ǻ����ˣ�������棬���뻨�����ɷ�Ǻÿ���\n" NOR;

        ap = attack_power(me, "throwing") * 2;
        dp = defense_power(target, "parry") + defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1) * 10;

        message_combatd(msg, me, target);
        tell_object(target, HIC "\n�㼱æ�����ȥ�ӣ���ͻ�أ��㷢�����죬����һ������������һԾ��\n" NOR);
//        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)
        if (ap / 2 + random(ap) > dp)
        {
                if( query("reborn/times", target) || query("id", weapon) != "tang hua" )
                {
                        string pmsg;

                        weapon->add_amount(-1);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        msg = HIR "���$p" HIR "һ���Һ���������$P" HIR "������һ" +
                                query("base_unit", weapon)+weapon->name()+HIR"��\n"NOR;

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+120);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }

                msg = HIR"�ǻ�Խ��Խ�ޣ�$n" HIR "��֪�������ѳ����ˣ�����һ��,΢Ц�ŵ����ˣ��ǻ�Ҳл�ˡ�\n" NOR;
                tell_object(target, HIR "\n�㿴���ǻ���������һ��������\n���������������ժ��������"
                                        "�ǻ�������Խ��Խ���ˣ���ϡ����ǵ���������һ��СС�ġ��ơ��֡�\n" NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                weapon->move(target);

                message_combatd(msg, me, target);
                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
                me->start_busy(2);
        } else
        {
                if( query("id", weapon) == "tang hua" )
                        tell_object(target, HIR "�������ƻ��������е��ƻ���������ȫ��������������ӵĸ�����\n" NOR);
                msg = HIR "$n " HIR "����Ʈ�����ǻ����ն�����ֻ������һ�����죬�ǻ�л�ˣ���������ڵ����ϡ�\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}

