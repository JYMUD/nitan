// mahayana.c ������͹�
//Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( query("shen", me)<0 )
                return notify_fail("���а��̫�أ��޷�����������͹���\n");

        return 1;
}

void skill_improved(object me)
{
        if ((int)me->query_skill("mahayana", 1) == 120 &&
            !query("sl_gift/mhyn", me) && query("gender", me) != "����" )
        {
                addn("dex", 1, me);
                set("sl_gift/mhyn", 1, me);
                tell_object(me, HIM "\n��Ĵ�����͹�ѧ�����ɣ�������������\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n������͹���"NOR"\n");
        write(@HELP

    �������ز�ϲ�����������������˳���������������������Ǳ
�ܣ�����Ч�̶���ȡ���ڷ���Ϊ����������͹��ĵȼ���������
���޿��ڶ�������ʹ������jingzuo����help jingzuo��

        ѧϰҪ��
                ��Ӧ���ټ�ʮ��ׯ
                ����ѧ�����ķ���������ڽ��ķ�
HELP
        );
        return 1;
}
