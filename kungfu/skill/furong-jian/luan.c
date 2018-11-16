#include <ansi.h>
#include <combat.h>

#define LUAN "��" HIM "�ҽ�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if( userp(me) && !query("can_perform/furong-jian/luan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" LUAN "��\n");

        if ((int)me->query_skill("furong-jian", 1) < 100)
                return notify_fail("��ܽ�ؽ���������죬����ʩչ" LUAN "��\n");

        if (me->query_skill_mapped("sword") != "furong-jian")
                return notify_fail("��û�м���ܽ�ؽ���������ʩչ" LUAN "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʩչ" LUAN "��\n");

        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("����Ṧ��򲻹�������ʩչ" LUAN "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ" LUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIM "\n$N" HIM "��Хһ�����ڿն���" + wn + "�ڿ������һ����"
              HIM "������̼佣����ɢ������������\n������������Ӱ������$n"
              HIM "ȫ��" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("furong-jian", 1);
        dp = target->query_skill("dodge", 1);

        if (random(ap) >= random(dp / 3))
        {
                 damage = me->query_skill("furong-jian", 1);
                 damage += random(damage / 3);

                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "ֻ����������Ϯ�������Լ���Χ"
                                           "ס������ԥ�䣬$n" HIR "�ѱ�" + wn + HIR 
                                           "�̵�Ƥ��������\n" NOR);
                 me->start_busy(3);
                 addn("neili", -100, me);
        } else
        {
                 msg = CYN "Ȼ��$n" CYN "�������е�����������һ��"
                      "��Ȼ���$N" CYN "��һ����\n" NOR;

                       me->start_busy(3);
                 addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}