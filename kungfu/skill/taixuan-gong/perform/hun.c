// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define HUN "��" HIW "����һ��" NOR "��"

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/taixuan-gong/hun", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUN "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("taixuan-gong", 1) < 120)
                return notify_fail("���̫������������죬����ʩչ" HUN "��\n");

        if (me->query_skill_mapped("unarmed") != "taixuan-gong")
                return notify_fail("������û�м���̫����Ϊȭ�ţ�����ʩչ" HUN "��\n");

        if (me->query_skill_mapped("force") != "taixuan-gong")
                return notify_fail("������û�м���̫����Ϊ�ڹ�������ʩչ" HUN "��\n");

        if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                return notify_fail("������û��׼��ʹ��̫����������ʩչ" HUN "��\n");

        if( query("neili", me)<600 )
                return notify_fail("�����������������ʩչ" HUN "��\n");
 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "\n$N" HIG "˫�ֺ�ʮ��˫Ŀ΢�գ�̫���������ĵ�ӿ������Ȼ�䣬$N"
              HIG "˫����ǰ�Ƴ���һ��ǿ��������Ϯ��$n " HIG "��\n" NOR;
 
        ap=attack_power(me,"unarmed")+query("con", me)*10;

        dp=defense_power(target,"force")+query("con", target)*10;

        addn("neili", -150, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "Ȼ��$n" HIY "ȫ���ֵ������ڽ�$N" HIY
                       "������������ס��\n" NOR;
                me->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(2);
                damage = defense_power(me, "unarmed");
                // target->addn("neili", -(me->query_skill("taixuan-gong", 1) + 
                            // random(me->query_skill("taixuan-gong", 1))), me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                           (: final, me, target, damage :));

        }
        message_combatd(sort_msg(msg), me, target);
        return 1;
}


string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 3, me);
        target->busy(1);
        return  HIR "$n" HIR "��æ������ˣ�����������"
                "�ø��죬ֻ��$p" HIR "һ���ҽУ�һ����"
                "���Ѿ�͸���������Ѫ�ɽ���$n" HIR "��"
                "��������ɢ���޷����С�\n" NOR;
}
