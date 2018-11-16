// This program is a part of NITAN MudLIB
// xue.c ��ѩ�׷�

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "��ѩ�׷�" NOR; }

string *desc = ({
HIW"\n                  ^����������^          \n" NOR,
HIY  "                ^^^ɽ��������^^^       \n" NOR,
RED  "             ^^^^^^�ع�õ磡^^^^^^  \n" NOR,
HIM  "          ^^^^^^^^^���ӿ�����^^^^^^^^^ \n" NOR,
HIC  "       ^^^^^^^^^^^^��ɽѩ����^^^^^^^^^^^^ \n" NOR,
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, level;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹���\n");

        if ((int)me->query_skill("tianshan-zhang", 1) < 100)
                return notify_fail("�����ɽ�ȷ��������ң��޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("��û�м�����ɽ�ȷ���ʹ����" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "ʹ�����޾�������ѩ�׷ɡ�����ʽ��ù����쳣��\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);
        level = me->query_skill("tianshan-zhang", 1);
        addn("apply/attack", level/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                msg = desc[i];
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("apply/attack", -level/2, me);
        me->start_busy(1 + random(3));
        return 1;
}
