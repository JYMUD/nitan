// kurong-changong.c ��������

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force)
{
        return 1;
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa"  ||
               force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
            int lvl;

            lvl = (int)me->query_skill("kurong-changong", 1);
            return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int nb, nk;
        int lvl = (int)me->query_skill("kurong-changong", 1);

        if( query("gender", me) == "����" && lvl>49 )
                return notify_fail("���޸����ԣ���������������������Ŀ���������\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        nb = (int)me->query_skill("buddhism", 1);
        nk = (int)me->query_skill("kurong-changong", 1);

        if (nb < 120 && nb <= nk)
                return notify_fail("��������ķ���Ϊ�������޷���������Ŀ���������\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"kurong-changong/" + func;
}


int help(object me)
{
        write(HIC"\n����������"NOR"\n");
        write(@HELP

    �г��޳���˫�����٣��ϱ��������Ǽٷǿգ�
    �����湦�������¿��ٳ��Ͼ��ô˼����ഫ����Ĳ�������˫
��֮�����𣬴����˷ǿݷ��١��Ǽٷǿյ���߾��磬�������ӱ�
�Դ�Ϊ����֮�������ο�������Ϊ��������֮���ɡ�
    Ϊ���ϴ���μҵı����ڹ���

        ѧϰҪ��
                �����ڹ�10��
                ������̫��
HELP
        );
        return 1;
}
