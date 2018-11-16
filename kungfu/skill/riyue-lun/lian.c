// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "������ת" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string wp, msg;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("��û�м��������ַ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("riyue-lun", 1) < 150)
                return notify_fail("�������ַ�����㣬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wp = weapon->name();

        msg = HIY "$N" HIY "��Ŀ��ȣ�ʩչ�������ַ���" HIW "������ת"
              HIY "���񼼣���ؽ�����" + wp + HIY "����\n������������"
              "����â���໥������ѹ��$n" HIY "������ɷΪ���棡\n" NOR;
        message_combatd(msg, me, target);

        if ((int)me->query_skill("longxiang-gong", 1) < 90)
                count = me->query_skill("force", 1) / 8;
        else
                count = me->query_skill("longxiang-gong", 1) / 4;

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! weapon->is_item_make()
                    && query("id", weapon) == "riyue jinlun" )
                {
                        switch (i)
                        {
                        case 0:
                                msg = WHT "ͻȻ�����ִ����½����з���"
                                      "����������һ����â��$n" WHT "��"
                                      "ȥ��\n" NOR;
                                break;
                        case 1:
                                msg = HIR "ͻȻ�����ִ����½����з���"
                                      "����������һ����â��$n" HIR "��"
                                      "ȥ��\n" NOR;
                                break;
                        case 2:
                                msg = YEL "ͻȻ��ͭ�ִ����½����з���"
                                      "����������һ����â��$n" YEL "��"
                                      "ȥ��\n" NOR;
                                break;
                        case 3:
                                msg = HIW "ͻȻ�����ִ����½����з���"
                                      "����������һ����â��$n" HIW "��"
                                      "ȥ��\n" NOR;
                                break;
                        default:
                                msg = HIY "ͻȻ����ִ����½����з���"
                                      "����������һ����â��$n" HIY "��"
                                      "ȥ��\n" NOR;
                                break;
                        }
                        message_combatd(msg, me, target);
                        COMBAT_D->do_attack(me, target, weapon, 30);
                } else
                        COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("neili", -250, me);
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        me->start_busy(1 + random(3));
        return 1;
}

