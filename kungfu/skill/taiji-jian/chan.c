// This program is a part of NITAN MudLIB
// chan.c ���־�

#include <ansi.h>

string name() { return "���־�"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��" + name() + "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("�����ý�����ʩչ��" + name() + "����\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("�������������ʩչ��" + name() + "����\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("���̫���񹦻�򲻹�������ʩչ��" + name() + "����\n");

        if (me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("���̫������������죬����ʹ�á�" + name() + "����\n");

        msg = HIG "$Nʹ��̫�������������־���������������������ͼ����$n�Ĺ��ơ�\n"
              HIG "��Ȼ����" + weapon->name() + HIG "����һ����ԲȦ�����ڽ��ȣ�"
              HIG "���಻��������������һ�Ŵ���������$n�ս���\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -query("max_neili", me)/50, me);
                msg += HIC "\n���̫������ɢ������ϸ˿Խ��Խ�࣬���ǻ�����һ����˿�ޣ���$p��������������\n" NOR;
                target->start_busy(ap / 80 + 3);
                me->start_busy(1);
        } else
        {
                addn("neili", -query("max_neili", me)/80, me);
                msg += HIY "\n����$p������$P����ͼ������һԾ�����ӳ�Ȧ�⡣\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n̫���������־�����"NOR"\n");
        write(@HELP
        ̫������Բת���ϣ����಻�����ٵ���֮������Ԧ����ʹ���������־�ÿ��
        һ�У����Ʒų�һ��ϸ˿����ס���֣�ǧ���򻯣������޾���ʹ���޷�������
        ���ҿ����Զ���������������ֱ�����ܶ��֡�

        Ҫ��  ������� 1000 ���ϣ�
                ���� 500 ���ϣ�
                ̫�����ȼ� 100 ���ϣ�
                ����̫����Ϊ�мܣ�
                ��δ���ƴ򲻻��֡�
HELP
        );
        return 1;
}