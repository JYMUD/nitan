#include <ansi.h>
#include <combat.h>

#define YIN "��" HIM "����������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/qixian-wuxingjian/yin", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! me->is_fighting(target))
                return notify_fail(YIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" YIN "��\n");

        skill = me->query_skill("qixian-wuxingjian", 1);

        if (skill < 160)
                return notify_fail("���������ν���Ϊ���ޣ�����ʩչ" YIN "��\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("��û��׼���������ν�������ʩչ" YIN "��\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("��û��׼���������ν�������ʩչ" YIN "��\n");

        if (me->query_skill("force") < 250)
                return notify_fail("����ڹ���Ϊ����������ʩչ" YIN "��\n");

        if( query("neili", me)<600 )
                return notify_fail("�����ڵ���������������ʩչ" YIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if (weapon)
        {
                msg = HIM "ֻ��$N" HIM "һ����ߣ����ھ��߶�" + weapon->name()
                      + HIM "�������������������Ȼ���죬ֻ����࣡���\nһ���ƿ�"
                      "֮�죬һ�����ν������������ֱ��$n" HIM "��ȥ��\n" NOR;
        } else
        {
                msg = HIM "ֻ��$N" HIM "һ����ߣ�����ھ������������������"
                      "Ȼ���죬ֻ����࣡���һ���ƿ�֮\n�죬һ�����ν�������"
                      "�����ֱ��$n" HIM "��ȥ��\n" NOR;
        }

        ap = me->query_skill("force");
        dp = target->query_skill("force");

        if( query("max_neili", target)<10 )
        {
                msg += HIM "$N" HIM "��һ��ʩ��������$n"
                       HIM "����û��һ�㣬˿������\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        // �ȼ��������Ҳ����ֺ�
        if( userp(target) && query("max_neili", target)+500>query("max_neili", me) )
        {
                msg += HIM "����$n" HIM "�����������׾�����$N"
                       HIM "��һ�У�˿������\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "����$n" CYN "��æ���������Ŭ��ʹ�Լ�"
                       "���������ĸ��ţ����ڻ�������һ�С�\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        {
                damage = ap + skill;
                damage += random(damage);

                target->receive_damage("jing", damage * 4 / 3, me);
                target->receive_wound("jing", damage / 3, me);

                msg += HIR "$n" HIR "ֻ����$N" HIR "������������"
                       "������һ��������͸��Ĥ�����ۡ������һ��"
                       "��Ѫ��\n";

                me->start_busy(2);
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

