#include <ansi.h>
// ��Ĺ�� jueqing-quyu
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "��Ĺ��"; }

int valid_learn(object me)
{        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("̫������ֻ�ܹ�Ĺ�ɵ��ӷ�����ϰ��\n");

        if (me->query_skill("yunv-xinfa", 1) < 200)
                return notify_fail("����Ů�ķ�����㣬�޷�̫�����顣\n");

        return 1;
}

int difficult_level()
{
        return 6000;
}
