inherit FORCE;

int is_ultimate_skill() { return 1; }

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zhanshenjue", 1);
        return lvl * lvl * 15 * 3 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�׻��ķ���\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�׻��ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

