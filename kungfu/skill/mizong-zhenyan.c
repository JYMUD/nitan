#include <ansi.h>
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "������"; }

int valid_learn(object me)
{        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("��������ֻ�ܴ����µ��ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}