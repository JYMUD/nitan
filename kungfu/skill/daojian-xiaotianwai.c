#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name1() { return "�������"; }
string family_name2() { return "��ԭ���"; }

int valid_learn(object me)
{        

        if( query("family/family_name", me) != family_name1() && query("family/family_name", me) != family_name2() )
                return notify_fail("����Х����ֻ�ܺ��ҵ��ӻ���ҵ��ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}