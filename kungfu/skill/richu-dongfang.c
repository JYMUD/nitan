#include <ansi.h>
// �ճ����� richu-dongfang
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "�������"; }

int valid_learn(object me)
{        
        if (me->query_skill("riyue-jian", 1) < 30)
                return notify_fail("�����½������㣬�޷���ϰ�ճ�������\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("�ճ�����ֻ��������̵��ӷ�����ϰ��\n");

        if (me->query_skill("riyue-xinfa", 1) < 
            me->query_skill("richu-dongfang", 1) * 60 /100)
                return notify_fail("�������ķ���Ϊ���㣬�޷�������ϰ�ճ�������\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
