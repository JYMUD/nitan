// This program is a part of NITAN MudLIB
// jie.c ��������

#include <ansi.h>
inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        object obj;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_character())
                return notify_fail("��Ҫ��˭����������\n");

        if (((int)me->query_skill("bahuang-gong", 1) < 40 ) &&
            ((int)me->query_skill("beiming-shengong", 1) < 40 ))
                return notify_fail("��ı����ڹ�������죬���ܽ���������\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 150)
                return notify_fail("�����ɽ�����Ʋ�����죬���ܽ���������\n");

        if (! objectp(obj = present("jiudai", me)))
                return notify_fail("������û�оƴ����޷������ⶾ��\n");

        if( query("neili", me)<200 )
                return notify_fail("���������㡣\n");

        if (! target->query_condition("ss_poison"))
                return notify_fail("Ŀ��û������������\n");

        message_combatd(HIY CYN "\n$N��ɫͻ�䣬���м�ת��������$n�˰���ʮ���ƣ��⿪��$n������������\n" NOR, me, target);
        addn("neili", -200, me);
        me->start_busy(2);
        target->clear_condition("ss_poison");
        return 1;
}
