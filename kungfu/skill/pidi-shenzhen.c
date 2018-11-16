#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
        object ob;
  
        if (me->query_skill("throwing", 1) < 40)
                return notify_fail("��İ������ܲ�����졣\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("pidi-shenzhen", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ�������������ıٵ����롣\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("�����������û�а취��ϰ�ٵ����롣\n");

        if( query("neili", me)<60 )
                return notify_fail("�������������û�а취��ϰ�ٵ����롣\n");

        me->receive_damage("qi", 70);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pidi-shenzhen/" + action;
}