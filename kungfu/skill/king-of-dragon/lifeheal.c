// lifeheal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( !wizardp (me)) return 0;
        if( !target )
                return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

        message_combatd( HIY "$N�������������ڹ�������������$n���ģ������ؽ���������$n����....\n\n���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ����Ѫ����ɫ������������ˡ�\n" NOR, me, target );

        set("eff_qi",query("max_qi",  target), target);
        set("qi",query("max_qi",  target), target);

        return 1;
}