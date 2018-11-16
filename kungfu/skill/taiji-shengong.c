// taiji-shengong.c ̫����

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("taiji-shengong", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("taiji-shengong", 1);


        if( query("gender", me) == "����" && lvl>49 )
                return notify_fail("���޸����ԣ����������������������̫���񹦡�\n");

        if( query("class", me) == "bonze" )
                return notify_fail("̫���񹦽����������ϣ���Υ��������徻֮�⣬"
                        + RANK_D->query_respect(me) + "���޴˹������������\n");

        if( lvl>10 && query("shen", me)<lvl*100
             && me->query_skill("taoism", 1) < 100)
                return notify_fail("�����������̫���ˡ�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("̫����ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"taiji-shengong/" + func;
}

int help(object me)
{
        write(HIC"\n̫���񹦣�"NOR"\n");
        write(@HELP

    ̫�������䵱����֮�أ��������塹�����项����Բ������
ͨ��������ϰ�䵱�ɸ��ָ����书�ĸ������䵱�������̫����
�͵�ѧ�ķ�������������������������֮��Ч��

        ѧϰҪ��
                ���в���ѧ
                ̫���޷�����50�����ϵ�̫����
                �����ڹ�10��
                ��Ӧ������
HELP
        );
        return 1;
}
