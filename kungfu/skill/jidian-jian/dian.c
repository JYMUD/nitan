#include <ansi.h>
#include <combat.h>

#define DIAN "��" HIY "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/jidian-jian/dian", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ������޷�ʩչ" DIAN "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" DIAN "��\n");

        if (me->query_skill("jidian-jian", 1) < 100)
                return notify_fail("��ļ��罣����Ϊ�������޷�ʩչ" DIAN "��\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������޷�ʩչ" DIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���һ��������" + weapon->name() + NOR + HIY
              "һ�����˽���ɣ���ʱ֮�䣬�Ĵ����ǵ�⣬ҫ����Ŀ��\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                addn("neili", -180, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "ֻ������ৡ�������$n" HIR "�޷�"
                                           "��͸������ʵ������������������һ����"
                                           "�У�Ѫ��Ȫӿ��\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "�����񵲣�$P" CYN "ֻ"
                       "���ö��ַ������ܣ����н��⽥���� \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}