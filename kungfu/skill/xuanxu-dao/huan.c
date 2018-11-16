#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "�һ���"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���һ�����ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ���һ�����\n");

        if (me->query_skill("xuanxu-dao", 1) < 135)
                return notify_fail("������鵶����Ϊ������Ŀǰ����ʹ���һ�����\n");

        if( query("neili", me)<250 )
                return notify_fail("�����������������ʹ���һ�����\n");

        msg = HIW "$N" HIW "ʹ�����鵶���еľ����һ����������ɻ�������������ֻ�ʵ�$n" + HIW
             "��ǰһƬӰ����\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "�����������������������죬$p" HIR "һ��"
                                           "�ҽУ�ȫ�������ͷ������һһ�ʶϣ���̲�����"
                                           "������ȥ��\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "�����񵲣�$P" CYN
                       "ֻ���þ�������˥�ߣ����е��⽥���� \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
