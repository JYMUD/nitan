// taoism.c ��ѧ�ķ�
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

        lvl = (int)me->query_skill("taoism", 1);

        if( query("gender", me) == "����" && lvl>19 )
                return notify_fail("�����һ�������������Ժ���ԭ����û������֮\n"
                           "�����޷��������������仯֮����\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��ѧ�ķ�ֻ�ܿ�ѧϰ����ߡ�\n");
}

int help(object me)
{
        write(HIC"\n��ѧ�ķ���"NOR"\n");
        write(@HELP

    ̫�ϵ��洫�µĵ���������ǧ�����̺��Ĳ�������ķ���
    ��Ѱ�ҵ��¾��Ķ���

        ѧϰҪ��
                �������ķ��������ķ�����������������ͻ����������ܼ�ѧ
HELP
        );
        return 1;
}
