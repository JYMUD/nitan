#include <ansi.h>
#include <combat.h>

string name() { return HIY "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("������ɨҶ�Ȳ�����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("�������ɨҶ�Ȳ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "xuanfeng-tui")
                return notify_fail("��û�м�������ɨҶ�ȣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "xuanfeng-tui")
                return notify_fail("��û��׼������ɨҶ�ȣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʹ���һ�������������Ʈ������������糾����Я"
              "������������ɣ�\n" NOR;
        message_combatd(msg, me);
        addn("neili", -100, me);

        count = me->query_skill("bibo-shengong", 1) / 2 + me->query_skill("xuanfeng-tui", 1);
        addn_temp("apply/attack", count, me);

        msg = YEL  "\n$N" YEL"���������ƣ�����һ�Ÿ����߳���\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "��Ӱ�У�" HIM "$N" HIM "����������ƴ����û���$n��\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "��" YEL "$n" YEL "�Ż��󿪣�����������˫����������" YEL "$n��\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "$N" HIM "ԽսԽ�£���Χ����һ�����磬ʹ��" HIM "$n" CYN "�����巽��\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "���ǹ�է�֣������Դ���Ȼ֮ɫ����" YEL "$n��\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM "$N" HIM "��Хһ��������෢����Ȼת��" HIM "$n" HIM"��󣬷�������һ�ƣ�\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        addn("neili", -100, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count, me);
        return 1;
}