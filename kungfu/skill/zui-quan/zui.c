// zui.c �޺����

#include <ansi.h>

#define PFM_NAME        "�޺����"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int skill;
 
        if( query("neili", me)<150 )
                return notify_fail("�������������ʩչ��" + PFM_NAME + "����\n");

        if( query_temp("zui-quan_zui", me) )
                return notify_fail("���Ѿ���������������ˡ�\n");
        
        if ((int)me->query_skill("zui-quan", 1) < 80)
                return notify_fail("�����ȭ�������ң��޷�ʩչ��" + PFM_NAME + "����\n");

        msg = HIY "$N" HIY "��������һ�䣬˫ȭ���գ�ʹ��һ�С�" + PFM_NAME +
              HIY "������������֡�\n"
              HIG "���Ʋ������ģ���̬�ɾУ�������ȴ���֮����\n" NOR;

        message_combatd(msg, me);
        addn("neili", -100, me);

        skill = me->query_skill("zui-quan", 1);
        count = skill * (3 + random(5)) / 10;
        addn_temp("dex", count, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, count :), skill / 3);

        set_temp("zui-quan_zui", 1, me);

        me->start_busy(1 + random(3));
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("zui-quan_zui", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("zui-quan_zui", me);
                tell_object(me, "����޺�����˹���ϣ��������ջص��\n");
        }
}