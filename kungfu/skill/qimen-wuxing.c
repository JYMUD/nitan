// qimen-wuxing ��������
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage=="taoism"; }
int practice_skill(object me)
{
        return notify_fail("���������ܿ�ѧ(learn)����ߡ�\n");
}
int valid_learn(object me)
{
        if( (int)me->query_skill("taoism") < 10	)
                return notify_fail("��ĵ�����Ϊ����������޷�ѧϰ�������С�\n");
        if ((int)me->query_skill("mathematics", 1) < 200)
                return notify_fail("�������֪ʶ̫��޷�����������еİ��\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("qimen-wuxing", 1))
                return notify_fail("�������֪ʶ���ޣ��޷�������µ��������С�\n");

        return 1;
}

string conjure_magic_file(string spell)
{
        return __DIR__ + "qimen-wuxing/" + spell;
}
int help(object me)
{
        write(HIC"\n�������У�"NOR"\n");
        write(@HELP


    �Ƕ����һ����Ķ��Ź����ഫ�һ�����Ȼ�ش����⣬�˼���
����������ȴ�ǼҴ�Ԩ���������������о��ú���������Ź���
�������һ����Ĳ�����Ϳ��԰ڳ����������󣬰ѵ����������ڡ�

    array somebody  �ڲ����������£����Զ�ĳ�˲���ʹ��
�������ڡ�

    �����Ķ����׾���ϵ���鼮��ߡ�


        ѧϰҪ��
                ����ͬʱ��ϰ���һ���֮��
HELP
        );
        return 1;
}
