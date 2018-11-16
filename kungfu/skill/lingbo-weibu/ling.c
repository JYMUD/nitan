// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "�����貨" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);


int perform(object me, object target)
{
        string msg;
        int level, ap, dp, count;

        if (! target) target = offensive_target(me);
        if (! target || ! target->is_character() || ! me->is_fighting(target))
                return notify_fail("��һ��������ô��\n");

        if ((level = me->query_skill("lingbo-weibu", 1)) < 120)
                return notify_fail("����貨΢������������������ʩչ" + name() + "��\n" NOR);

        if( query("neili", me)<600 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n" NOR);

        if( query_temp("lingbo", me) )
                return notify_fail("���Ѿ����������貨���ˡ�\n");

        if( query("gender", me) == "Ů��" )
               msg = HIW "\n$N" HIW "�����������������������ʮ"
                     "���ԣ����貨΢����ͷ��βѸ���ޱȵ�����һ�Ρ� "
                     "$N" HIW "�����������������ζ�ʱ��ӯ�ޱȣ�"
                     "΢���貨���������ң���ַ��ӵ����쾡����\n" NOR;

        else   msg = HIC "\n$N" HIC "�����������������������ʮ"
                     "���ԣ����貨΢����ͷ��βѸ���ޱȵ�����һ�Ρ�                    "
                     "ֻ��$N" HIC "��̬Ʈ�ݣ�Ӱ���ҷɣ����ζ�ʱ��"
                     "ӯ�ޱȣ��������ң���ַ��ӵ����쾡����\n" NOR;

        message_combatd(msg, me, target);
/*
        count = level / 30;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("lingbo", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), level / 2);

        addn("neili", -400, me);
        return 1;
*/
        ap = attack_power(me, "dodge");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIW "$N���������·���$n������$N���貽ת�˸�ͷ���ۻ�\n" NOR;
                if (! target->is_busy())
                target->start_busy(ap / 60 + 4);
                addn("neili", -400, me);
                me->start_busy(1);
        } else
        {
                msg = HIG "����$n������$N���貽,��̬���ݵĶ��˹�ȥ\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;

}

/*
void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("lingbo", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("lingbo", me);
                tell_object(me, "��ġ������貨���˹���ϣ��������ջص��\n");
        }
}
*/