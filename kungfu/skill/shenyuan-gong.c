// shenyuan-gong.c ��Ԫ��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("shenyuan-gong", 1);
        return lvl /10 * lvl /10 * 20 * 15 / 10 / 20;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("shenyuan-gong", 1);
        if( query("gender", me) == "����" && lvl>49 )
                return notify_fail("���޸����ԣ������������������������Ԫ����\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲������޷������Ԫ����\n");
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��Ԫ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
int help(object me)
{
        write(HIC"\n��Ԫ����"NOR"\n");
        write(@HELP

    ��Ԫ���ǽ��Ϲ���Ľ�����ҵı����ڹ���

        ѧϰҪ��
                �����ڹ�10��
HELP
        );
        return 1;
}
