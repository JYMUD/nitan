#include <ansi.h>
// ħ�� motun-tianxia
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "ħ��"; }

int valid_learn(object me)
{        
        if (me->query_skill("chiyou-kuangzhanjue", 1) < 120)
                return notify_fail("����ȿ�ս������㣬�޷���ϰħ�����¡�\n");
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("ħ������ֻ��ħ�̵��ӷ�����ϰ��\n");

        if (me->query_skill("moon-blade", 1) < 150)
                return notify_fail("��Բ���䵶��Ϊ���㣬�޷�������ϰħ�����¡�\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
