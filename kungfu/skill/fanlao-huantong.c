#include <ansi.h>
// ���� fanlao-huantong
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "���չ�"; }

int valid_learn(object me)
{        
        if (me->query_skill("bahuang-gong", 1) < me->query_skill("fanlao-huantong", 1))
                return notify_fail("��˻�����Ψ�Ҷ��𹦻���㣬�޷���ϰ���ϻ�ͯ����\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("���ϻ�ͯ��ֻ�����չ����ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}