#include <ansi.h>
#include <combat.h>

#define XIAO "��" HIW "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/lingyun-jian/xiao", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAO "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" XIAO "��\n");

        if ((int)me->query_skill("lingyun-jian", 1) < 120)
                return notify_fail("�����ƽ���������죬����ʩչ" XIAO "��\n");

        if (me->query_skill_mapped("sword") != "lingyun-jian")
                return notify_fail("��û�м������ƽ���������ʩչ" XIAO "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʩչ" XIAO "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" XIAO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "��̾һ���������Ȼ����Ȼ����бָ��"
              "�գ�����" + wn + HIW "������������Ȼ��ʹ����"
              "�С�" HIY "��������" HIW "����ɲʱ�佣������"
              "��" + wn + HIW "��ֱ������֮�ƣ�ն��$n\n" HIW "��" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "ֻ��һ���������������" 
                                          "�������ѣ�����Ѫ�Ѵ�$n�ؿ������\n" 
                                          NOR);
                 me->start_busy(2 + random(4));
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "Ȼ��$n" CYN "�����ֿ죬����һ��"
                      "���$N" CYN "��һ����\n" NOR;

                 me->start_busy(2);
                 addn("neili", -180, me);
        }
        message_vision(msg, me, target);

        return 1;
}


