// lamaism.c �����ķ�
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("lamaism", 1);

        if( query("class", me) != "bonze" && query("family/family_name", me) != "���ϻ���" && lvl>39 )
                return notify_fail("��δ����ţ���Ե���ϣ��޷������޳������񷨡�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����ķ�ֻ�ܿ�ѧ(learn)����ߡ�\n");
}

int help(object me)
{
        write(HIC"\n�����ķ���"NOR"\n");
        write(@HELP

    �����ķ���ѩ�������ķ������Գ������顣

        ѧϰҪ��
                ����ѧ���ڡ����Һͻ�ɽ���ķ��Լ����޶���
HELP
        );
        return 1;
}
