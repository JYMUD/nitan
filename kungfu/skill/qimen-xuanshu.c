#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "�һ���"; }

int valid_learn(object me)
{        
        
        if (me->query_skill("qimen-wuxing", 1) < 100)
                return notify_fail("�������������յò�����\n");

        if( query("family/family_name", me) != family_name() )
                return notify_fail("��������ֻ���һ������ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}