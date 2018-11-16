#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( query_temp("gui_yuan", me) )
                return notify_fail("���Ѿ����𡸾�����Ԫ���ˡ�\n");

        if ((int)me->query_skill("shexing-lifan", 1)< 150)
                return notify_fail("��������귭�ȼ�����������ʩչ���������\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("���������ʹ�á�������Ԫ��������\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("����Ṧ��Ϊ����������ʹ�ô��������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ����ʹ�á�������Ԫ����\n");

        if( query("neili", me)<250 )
                return notify_fail("���ʱ���������㣡\n");

        msg = HIW "$N" HIW "�������������˫�۹���һ���죬����һչ����"
                  "���˶�ʱ���Ʈ���ٶȱ���쳣���ݡ�\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("shexing-lifan", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("apply/str", count, me);
        addn_temp("apply/dex", count, me);
        set_temp("gui_yuan", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("gui_yuan", me) )
        {
                addn_temp("apply/str", -amount, me);
                addn_temp("apply/dex", -amount, me);
                delete_temp("gui_yuan", me);
                tell_object(me, "��ġ�������Ԫ���˹���ϣ��������ջص��\n");
        }
}
