#include <ansi.h>
// ���� ���� jingxin
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "������"; }

int valid_learn(object me)
{        
        if (me->query_skill("huifeng-jian", 1) < 30)
                return notify_fail("��ط����������㣬�޷���ϰ���ġ�\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("����ֻ�ܶ����ɵ��ӷ�����ϰ��\n");

        if (me->query_skill("jingxin", 1) / 2 > me->query_skill("mahayana", 1))
                return notify_fail("�������͹��ȼ����㣬�޷�������ϰ���ġ�\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}