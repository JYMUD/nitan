// This program is a part of NITAN MudLIB
// zhao.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "�������"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ա�ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("pudu-zhang", 1) < 135)
                return notify_fail("����ն��ȷ���Ϊ������Ŀǰ����ʹ�÷�����գ�\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����������������ʹ�÷�����գ�\n");

        if (me->query_skill_mapped("staff") != "pudu-zhang")
                return notify_fail("��û�м����ն��ȷ�������ʹ�÷�����գ�\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "������Ц���Ӷ����е�" + weapon->name() +
              HIY "����̩ɽһ��ѹ��$n" + HIY "������̾Ϊ��ֹ��\n" NOR;

        ap=attack_power(me,"staff")+query("max_neili", me)/10;
        dp=defense_power(target,"force")+query("max_neili", target)/10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "ֻ��$p" HIR "�ƺ�һ�������ж���"
                                           "�����������ӷɵ���ȥ�����ص�ˤ���ڵ��ϣ�\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�⾪�춯�ص�һ����\n"NOR;
                me->start_busy(2+random(1));
        }
        message_combatd(msg, me, target);

        return 1;
}
