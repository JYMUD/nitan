// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "����鳤" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int cost;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("��û�м������｣��������ʩչ" + name() + "��\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 150)
                return notify_fail("�����｣���ȼ�����������ʩչ" + name() + "��\n");

        if( query("neili", target)<300 )
                return notify_fail("�����ӶԷ������������棬��������" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "���е�" + weapon->name() + HIG "ٿ�Ĵ̳�������һ��"
              "����������ס������������\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("chuixiao-jiafa", 1);
        dp = defense_power(target, "force") +
             target->query_skill("chuixiao-jiafa", 1);

        if (ap > dp || ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);
                msg += HIM "$p" HIM "�پ�$P" HIM "������������һ���������У���"
                       "��׽��ȥ����ֻ��ǿ������������\n" NOR;
                cost = 500 + (ap - dp) * 3 / 2;
                if( cost>query("neili", target) )
                        cost=query("neili", target);
                addn("neili", -cost, target);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += HIC "����$p" HIC "���񰲶���˿��û���ܵ�����\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}