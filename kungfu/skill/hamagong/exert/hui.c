// hui.c ��󡹦��Ϣ

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        int skill;
        string msg;

        if( !(skill=query_temp("reverse", me)) )
                return notify_fail("�㲢û�е�ת��������\n");

        msg = HIB "$N" HIB "�����³�һ��������ɫ���˱䣬����������\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/defense", -skill/4, me);
        addn_temp("apply/armor", -skill/2, me);
        addn_temp("apply/dispel_poison", -skill/2, me);
        addn_temp("apply/reduce_poison", -10, me);
        delete_temp("reverse", me);

        set("neili", 0, me);
        return 1;
}