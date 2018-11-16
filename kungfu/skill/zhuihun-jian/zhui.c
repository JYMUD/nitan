#include <ansi.h>
#include <combat.h>

#define ZHUI "��" HIR "׷�����" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/zhuihun-jian/zhui", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHUI "��\n");

        if (me->query_skill_mapped("sword") != "zhuihun-jian") 
                return notify_fail("��û�м���׷�������������ʩչ" ZHUI "��\n");

        if ((int)me->query_skill("zhuihun-jian", 1) < 100)
                return notify_fail("���׷���������������죬����ʩչ" ZHUI "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʩչ" ZHUI "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����ߣ�����" + weapon->name() +
              HIR "һʽ��׷��������������ʱ����һ��Ѫ�⣬ֱ��$n"
              HIR "��\n" NOR;

        addn("neili", -150, me);
        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");
        if (target->is_bad()) ap += ap / 5;

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           (: final, me, target, damage :));
        } else
        {
                msg += CYN "��$n" CYN "ȴ������㣬һ˿���ң�"
                       "ȫ�񽫴��л��⿪����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "ֻ��$n" HIR "һ���ҽУ�����һ�����ض��룬��"
                "ʱ��Ѫ�Ĵ��ɽ���\n" NOR;
}