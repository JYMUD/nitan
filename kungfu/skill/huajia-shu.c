#include <ansi.h>
// ȫ�滯���� huajia-shu
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "ȫ���"; }

int valid_learn(object me)
{        
        if (me->query_skill("quanzhen-jian", 1) < 30)
                return notify_fail("��ȫ�潣������㣬�޷���ϰ��������\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("������ֻ��ȫ��̵��ӷ�����ϰ��\n");

        if (me->query_skill("taoism", 1) < 
            me->query_skill("huajia-shu", 1) * 60 /100)
                return notify_fail("���ѧ�ķ���Ϊ���㣬�޷�������ϰ��������\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
