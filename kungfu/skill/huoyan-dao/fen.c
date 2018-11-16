// This program is a part of NITAN MudLIB
// fen.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����"; }
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("huoyan-dao", 1);

        if (skill < 120)
                return notify_fail("��Ļ��浶�ȼ�������������ʹ����������\n");

        if (me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʹ������������\n");

        if( query("neili", me)<400 )
                return notify_fail("��������������޷��˹���\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "�������ƣ�ʹ��һ�С����������ε�����$n"
              HIR "���ؿڻ�ȥ��\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$p" HIR "ǿ��������ͼ�ֿ���Ȼ���޷�����$P"
                                           HIR "�����ı仯�������$P"
                                           HIR "�����ε����ش����ؿڣ�\n" NOR);
                me->start_busy(2);

        } else
        {
                msg += HIC "ȴ��$p" HIC "���Ų�æ������һ���������$P"
                       HIC "�ı�ɱһ����\n" NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
