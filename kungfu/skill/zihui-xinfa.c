// zihui-xinfa �ϻ��ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
//        return force == "murong-xinfa";
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zihui-xinfa", 1);
                return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "����" && me->query_skill("zihui-xinfa",1)>49 )
                return notify_fail("���޸����ԣ�������������������������ϻ��ķ���\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�ϻ��ķ���\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�ϻ��ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"zihui-xinfa/" + func;
}
