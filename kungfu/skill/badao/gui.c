#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define LONG "��" HIY "�麣һ��" NOR "��"

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("��Ե�������죬�޷�ʩչ" LONG "��\n");

        if ((int)me->query_skill("force") < 700)
                return notify_fail("���ڹ���򲻹����޷�ʩչ" LONG "��\n");

        if( query("neili", me)<2000 )
                return notify_fail("�����������������޷�ʩչ" LONG "��\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("��û�м����Ե����޷�ʩչ" LONG "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "\n$N" HIC "��¶��ɫ������һ�������϶��£�ɲ�Ǽ䣬��ؿ޺�����ǧ�������糱ˮ��"
              "�˰�׳�ۣ�����ǵص���ǰ�������Ȼ������������Ϊһ����â���������������$n" HIC "��\n" NOR;

        ap=me->query_skill("blade")+me->query_skill("martial-cognize",1);
        dp=target->query_skill("dodge")+target->query_skill("martial-cognize",1);
        if (ap * 4 / 5 + random(ap) > dp)
        {
                me->start_busy(3);
                damage = ap * 3 + random(ap * 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300 + random(100),
                                           HIR "�����������ޱȵĵ������������Ĵ�$n" HIR "�ؿ�͸�����������ë���Ȼ��\n" NOR);
                addn("neili", -1800, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "Ȼ��$n" CYN "����һЦ������������������л��⡣\n" NOR;
                addn("neili", -120, me);
        }

        message_combatd(sort_msg(msg), me, target);
        
        return 1;
}
