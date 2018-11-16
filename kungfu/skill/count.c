// count.c ��������
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

int is_fmsk() { return 1; } 
string type() { return "knowledge"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
        int gift, mat;

        gift = 35;
        mat = 300;

        if( query("family/family_name", me) == "�һ���" )
        {
                gift = 30;
                mat = 200;
        }

        if( !query("family/family_name", me) || 
            query("family/family_name", me) != "�һ���" )
                return notify_fail("�㲻���һ������ӣ���������������Եİ��\n");

        if( query("int", me)<gift )
                return notify_fail("����������Բ��㣬��������������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < mat)
                return notify_fail("�������֪ʶ̫��޷�����������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("�������֪ʶ���ޣ��޷�������µ��������ԡ�\n");

        if( me->query_skill("zuoyou-hubo",1) && !query("special_skill/capture", me) )
                return notify_fail("����ܵ����һ�������֮��Ӱ�죬��������������Եİ��\n");

        return 1;
}


int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}
int help(object me)
{
        write(HIC"\n�������ԣ�"NOR"\n");
        write(@HELP

    �һ������ӿ���ƾ�˼��ܲ�֪���Ŀǰ���ڵ�λ�á�����ͨ��
�Ķ�����ͼ���������顷��ߡ�
    ��help location��

        ѧϰҪ��
                ����д��50��
                ��Ϊ��ҩʦ�մ�����
HELP
        );
        return 1;
}
