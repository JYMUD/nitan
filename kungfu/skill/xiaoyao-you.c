#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "��ң��"; }

int valid_learn(object me)
{       
        if (me->query_skill("lingbo-weibu", 1) < 150)
                return notify_fail("���貨΢��������㣬�޷���ϰ��ң�Ρ�\n"); 

        if( query("family/family_name", me) != family_name() )
                return notify_fail("��ң��ֻ����ң�ɵ��ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
