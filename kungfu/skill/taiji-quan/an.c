// an.c ̫��ȭ�������־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "���־�"; }

int perform(object me, object target)
{
        int damage, acter, ap, dp, taoism;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á����־�����\n");

        if ((int)me->query_skill("taiji-quan", 1) < 200)
                return notify_fail("���̫��ȭ�����⻹����������ʹ�á����־�����\n");

        if( query("neili", me)<300 )
                return notify_fail("����������̫��������ʹ�á����־�����\n");

        msg = HIG "$N" HIG "˫ȭ���»Ӷ���ʹ��̫��ȭ�����־�����$n"
              HIG "�е�һ��ǿ��ľ�����ͷ��ѹ�䡣\n" NOR;

        addn("neili", -200, me);

        dp = (defense_power(target, "parry") + target->query_skill("force", 1)) / 3;

        if( query("character", me) == "��������" ||
            query("character", me) == "������˫" ||
            query("character", me) == "������" )
               acter = 3;
        else
               acter = 4;

        taoism = me->query_skill("taoism", 1);

        ap = (attack_power(me, "cuff") + me->query_skill("taiji-shengong", 1) +
              taoism) / acter;

        if (target->is_bad())   ap += ap / 2;

        if (random(ap) > dp / 2 || !living(target))
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1+random(3));

                damage = damage_power(me, "cuff");

                if( query("shen", me)/800<5000 )
                     damage += 5000;
                else
                     damage+=query("shen", me)/800;

                damage+=query("jiali", me)*2;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 70,
                                           HIY "$n" HIY "�Ǹк��������������ѵ���"
                                           HIY "��ͷһ�𣬿�������"HIR"��Ѫ"HIY"��\n"
                                           ":����@?");
        } else
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "�����ڹ����۾����⣬ͦ��Ӳ����$P"
                       HIY "��һ�У����顱��һ�����죬˫����������������\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
