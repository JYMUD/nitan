// kuihua-xinfa.c �����ķ�
// Last Modified by winder on Mar. 10 2000

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
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-xinfa", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i = (int)me->query_skill("kuihua-xinfa", 1);
        int t = 1, j;
        if (i > 200) i = 200;
        for (j = 1; j < i / 10; j++) t*= 2;
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ�����ķ���\n");
        if( i>10 && query("shen", me)>t*100 )
                return notify_fail("ѧ�����ķ���Ҫ�ĺ���������������������ò���ѽ��\n");
/*
        if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
                return notify_fail("������ͺ¿ţ�����ǵ��ķ�����ѧ�����ķ���ʲ�ᣡ\n");
*/
        if( query("gender", me) != "����" && !query("special_skill/ghost", me) ) 
                return notify_fail("�����񹦣��ӵ��Թ���\n");

        return ::valid_learn(me);
}
int practice_skill(object me)
{
        return notify_fail("�����ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"kuihua-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n�����ķ���"NOR"\n");
        write(@HELP

    �����ķ�Ϊ������̺�ľ�±����ڹ��ķ���

        ѧϰҪ��
                �����ڹ�10��
                ��Ӧ������
                ����ѧ�����ķ��͵����ķ�
HELP
        );
        return 1;
}
