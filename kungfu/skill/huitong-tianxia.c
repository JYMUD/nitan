#include <ansi.h>
// 
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "Ľ������"; }

int valid_learn(object me)
{        
        if (me->query_skill("canhe-zhi", 1) < 300)
                return notify_fail("��κ�ָ����㣬�޷���ϰ��ͨ���¡�\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("��ͨ����ֻ��Ľ�����ҵ��ӷ�����ϰ��\n");

        if (me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("����ѧ�������㣬�޷���ϰ��ͨ���¡�\n");

        return 1;
}

int difficult_level()
{
        return 8000;
}