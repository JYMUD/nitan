#include <ansi.h>
// �䵱�� tianwei-zhengqi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "�䵱��"; }

int valid_learn(object me)
{        
        if( query("shen", me)<1000000 )
                return notify_fail("����������������û����������ڻ��޷���������������\n");        
        
        if( query("family/family_name", me) != family_name() )
                return notify_fail("��������ֻ���䵱�ɵ��ӷ�����ϰ��\n");

        if (me->query_skill("taiji-jian", 1) < 150)
                return notify_fail("��̫��������Ϊ���㣬�޷�������ϰ����������\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}