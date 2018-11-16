#include <ansi.h>
#include <combat.h>

#define CANG "��" HIY "�Ʋ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object anqi;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/huilong-bifa/cang", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(CANG "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(anqi=query_temp("handing", me)) || 
            query("skill_type", anqi) != "throwing" )
                return notify_fail("���������в�û�����Ű�����\n");

        if ((int)me->query_skill("huilong-bifa", 1) < 120)
                return notify_fail("��Ļ���起�������죬����ʩչ" CANG "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" CANG "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������ˡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ����ȣ�����һ���׶�ʱ�ų�һ������������" +
              query("name", anqi)+NOR+HIY"��������������$n"HIY"��\n"
              NOR;

        ap = me->query_skill("force") + me->query_skill("throwing");
        dp = target->query_skill("dodge") + target->query_skill("parry");
        me->start_busy(3);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap / 2 + random(ap / 2);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 40,
                                           HIR "$n" HIR "ֻ������Ϯ�壬��ͷ�䣬��"
                                           "��"+query("name", anqi)+NOR+HIR
                                           "���˶˲����Լ��ؿڣ���ʱ��ŭ������Ż"
                                           "��һ����Ѫ��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ����"
                       "��һԾ���𣬶�ܿ�����\n" NOR;
        }

        if( query("id", anqi) == "huilongbi" )
        {
                msg += HIC "��ʱȴ����������һ���������ַɻص�$N"
                       HIC "���С�\n" NOR;
        }
        message_combatd(msg, me, target);

        if( objectp(anqi) && query("id", anqi) != "huilongbi" )
                destruct(anqi);

        return 1;
}