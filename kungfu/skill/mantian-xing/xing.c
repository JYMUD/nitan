#include <ansi.h>
#include <combat.h>

#define XING "��" HIR "������" NOR "��"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        mixed my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( playerp(me) && !query("can_perform/mantian-xing/xing", me) )
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" XING "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XING "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("����������û�����Ű���������ʩչ" XING "��\n");

        if (weapon->query_amount() < 15)
                return notify_fail("����Ҫ��ʮ��ö��������ʩչ" XING "��\n");

        if ((skill = me->query_skill("mantian-xing", 1)) < 80)
                return notify_fail("��������ǲ�����죬����ʩչ" XING "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" XING "��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ���㣬����ʩչ" XING "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������㣬����ʩչ" XING "��\n");

        if( query_temp("feixing", target) )
                return notify_fail("�Է��Ѿ�������ľ��У������Ƿ���һ�����Ͽ�����ɣ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -100, me);
        weapon->add_amount(-15);

        msg = HIR "$N" HIR "��ط���Ծ��ʮָ���ţ�ʩ���������ǡ���"
              "����" + weapon->name() + HIR "������������\n��ʱ�ƿ���"
              "���죬" + weapon->name() + HIR "����ͬ���Ƿ�׹һ�㣬����"
              "$n" HIR "������Ѩ��\n" NOR;

        my_exp=COMBAT_D->valid_power(query("combat_exp", me))/100;
        ob_exp=COMBAT_D->valid_power(query("combat_exp", target))/100;

        me->want_kill(target);
        if (my_exp / 2 + random(my_exp * 3 / 2) > ob_exp)
        {
                if (target->query_skill("parry") < me->query_skill("throwing"))
                {
                        n = 2 + random(2);
                        if (random(my_exp) > ob_exp) n += 1 + random(2);
                        if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                        if (random(my_exp / 4) > ob_exp) n += 1 + random(2);

                        msg += HIR "���$n" HIR "һ���ҽУ�ͬʱ����$P" HIR +
                               chinese_number(n)+query("base_unit", weapon)+
                               weapon->name() + HIR "��ֱ������������Ŀ����"
                               "�\n" NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               query("jiali", me)+100+n*10);
                        }

                        set_temp("feixing", 1, target);
                        addn_temp("apply/attack", -70, target);
                        addn_temp("apply/dodge", -70, target);
                        addn_temp("apply/parry", -20, target);
                        target->receive_damage("qi", 150, me);
                        target->receive_wound("qi", 50, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);

                        tell_object(target, RED "������ҪѨ�ܵ���������ȫ��"
                                            "�������᲻�ϰ��������\n" NOR);
                        tell_object(me, HIC "����֪�ղ������Ѵ��жԷ�Ҫ������"
                                            "��������Ц��\n" NOR);

                        target->kill_ob(me);
                        call_out("back", 2 + random(skill / 15), target);
                } else
                {
                        msg += HIR "$n" HIR "�������ǣ�˫�ֻ�Ȧ�������裬��Ū"
                               "����Ҫ������ɱ�ţ��ɻ������˵����ˡ�\n" NOR;

                        target->receive_damage("qi", 100);
                        target->receive_wound("qi", 40);

                        p=query("qi", target)*100/query("max_qi", target);
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);

                        tell_object(target, RED "��ֻ��ȫ����һ���ʹ��֪��"
                                            "�Լ��䱻���У���ȴ�Ǳܿ���ҪѨ��"
                                            "\n" NOR);
                        target->kill_ob(me);
                        me->start_busy(1 + random(2));
                }
        } else
        {
                 msg += CYN "����$n" CYN "С����Ų���ò����ױܿ���"
                        CYN "$N" CYN "����ǵصĹ�����\n" NOR;
                 me->start_busy(3);
                 message_combatd(msg, me, target);
        }
        return 1;
}

void back(object target)
{
        if (objectp(target))
        {
                addn_temp("apply/attack", 70, target);
                addn_temp("apply/dodge", 70, target);
                addn_temp("apply/parry", 20, target);
                tell_object(target, HIY "���������������һ˿˿�Ļָ��ˡ�\n" NOR);
                delete_temp("feixing", target);
        }
}