// bahuang-gong.c �˻�����Ψ�Ҷ���
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_enable(string usage) { return usage == "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiaoyao-xinfa" ||
               force == "lingjiu-xinfa" ||
               force == "beiming-shengong" ||
               force == "xiaowuxiang" ||
               force == "wudoumi-shengong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bahuang-gong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if( query("gender", me) == "����" && 
        (int)me->query_skill("bahuang-gong", 1) > 49)
                return notify_fail("���޸����ԣ���������������������İ˻�����Ψ�Ҷ��𹦡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�˻�����Ψ�Ҷ���ֻ����ѧ(learn)������ߡ�\n");
}
string exert_function_file(string func)
{
        return __DIR__"bahuang-gong/" + func;
}

int help(object me)
{
        write(HIC"\n�˻�����Ψ�Ҷ��𹦣�"NOR"\n");
        write(@HELP

    �˻�����Ψ�Ҷ��������չ��������ϵ��ڹ����������ϳ���
��Ϊ�������⹦���������ȴ��һ�����Ĳ���֮����ÿ��ʮ�꣬
��Ҫ���ϻ�ͯһ�Ρ�

        ѧϰҪ��
                ���չ�����
                �����ڹ�10��
HELP
        );
        return 1;
}
