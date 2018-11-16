// This program is a part of NT MudLIB
// binghuo.c ���溮����--

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���������"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
        ||  !me->is_fighting(target))
                return notify_fail("����������졹ֻ����ս����ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ֻ�п��ֲ���ʩչ����������졹��\n");

        if( (int)me->query_skill("fireice-strike", 1) < 150 )
                return notify_fail("������溮���ƹ��򻹲�����죬����ʹ�á���������졹��\n");

        if(me->query_skill("yunv-xinfa", 1) < 120)
                return notify_fail("�������ڵ���Ů�ķ���ʹ��������������졹��\n");

        if ( me->query_skill_mapped("strike") != "fireice-strike" )
                return notify_fail("�������޷�ʹ�á���������졹���й�����\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ̫��������ʹ�á���������졹��\n");

        if( query("neili", me)<800 )
                return notify_fail("�������������\n");

        if( !living(target) )
                return notify_fail("�Է��Ѿ������ˣ��ò���ʹ��ô�������ɡ�\n");

        if ("jiuyang-shengong" == target->query_skill_mapped("force"))
        {
                msg = HIR"$N" HIR"������������͸��⣬һ�ɳ���������" HIR"$n" HIR"ӭ��������\n" NOR;

                dp = target->query_skill("force",1) / 4;

                if (random(me->query_skill("force",1)) > dp)
                {
                       addn("neili", -100, me);
                       msg += HIY "$nһ��֮�£����˾����������ֿ�������ɫת�˼�ת����Ȼ����\n"NOR;
                }  else
                {
                       me->start_busy(3);
                       addn("neili", -200, me);
                       msg += HIW"$p" HIW"���һ�����������ã������˾���������\n"
                              HIR"$N" HIR"��������������Ѫ�����ڣ�����������\n"NOR;
                }
        }  else
        {
                msg = HIR "\n$N" HIR "������������͸��⣬һ�ɳ�������ֱϮ" HIR "$n" HIR "�ؿڣ�\n"NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");
                if (ap / 2 + random(ap) > dp)
                {
                        //me->start_busy(1);
                        if( !target->is_busy() )
                                target->start_busy(1);

                        addn("neili", -300, me);
                        damage = damage_power(me, "strike");
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                HIR "$n" HIR" ��ʱ�����ؿ��类���գ�һ���������Լ̻أ�!!\n"NOR);

                        if( me->query_skill("fireice-strike", 1) > 150 )
                                call_out("perform2", 0, me, target);
                }
                else
                {
                        me->start_busy(3);
                        addn("neili", -100, me);
                        msg += HIW"����$pһ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n"NOR;
                }
        }
        message_combatd(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if (!me || !target || environment(me) != environment(target)) return 0;
        if(!living(target))
                return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( query("neili", me)<600 )
                return notify_fail("���Ҫ�ٳ��ڶ��ƣ�ȴ�����Լ������������ˣ�\n");

        msg = HIB "\n����" HIB "$N" HIB "��ӳ����֣����ľ��ǰ���������������Ƕ���" HIB "$n" HIB "�Ĺ�ȥ!\n"NOR;
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                HIW  "���һ�ƻ��У�" HIW "$n" HIW "ֻ����ȫ������ͨ�����ⶳ�ᣬ��ɫһ�±�ף�\n"NOR);
        }
        else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += HIY "\n$p" HIY "�ۿ��������ˣ�����������˳�����˿�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
