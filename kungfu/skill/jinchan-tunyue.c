#include <ansi.h>
// ������� jinchan-tunyue
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "ŷ������"; }

int valid_learn(object me)
{        
        if (me->query_skill("hamagong", 1) < 30)
                return notify_fail("���󡹦����㣬�޷���ϰ������¡�\n"); 
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("�������ֻ��ŷ�����ҵ��ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
