// This program is a part of NITAN MudLIB
// jiubu.c �Ų�ʽ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "�Ų�ʽ"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("���Ų�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 120)
                return notify_fail("�����÷�ַ�������죬����ʹ�á��Ų�ʽ����\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ�����ߣ��������á��Ų�ʽ����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʹ�á��Ų�ʽ����\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("��û�м�����ɽ��÷�֣�����ʹ�á��Ų�ʽ����\n");

        msg = HIC "$N" HIC "˫������ʵʵ��ץ��$n"
              HIC "��Ҫ��������翣���ʽ���أ���������׽����\n" NOR;

        ap=attack_power(me,"hand")+me->query_str()*20;
        dp=defense_power(target,"dodge")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$p" HIR "һ�����ܲ����������$P"
                                           HIR "ץ�˸����У�������Ϣ���ɵ�һ�ͣ���Ѫ��ӿ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�������ݣ�����Ķ����$P"
                       HIC "�Ĺ�����\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}