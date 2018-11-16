#include <ansi.h>
#include <combat.h>

#define KAI "��" HIY "����ٵ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/pangu-qishi/kai", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "hammer" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" KAI "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" KAI "��\n");

        if (me->query_skill("pangu-qishi", 1) < 180)
                return notify_fail("����̹�������Ϊ����������ʩչ" KAI "��\n");

        if( query("neili", me)<400 )
                return notify_fail("�����������������ʩչ" KAI "��\n");

        if (me->query_skill_mapped("hammer") != "pangu-qishi")
                return notify_fail("��û�м����̹����ƣ�����ʩչ" KAI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "һ���Ϻȣ�����" + weapon->name() +
              WHT "��ɽ��Ρ�ţ�Я�ſ���ٵ�֮����$n" WHT "�������£�\n" NOR;

        ap=me->query_skill("hammer")+query("str", me)*10;
        dp=target->query_skill("force")+query("con", target)*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -500, me);
                me->start_busy(5);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "��ܲ�������$N" HIR "��"
                                           "�������ؿڣ���ʱһ�����죬���ݰ����"
                                           "��ɳ�ȥ��\n" NOR);
        } else
        {
                addn("neili", -300, me);
                me->start_busy(6);
                msg += HIC "����$n" HIC "�����ĵ���$N" HIC "������"
                       "�ľ��������а�������ʱ���������Ρ�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}