#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "��������" NOR; }

int unconcious_me(object me);

int perform(object me, object target)
{
        object du;
        int damage;
        string msg, msg1;
        int ap, dp, lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʩչ" + name() + "��\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 220)
                return notify_fail("��ĳ����ƻ�򲻹���\n");

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("��Ļ���������򲻹���\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 220)
                return notify_fail("��Ļ����󷨻�򲻹���\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬�޷�������ʩչ" + name() + "��\n");

        if( query("neili", me)<3000 )
                return notify_fail("��������Ϣ���㣬�޷�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("�㻹û��׼�������ƣ��޷�ʩչ" + name() + "��\n");

        /*
        if( !query_temp("powerup", me) )
                return notify_fail("����뽫ȫ���������������ʩչ" + name() + "��\n");

        if( !objectp(du=query_temp("handing", me)) && userp(me) )
                return notify_fail("������Ҫ����(hand)һЩ��ҩ��Ϊ���ӡ�\n");

        if( query("poison", objectp(du) && !mapp(du)) )
                return notify_fail(du->name() + "�ֲ��Ƕ�ҩ���޷���������棿\n");
        */

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "˫ĿѪ�죬ͷ��ɢ�ң��͵����췢��һ����Х��\n\n"
              "$N" HIR "����һ�ᣬ���Լ�������һҧ��������������"
              "���������ʱֻ��������Ѫ���������ȳ��ޱȣ��漴��\n"
              "��$N" HIR "����������ž����һ���죬˫��˳�������"
              "Ѫ��һ�ƣ�ɲ�Ǽ�һ�������ߵ��涾��ǽ�εض��𣬴�\n"
              "����ɽ����֮����$n" HIR "ӿȥ��\n" NOR;
        me->start_busy(2 + random(2));
        addn("neili", -1000, me);

        lvl = me->query_skill("chousui-zhang", 1);
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);

        /*
        if (lvl / 2 + random(lvl) < target->query_skill("force", 1))
        {
                if( query("max_neili", me)+random(query("max_neili", me))<
                    query("max_neili", target)*18/10 )
                {
                        msg += WHT "$n" WHT "��״��æ����������˫����"
                                "���Ƴ����Ʒ����ȣ�ǿ���������ʱ������"
                                "�εõ�ת����Ȼ��ͷ��$N" WHT "��ȥ��\n\n" NOR;
                        msg += HIR "$N" HIR "һ����Ц����̾һ������ǰһ�ڣ������˵��ϡ�\n\n" NOR;
                        //me->addn("max_neili", -random(50));
                        me->receive_damage("qi", 1, target);

                        remove_call_out("unconcious_me");
                        call_out("unconcious_me", 1, me);

                }
        } else
        {
        */
                ap = attack_power(me, "strike") +
                     me->query_skill("poison", 1);
                dp = defense_power(target, "dodge") +
                     target->query_skill("force", 1)/2;

                if (ap + random(ap) < dp)
                {
                        msg += CYN "$n" CYN "���Ʋ����æ��Ų���Σ��ܿ���$N" CYN "�Ĺ�����\n" NOR;
                        // me->addn("max_neili", -random(50));
                        if (! target->is_busy())
                                target->start_busy(3);
                } else
                {
                        msg1 = HIR "$n" HIR "��������������ӿ����ֻ����ǰһƬͨ�죬"
                               "�ѱ�������ˣ�����ϯ��ȫ������ͷ��Ҫ����һ�㡣\n" NOR;
                        // me->addn("max_neili", -random(50));
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90, msg1);

                        target->affect_by("fire_poison",
                                       (["level":query("jiali", me)*6+random(query("jiali", me)*4),
                                          "id":query("id", me),
                                          "duration" : lvl / 20 + random(lvl) ]));

                        target->receive_damage("qi", damage * 2);
                        target->receive_damage("jing", damage);
                        if (! target->is_busy())
                                target->start_busy(5);
                }
        /*
        }

        if (objectp(du)) destruct(du);
        */
        message_vision(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}

int unconcious_me(object me)
{
        if (! objectp(me))
              return 1;

        if (living(me))
              me->unconcious();

        return 1;
}