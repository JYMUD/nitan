// luoying-xinfa.c ��Ӣ�ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        return ::valid_learn(me);
}

int valid_force(string force)
{
        return force == "bibo-shengong";
}

int practice_skill(object me)
{
        return notify_fail("��Ӣ�ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return SKILL_D("luoying-xinfa/") + func;
}

