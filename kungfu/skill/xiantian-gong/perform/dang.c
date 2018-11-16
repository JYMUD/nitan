// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "�����Ƶ�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, cloth;
        int ap, dp, damage;
        string wp;
        string cl;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("������칦��Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("��û��׼��ʹ�����칦������ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "ֻ��$N" HIW "˫Ŀ�������䣬˫�ƶ�Ȼһ�񣬽����ڻ����"
              "���������ƹ��Ƴ�����ʱ��Х\n�����������쾢��������������"
              "���˰�ӿ��$n" HIW "��\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "����$n" HIR "΢΢һ㶼䣬$N" HIR "���Ȼ"
                               "���壬$p" HIR "һ��������ȫ�����羡�����ѡ�\n"
                               NOR "( $n" RED "���˹��أ��Ѿ�������в�����"
                               "ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -400, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                                   damage, 90, HIR "$N" HIR "��"
                                                   "���ʱ�߽���$n" HIR "�Ļ�"
                                                   "��������$p" HIR "��Ԫ����"
                                                   "�������������Ѫ��\n" NOR);

                        if( objectp(weapon=query_temp("weapon", target) )
                            && query("stable", weapon)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                wp = weapon->name();
                                msg += HIW "ֻ�����ϡ���һ�����죬$n" HIW "��"
                                       "�е�" + wp + HIW "��$N" HIW "��������"
                                       "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, weapon);
                                weapon->move(environment(target));
                        } else
                        if( objectp(cloth=query_temp("armor/armor", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "ֻ�����䡱��һ�����죬$n" HIW "��"
                                       "�ŵ�" + cl + HIW "��$N" HIW "��������"
                                       "��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        } else

                        if( objectp(cloth=query_temp("armor/cloth", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "ֻ�����䡱��һ�����죬$n" HIW "��"
                                       "�ŵ�" + cl + HIW "��$N" HIW "��������"
                                       "��Ӧ�����飬����һ�����Ƭ��\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        }
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "����$p" CYN "֪��$P" CYN "���е���"
                       "��������Ӳ�ӣ�����бԾ��ܿ�����\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}