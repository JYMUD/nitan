#include <ansi.h>
#include <combat.h>

#define YANG "��" HIY "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/poguang-dao/yang", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YANG "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" YANG "��\n");

        if ((int)me->query_skill("poguang-dao", 1) < 120)
                return notify_fail("���ƹ⵶��������죬����ʩչ" YANG "��\n");

        if (me->query_skill_mapped("blade") != "poguang-dao")
                return notify_fail("��û�м����ƹ⵶��������ʩչ" YANG "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" YANG "��\n");

        if( query("neili", me)<400 )
                return notify_fail("�����ڵ���������������ʩչ" YANG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "һ��ŭ�ȣ��ھ����ǣ�ʩչ�����С�" HIY "������" HIW 
              "������" + wn + HIW "�����Ļ����������Ȼ��ʽ���Ƽ򵥣�������ȴ"
              "�̲����������������������һ�㡣" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "��$N" HIR "�������ͣ���"
                                          "����˸��������������һ����һ����Ѫ" 
                                          "��ӿ������\n" NOR);
                 me->start_busy(2 + random(4));
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "Ȼ��$n" CYN "�Կ��ƿ죬����"
                      "һ����������С�\n" NOR;

                 me->start_busy(2);
                 addn("neili", -180, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


