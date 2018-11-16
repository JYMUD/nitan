// hunyuan-yiqi.c ���� ��Ԫһ����

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }
int query_neili_improve(object me)
{
        int lvl;

        if( query("sex", me) )
                return 0;

        lvl = (int)me->query_skill("hunyuan-yiqi", 1);
        return lvl * lvl * 15 * 21 / 100 / 200;
}

int valid_force(string force)
{
/*
        return force == "yijinjing" ||
               force == "taiji-shengong" ||
               force == "wudang-xinfa" ||
*/
        return 1;
}
int valid_learn(object me)
{
        int i, nb, nf, nh, ns, ts;

        nb = (int)me->query_skill("buddhism", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("hunyuan-yiqi", 1);
        ns=query("guilty", me);

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if( query("couple/have_couple", me) )
                return notify_fail("�㳾Եδ�ˣ��޷���ѧϰ��Ԫһ������\n");

        if( query("sex/number", me) )
                return notify_fail("���Ѿ�����ɫ�䣬�޷���ѧϰ��Ԫһ������\n");

        if( query("gender", me) != "����" )
                return notify_fail("���ͯ��֮�壬������ϰ��Ԫһ������\n");

        if ( nb < 100 && nb <= nh )
                return notify_fail("��������ķ���Ϊ�������޷���������Ļ�Ԫһ������\n");

        if ( nf < 10)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����Ԫһ������\n");

        if ( ns > 0 )
                return notify_fail("���ŷ�ɮ�����䣬�޷���������Ļ�Ԫһ������\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��Ԫһ����ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"hunyuan-yiqi/" + func;
}

int help(object me)
{
        write(HIC"\n��Ԫһ������"NOR"\n");
        write(@HELP

    ��Ԫһ����Ϊ�����ɱ����ڹ���

        ѧϰҪ��
                �����ڹ�10��
                ������ɫ���ͯ��֮��
                �����ķ���Ϊ�����ڻ�Ԫһ����
                ������������
HELP
        );
        return 1;
}
