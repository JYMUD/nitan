#include <ansi.h>
// ������ renwang-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "���ϻ���"; }

int valid_learn(object me)
{        
        if (me->query_skill("sun-finger", 1) < 30)
                return notify_fail("��һ��ָ����㣬�޷���ϰ��������\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("������ֻ�ܶ��ϻ�����ӷ�����ϰ��\n");

        if (me->query_skill("kurong-changong", 1) < 
            me->query_skill("renwang-jing", 1) * 60 /100)
                return notify_fail("�����������Ϊ���㣬�޷�������ϰ��������\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
