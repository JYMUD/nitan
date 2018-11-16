// This program is a part of NITAN MudLIB
// jianzhang.c  ����������

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "����������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if( query("neili", me)<160 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("huashan-sword", 1) < 50)
                return notify_fail("��Ļ�ɽ�����������ң��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("��û�м�����ɽ�������޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʹ����ɽ�ɾ�����" HIW "����������" HIY"��������Ȼ�ӿ죡\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);

        count = me->query_skill("sword");
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
