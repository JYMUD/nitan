#include <ansi.h>
#include <combat.h>

string name() { return HIW "ѩ������" NOR; }

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

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("xueshan-jian", 1) < 140)
                return notify_fail("���ѩɽ������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("��û�м���ѩɽ����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        /*
        msg = HIW "$N" HIW "����" + weapon->name() + HIW
              "����������һ�С�ѩ����������������ʵ��ʵ����"
              "�飬����˷���$n" HIW "��ȥ��\n" NOR;
        */
        msg = HIY"$Nһ������" + weapon->name() + HIY"��һʽ"HIW"��ѩ��������"HIY"�������̳������������������ǣ�\n"
              "�ó�ѩ�����㣬����һ�����ǰ��Ʈ��ȥ��\n"NOR;
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        attack_time = 6;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "ֻ����Ӱ���أ���ʱ�ۻ���"
                       "�ң������˸����ֲ�����ƣ�ڱ�����\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "������ӿ����"
                       "��Ϯ�壬��æ���������С��Ӧ����\n"
                       NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}