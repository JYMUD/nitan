// This program is a part of NITAN MudLIB
// cui.c ���Ķϳ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "���Ķϳ�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, fp, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("�����Ķϳ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("����ߵ��湦��Ϊ���ޣ�����ʹ�á����Ķϳ�����\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������޷����á����Ķϳ�����\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õı������ԣ���ôʹ�á����Ķϳ�����\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("��û�н�" + (string)to_chinese(skill)[4..<1] +
                                   "����Ϊ�ߵ��湦, ����ʹ�á����Ķϳ�����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "һ�����ȣ�˫��һ���������ʱ���ɰ��ʯ��$n"
                      HIW "ֻ���ü�����Ϣ��\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "һ�����ȣ�����" + weapon->name() +
                      HIW "ֱ�����£�ֻ����Х�����������ϵĳ��������������׷׷������\n" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "һ�����ȣ�����" + weapon->name() +
                      HIW "��ɨ������һʱ�䳾�����$n"
                      HIW "��ʱ���ú���������\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        fp = defense_power(target, "force");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) < fp)
        {
                addn("neili", -200, me);
                msg += CYN "����$n" CYN "�ڹ���񣬷�������$N"
                       CYN "��һ�У�˿������\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -50, me);
                msg += CYN "$n" CYN "����һЦ��Ʈ��Ծ������$N"
                       CYN "��һ��ȫȻ��ա�\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -220, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "ֻ����$N" HIR "��������"
                                           "��ɽ����һ�㣬���ֵܵ������ۡ���һ���³�һ�����Ѫ��\n" NOR);
        }
        message_combatd(msg, me, target);

        return 1;
}


