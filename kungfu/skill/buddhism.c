// buddhism.c �����ķ�
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
        if( query("guilty", me)>0 )
                return notify_fail("���ŷ�ɮ�����䣬����֮��̫�أ��޷����������ķ���\n");

        if( query("class", me) != "bonze" && me->query_skill("buddhism",1) >= 350 )
                return notify_fail("�㷲���أ������ң���ô�ܼ������������ķ���\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����ķ�ֻ�ܿ�ѧ(learn)����ߡ�\n");
}

void skill_improved(object me)
{
        if( me->query_skill("buddhism",1) == 120 && !query("sl_gift/int", me) )
        {
                addn("int", 1, me);
                set("sl_gift/int", 1, me);
                tell_object(me, HIM "\n��������ķ�ѧ�����ɣ���������������\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n�����ķ���"NOR"\n");
        write(@HELP

    ���ֵ��ӵı��޿Ρ������ɴ�����ʦ��Ħ�����������ڴ�ʦ��
���Ƕ������ڵ�һ�棬���ֵ�����Ӧ����ϰ���ڣ����з�Ϊ�Ρ�
��ϻ�Ԫһ�������Գ����������ӵĳ̶�ȡ���ڻ�Ԫһ����������
�ķ��ȼ��ĸߵ͡�

        ѧϰҪ��
                �����ǳ������޷�����
                ������ķ�����������ܼ�ѧ
HELP
        );
        return 1;
}
