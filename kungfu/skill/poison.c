// poison.c ��������
// Last Modified by winder on Mar. 10 2000
// Modified by Java Mar.1998

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "poison"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( query("character", me) == "��������" && 
            query("family/family_name", me) != "�������" )
                return notify_fail("�����а��룺�����¹������䣬ѧʲô������\n");

        return 1;
}
/*
void skill_improved(object me)
{
        if ((me->query_skill("poison",1) == 50) ||
                (me->query_skill("poison",1) == 60) ||
                (me->query_skill("poison",1) == 70) ||
                (me->query_skill("poison",1) == 80) ||
                (me->query_skill("poison",1) == 90) ||
                (me->query_skill("poison",1) >= 100))
        {
                tell_object(me, "�����ڵĶ��ʿ�ʼ���������ˣ�������ɢ���ˡ�\n");
                me->apply_condition("poison_sandu",1000);
        }
}
*/
int practice_skill(object me)
{
        return notify_fail("��������ֻ�ܿ�ѧϰ����ߡ�\n");
}
int help(object me)
{
        write(HIC"\n����������"NOR"\n");
        write(@HELP

    ���޵����¶��ؾ��书���¶���Ч���ͻ��������ĸߵ��кܴ�
�Ĺ�ϵ�������ڶ��ط�������ʱ��������ɢ����

        ѧϰҪ��
                �������ɵ��ķ�����ѧ
                �������ɵ��Ӳ���ѧ
HELP
        );
        return 1;
}
