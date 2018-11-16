// reserve.c ��󡹦������ת

#include <ansi.h>

inherit F_CLEAN_UP;

void show_effect(object me, int a_amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("hamagong", 1) < 120)
                return notify_fail("��ĸ�󡹦������죬���ᾭ����ת��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ�����������\n");

        if( query_temp("reverse", me) )
                return notify_fail("���Ѿ���ת�����ˡ�\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "����˫�ֳŵص��������˾�������ʱ"
              "��Ϣ������������������\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/defense", skill/4, me);
        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/dispel_poison", skill/2, me);
        addn_temp("apply/reduce_poison", 10, me);//���10%�Ŀ���
        set_temp("reverse", skill, me);

        addn("neili", -100, me);
        if (me->is_fighting())
                me->start_busy(2);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, skill / 3 :), 10);
        return 1;
}

void show_effect(object me, int skill)
{
        if( !query_temp("reverse", me) )
               return ;

        skill=query_temp("reverse", me);

        if( query("neili", me)<200 )
        {
              write(HIG "�����˾����������ľ�����Ȼ����Ѫ��ӿ����о��Լ������ܵ������ˡ�\n" NOR);
              addn("max_neili", -1, me);
              set("neili", 0, me);
              delete_temp("hmg_dzjm", me);
              addn_temp("apply/defense", -skill/4, me);
              addn_temp("apply/armor", -skill/2, me);
              addn_temp("apply/dispel_poison", -1*(skill/2+30), me);
              addn_temp("apply/reduce_poison", -10, me);

              return;
        }

        addn("neili", -200, me);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, skill / 3 :), 10);

        return;
}
