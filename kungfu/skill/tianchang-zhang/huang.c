// This program is a part of NITAN MudLIB
// huang.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "�������"; }

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��������ġ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ֲ���ʩչ��������ġ���\n");

        if (me->query_skill_mapped("strike") != "tianchang-zhang")
                return notify_fail("��û�м����쳤�Ʒ����޷�ʩչ��������ġ���\n");

        skill = me->query_skill("tianchang-zhang", 1);

        if (skill < 100)
                return notify_fail("����쳤�Ʒ���Ϊ���ޣ�����ʹ�á�������ġ���\n");

        if( query("neili", me)<150 )
                return notify_fail("��������������޷����á�������ġ���\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���롱��һ����ȣ�����������ֻ������һƬѪ�죬ٿ������ĳ���"
              HIR "һ���ȷ��ʱϮ��$n" HIR "����ǰ��Ѩ��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -120, me);
                me->start_busy(2);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "һʱ��ֻ������Ѫ��ӿ����"
                                           "�������٣���Ϣ���ң����ɵ�����һ��"
                                           "��Ѫ��\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += HIC "Ȼ��$n" HIC "�ڹ���տ��˿����Ϊ$N"
                       HIC "���Ʒ���������������" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}