#include <ansi.h>
// ��ɽ�� jianyi
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "��ɽ��"; }

int valid_learn(object me)
{        
        if (me->query_skill("zixia-shengong", 1) < 120)
                return notify_fail("����ϼ�񹦻���㣬�޷���ϰ���⡣\n");
        
        if( query("family/family_name", me) != family_name() && query("family/family_name", me) != "��ɽ����" )
                return notify_fail("����ֻ�ܻ�ɽ�ɵ��ӷ�����ϰ��\n");

        if (me->query_skill("huashan-sword", 1) < 150)
                return notify_fail("�㻪ɽ������Ϊ���㣬�޷�������ϰ���⡣\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}
