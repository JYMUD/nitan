#include <ansi.h>
inherit SKILL;

mapping *action = ({

([      "action": "$Nʹһʽ���˼����������$w����΢�񣬻ó�һ���������$n��$l",
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "skill_name" : "�˼��",
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        // ��12T��ͻ
        if( me->query_skill("yinyang-shiertian",1) && !query("thborn/ok", me) )
                return notify_fail("��о����ڵ�������ת�������������ƺ��������ּ��ܡ�\n");
                
        if( query("str", me)<32 )
                return notify_fail("������������㡣\n");

        if( query("int", me)<32 )
                return notify_fail("���������Բ��㡣\n");

        if( query("dex", me)<32 )
                return notify_fail("�����������㡣\n");
                
        if( query("con", me)<32 )
                return notify_fail("��������ǲ��㡣\n");                        
                
        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���������������˼����\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ����̫ǳ�����������˼����\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("��Ľ����������㣬���������˼����\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("�����ѧ�������㣬���������˼����\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("��������ķ���Ϊ���㣬���������˼����\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("renjian-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������˼����\n");
                                                                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("renjian-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if (me->query_skill("renjian-dao", 1) > 180)
                return notify_fail("�˼��������޷��򵥵�ͨ����ϰ������\n");
        return 1;                
}

int difficult_level()
{
        return 30000;
}

string main_skill() { return "lunhui-sword"; } 