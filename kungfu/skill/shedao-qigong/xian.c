// This program is a part of NITAN MudLIB
// xian.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        string skill;
        int ap, pp, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("���������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("shedao-qigong", 1) < 120)
                return notify_fail("����ߵ��湦��Ϊ���ޣ�����ʹ�á��������֡���\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷����á��������֡���\n");

        if( objectp(weapon=query_temp("weapon", me)) &&
            query("skill_type", weapon) != "staff" &&
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õı������ԣ���ôʹ�á��������֡���\n");

        if (weapon)
                skill=query("skill_type", weapon);
        else
                skill = "unarmed";

        if (me->query_skill_mapped(skill) != "shedao-qigong")
                return notify_fail("��û�н�" + (string)to_chinese(skill)[4..<1] +
                                   "����Ϊ�ߵ��湦, ����ʹ�á��������֡���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        switch (skill)
        {
        case "unarmed":
                msg = HIW "$N" HIW "����һԾ����Ȼ�ƽ�$n" HIW "�漴һ����$p"
                      HIW "��ͷ��ȥ������ʵʵ������ǧ�ٱ仯��\n" NOR;
                break;

        case "sword":
                msg = HIW "$N" HIW "�㲻��أ�ƮȻ������ǰ��һ���̳���" +
                      weapon->name() + HIW "ֱָ$n" HIW "���䡣" NOR;
                break;

        case "staff":
                msg = HIW "$N" HIW "����" + weapon->name() +
                      HIW "�������£�����ʵʵ������һ�Ź�Ӱ��ббɨ��$n"
                      HIW "���䡣\n" NOR;
                break;
        }

        ap = attack_power(me, skill);
        pp = defense_power(target, "parry");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > pp)
        {
                addn("neili", -150, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "���ܲ��ܣ����㲻�ã�һ����ʧ"
                                           "����$P" HIR "���˸����У���Ѫ������\n" NOR);
        } else
        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -180, me);
                me->start_busy(2);
                damage = damage_power(me, skill);
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55,
                                           HIR "$n" HIR "��$P" HIR "���м�Ϊ�������"
                                           "�ֵ�����æ����Ծ����ȴ��$P" HIR "��ʽһ�䣬��Ȼ�ϵ����ȣ�\n"
                                           "һ������$p" HIR "��ֱ���˸���Ѫ���·ɽ���\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "���ҵ��������в��У�������ȥ$P"
                       CYN "������ʮ�����仯����©���������\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


