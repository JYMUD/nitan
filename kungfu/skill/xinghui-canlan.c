// xinghui-canlan.c �ǻԲ���
// By haiyan

inherit SKILL;

int valid_enable(string usage) { return usage == "throwing"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("����ڹ��ķ���򲻹����޷�ѧ�ǻԲ��á�\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("����Ṧ��򲻹����޷������ǻԲ��á�\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("������������ɣ��޷������ǻԲ��á�\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("mantianhuayu-zhen", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ���������������ǻԲ��á�\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<60 )
                return notify_fail("��������������ǻԲ��á�\n");

        me->receive_damage("qi", 45);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xinghui-canlan/" + action;
}
