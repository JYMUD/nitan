#include <ansi.h>
#include <combat.h>

string name() { return HIW "���ѩ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 50)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("xueshan-jian", 1) < 30)
                return notify_fail("���ѩɽ������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<50 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("��û�м���ѩɽ����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        //msg = HIC"$N�ؽ����裬���Ʋ��ϼӿ죬������Х��ɢ����ƬƬѩ�����磬ƮȻ������\n�γ�һ��ѩ�������У���$n�������\n";
        msg = HIW "$N" HIW "�ؽ����裬һʽ�����ѩ�衹ʩ�����������಻������"
              "Х��������ͼ��$n" HIW "�������С�\n" NOR;

        addn("neili", -30, me);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "ֻ�����ؽ�Ӱ����ǵ����Լ���"
                       "�����ٱ����˸���æ���ң���֪���Ӧ�ԡ�\n"
                       NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
