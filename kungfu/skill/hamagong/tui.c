// tui.c ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("hamagong", 1);

        if (skill < 240)
                return notify_fail("��ĸ�󡹦��Ϊ�����������ʹ�á�����ʽ����\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ��������޷�ʩչ������ʽ����\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������޷����á�����ʽ����\n");

        msg = HIY "$N" HIY "���ڵ��ϣ����á���һ����У�˫����"
              "����룬ƽ�ƶ�����һ�ɼ����������ͬ"
              "��ɽ����һ�㱼��$n" HIY "��\n" NOR;

        ap=me->query_skill("force")*15+query("max_neili", me);
        dp=target->query_skill("force")*15+query("max_neili", target)+
             target->query_skill("sun-finger", 1) * 20;
        if (dp < 1) dp = 1;
        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -400, me);
                me->start_busy(2);
                damage = (ap - dp) / 10 + random(ap / 10);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "�����͵�������$P" HIR "�����ƺ�"
                                           "�Ⱥƴ�$p" HIR "��ʱ������Ѫ���������ۡ���"
                                           "�³���һ����Ѫ��\n" NOR);
        } else
        if (target->query_skill("sun-finger", 1))
        {
                addn("neili", -300, me);
                msg += HIG "Ȼ��$p" HIG "����һЦ������һָ�̳�������һ"
                       "��ָ�ľ������������׵Ļ�����$P" HIG "�Ĺ��ơ�\n" NOR;
        } else
        {
                addn("neili", -200, me);
                msg += CYN "����$n" CYN "�������˵�˫���ϣ�������$P"
                       CYN "��һ��֮ʽ��ֻ�������һ�����������"
                       "�������\n" NOR;
                me->start_busy(3);
                target->start_busy(2);
                if( query("neili", target)>200 )
                        addn("neili", -200, target);
                else
                        set("neili", 0, target);
        }
        message_combatd(msg, me, target);

        return 1;
}