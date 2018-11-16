#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "ǧ�˰���" NOR; }

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("yunv-jian", 1) < 40)
                return notify_fail("����Ů����������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("��û�м�����Ů����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<60 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "��Ȼ����̬��ǧ����Ʈ�ݣ�����һ�����"
              "���˵�Ů�����������һ����\n����$N����" + wn + HIC "ȴ"
              "������������ӯ�ػζ������ƺ����·���ȴ��������������"
              "������ʽ��" NOR;

        message_combatd(msg, me, target);

        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "������$n" HIY "��ʽ�е���ʵ����æ"
                      "��ס�Լ�ȫ��һʱ������Ӧ�ԣ�\n" NOR;
                target->start_busy(2 + random(ap / 100));
        } else
        {
                msg = CYN "����$N" CYN "������$n" CYN "���������У���"
                      "ʱһ˿���ң���������\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}