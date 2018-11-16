#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) 
{ 
       return usage == "throwing"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ��ķ���򲻹����޷�ѧ����롣\n");

        if ((int)me->query_skill("dodge") < 80)
                return notify_fail("����Ṧ��򲻹����޷���������롣\n");

        if ((int)me->query_dex() < 26)
                return notify_fail("������������ɣ��޷���������롣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("yufeng-zhen", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ������������������롣\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<60 )
                return notify_fail("�����������������롣\n");

        me->receive_damage("qi", 52);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yufeng-zhen/" + action;
}