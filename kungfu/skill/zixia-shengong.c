// zixia-shengong.c ��ϼ��

#include <ansi.h>;
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
}

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("zixia-shengong", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, t, level;

        level = (int)me->query_skill("zixia-shengong", 1);

        if (level <= 100)
                for (i = 1; i < level / 10; i++)
                        t *= 2;

        if( query("gender", me) == "����" && level>49 )
                return notify_fail("�����޸����ԣ���ϼ�����Ѹ���һ��¥��\n");

        if ((int)me->query_skill("zixia-shengong", 1) >= 45
        &&  (int)me->query_skill("huagong-dafa", 1) >= 100
        &&  (int)me->query_int() < 100 )
                return notify_fail("���ܸ����а���ڹ�ǣ������ϼ��ˮ�����ݣ�������������Ѹ���һ��¥��\n");

        if (level <= 100)
        {
                if( level>10 && query("shen", me)<t*100 )
                        return notify_fail("�����������̫���ˣ��޷������������ϼ�񹦡�\n");
        }
        else
        {
                if( query("shen", me)<(51200+(level-100)*1000) )
                        return notify_fail("�����������̫���ˣ��޷������������ϼ�񹦡�\n");
        }
        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("��ϼ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
int help(object me)
{
        write(HIM"\n��ϼ�񹦣�"NOR"\n");
        write(@HELP

    ��ɽ�����ڹ��������Ƽ��˹�֮�ã��������Ӿ�������������
�Ӻ����������������Ϊ�������������������������������Ϊ��

        ѧϰҪ��
                �����ڹ�10��
                ��Ӧ������
                ̫���޷�ѧ��50�����ϵ���ϼ��
HELP
        );
        return 1;
}
