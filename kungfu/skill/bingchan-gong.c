#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "������"; }

int valid_learn(object me)
{        
        if (me->query_skill("sanyin-wugongzhao", 1) < 30)
                return notify_fail("���������צ����㣬�޷���ϰ���Ϲ���\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("���Ϲ�ֻ�������ɵ��ӷ�����ϰ��\n");

        if (me->query_skill("bingchan-gong", 1) / 2 > me->query_skill("xingxiu-qishu", 1)) 
                return notify_fail("�����������ȼ����㣬�޷�������ϰ���Ϲ���\n"); 

        return 1;
}

int difficult_level()
{
        return 2000;
}