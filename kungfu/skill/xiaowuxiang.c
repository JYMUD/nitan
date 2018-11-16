// xiaowuxiang.c С���๦
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiaoyao-xinfa" ||
               force == "beiming-shengong" ||
               force == "bahuang-gong" ||
               force == "mizong-neigong" ||
               force == "longxiang";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiaowuxiang", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ�����㣬����ѧС���๦��\n");

        if( query("gender", me) == "����" && 
        (int)me->query_skill("xiaowuxiang", 1) > 49)
                return notify_fail("���޸����ԣ����������������������С���๦��\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("С���๦ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"xiaowuxiang/" + func;
}
int help(object me)
{
        write(HIC"\nС���๦��"NOR"\n");
        write(@HELP

    С���๦�˱��������ң�ɵ��ڹ�֮һ����ң�ڹ���Ϊ��ڤ��
�����˻�����Ψ�Ҷ��𹦼�С���๦���֣���ң��������ң�Ӿ�ͨ
��ڤ�񹦣���ɽͯ��ר�ð˻�����Ψ�Ҷ��𹦣���ʦ������̫����
��ˮ�����С���๦��Ϊ�����������Ϊ��ެ��ʦ�Ħ�����ã���
Ϊѩɽ���ڹ���С���๦��΢�����֮�߶�ѩɽ����֮���浶��
�����������־���֮�¡�

        ѧϰҪ��
                �ǳ���Ϊ����ѧ����30�����ϵ�С���๦
                ̫��ѧ����50�����ϵ�С���๦
                �����ڹ�10
                ��Ӧ������
HELP
        );
        return 1;
}
