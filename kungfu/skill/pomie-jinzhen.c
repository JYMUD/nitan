#include <ansi.h>

inherit SKILL;

int valid_enable(string usage)
{
        return usage == "throwing";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 90)
                return notify_fail("����ڹ���򲻹�����������������롣\n");

        if ((int)me->query_skill("dodge") < 90)
                return notify_fail("����Ṧ��򲻹�����������������롣\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("������鶯��������������������롣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("pomie-jinzhen", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��������������������롣\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<60 )
                return notify_fail("�������������������롣\n");

        me->receive_damage("qi", 45);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pomie-jinzhen/" + action;
}