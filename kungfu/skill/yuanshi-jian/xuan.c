#include <ansi.h>
#include <combat.h>

#define XUAN "��" HIW "������ת" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/yuanshi-jian/xuan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XUAN "��\n");

        if ((int)me->query_skill("yuanshi-jian", 1) < 180)
                return notify_fail("���ԭʼ����������죬����ʩչ" XUAN "��\n");

        if( query("neili", me)<400 )
                return notify_fail("�����������������ʩչ" XUAN "��\n");

        if (me->query_skill_mapped("sword") != "yuanshi-jian")
                return notify_fail("��û�м���ԭʼ����������ʩչ" XUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ������" + weapon->name() + HIW "��������佣������"
              "��ӿ��$n" HIW"�����糱ˮ��һ�˸߹�һ�ˡ�\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("force");
        attack_time = 5;
        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "��ʱֻ����ͷ��Ŀѣ��������ת��һʱ"
                       "�����мܡ�\n" NOR;
                count = ap / 16;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "������ӿ����æ����ֵ�"
                       "����Ϊ������\n" NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*30, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}