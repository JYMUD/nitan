// tiaoyan.c ��������֮������ʽ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ʽ��ֻ����ս���жԶ���ʹ�á�\n");

        if ((lvl = me->query_skill("duanyun-fu")) < 60)
                return notify_fail("��Ķ��������������ң�����ʩչ������ʽ����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷�ʩչ������ʽ����\n");

        msg = HIG "$N" HIG "ʹ����������֮������ʽ�������⼲��$n" HIG "˫�ۡ�\n" NOR;

        me->start_busy(2);
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, lvl, 45,
                                           HIR "���$p" HIR "ֻ������ǰһ�ڣ�˫��һ"
                                           "���ʹ��Ѫ�����档\n" NOR);
        } else
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ����æ�㿪�ˡ�\n" NOR;

        message_combatd(msg, me, target);

        return 1;
}