// This program is a part of NT MudLIB
// feng.c �ﳯ��

#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

string name() { return "�ﳯ��"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "�ﳯ��ֻ����ս����ʹ��\n");


        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");


        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����������ʹ�á��ﳯ�ˡ���\n");

        if (me->query_skill("feifeng-bian", 1) < 150)
                return notify_fail("��ķɷ�޷���Ϊ������Ŀǰ����ʹ�á��ﳯ�ˡ���\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʹ�á��ﳯ�ˡ���\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("��û�����ɷ�޷�������ʹ�á��ﳯ�ˡ���\n");

        msg = HIY "$N" HIY "����" HIY "$n" HIY "��٬һЦ����ǰ����,����" + weapon->name() +
              HIY "ȴ����ͣ����һ�С��ﳯ�ˡ�\n"
              HIY "���ϴ�գ�����Ϸ��"
              HIY "���������ֵ�" HIY "$n" HIY "����!! \n" NOR;

        ap = attack_power(me, "whip");
        if (living(target))
                 dp = defense_power(target, "parry");
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR
                       "���˸����ֲ�����Ŀ�Ӳ�Ͼ��ƣ�ڱ�����\n" NOR;
                count = ap;

                addn_temp("apply/attack", count, me);

        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "���ƺ�����������Ȼ������Ӧ����\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn("neili", -150, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}