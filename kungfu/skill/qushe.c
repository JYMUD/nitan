#include <ansi.h>
// ŷ������ ����
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "ŷ������"; }

int valid_learn(object me)
{        
        if (me->query_skill("jiuyin-hamagong", 1) < 150)
                return notify_fail("�������󡹦����㣬�޷���ϰ���ߡ�\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("����ֻ��ŷ�����ҵ��ӷ�����ϰ��\n");

        if (me->query_skill("baituo-michuan", 1) < 150)
                return notify_fail("������ش��ȼ����㣬�޷�������ϰ���ߡ�\n");

        if (me->query_skill("training", 1) < 150)
                return notify_fail("��Ԧ�����ȼ����㣬�޷�������ϰ���ߡ�\n");
        
        return 1;
}

int difficult_level()
{
        return 2000;
}