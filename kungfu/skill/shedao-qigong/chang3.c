// ���ɷ����־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "���־�"; }
int perform(object me, object target)
{
        string msg;
        int neili, damage;
        int i;
        int ap, dp;

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ɷ����־�ֻ����ս���жԶ���ʹ�á�\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 100)
                return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ����־���\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if( query("neili", me)<500 )
                return notify_fail("���Ѿ���ƣ���ߣ����������ˡ�\n");

        if (me->query_skill_mapped("unarmed") != "shedao-qigong")
                return notify_fail("��û�н�����ȭ��"
                                   "����Ϊ�ߵ��湦, ����ʹ�á����־�����\n");

        //neili=query("max_neili", me);
        neili=query("neili", me);
        if( neili > query("max_neili", me)*2 )
                neili = query("max_neili", me) * 2;

        addn("neili", -(300+random(200)), me);
        //me->receive_damage("qi", 10);

        // me->start_busy(1 + random(5));

        message_combatd(HIY "$N" HIY "�������һ��������Ȼ���쳤Х����"
                        "����У�����������Ψ�Ҳ��ܣ�\n" NOR, me);

        if( neili/2+random(neili/2)<query("max_neili", target) )
                return notify_fail("���˵�������ѷ���㣬�˲��ˣ�\n");

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");

        msg = "";
        if (ap / 2 + random(ap) > dp)
        {
                damage=(neili-query("max_neili", target))/2;
                if (damage > 0)
                {
                        damage+= query("jiali", me);
                        target->receive_damage("jing", damage, me);
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("jing", damage / 4, me);
                        target->receive_wound("qi", damage / 4, me);
                        message_combatd(HIR "$N" HIR "ֻ������һ���ʹ��������"
                                "ð��������������������ǰ�趯��\n" NOR, target);
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "ֻ����$N" HIR "��������"
                                           "��ɽ����һ�㣬���ֵܵ������ۡ���һ���³�һ�����Ѫ��\n" NOR);
                }
        } else
                msg += CYN "$n" CYN "����һЦ��Ʈ��Ծ������$N"
                       CYN "��һ��ȫȻ��ա�\n" NOR;

        message_combatd(msg, me, target);
        me->start_busy(2);
        /*
        me->want_kill(target);
        me->kill_ob(target);
        */
        return 1;
}