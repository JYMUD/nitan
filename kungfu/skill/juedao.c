#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N����һ��������������$w����$n�������ڿ��л���һ������",
        "force"  : 20,
        "attack" : 50,
        "dodge"  : 10,
        "parry"  : 30,
        "lvl"    : 0,
        "damage" : 30,
        "damage_type" : "����",
]),
([      "action" : "$N����һ�������⻮��$n����������֮��",
        "force"  : 40,
        "attack" : 65,
        "dodge"  : 10,
        "parry"  : 45,
        "lvl"    : 10,
        "damage" : 50,
        "damage_type" : "����",
]),
([      "action" : "$N���ݲ��ȣ�ת��������$w��������$n����",
        "force"  : 80,
        "attack" : 80,
        "dodge"  : 10,
        "parry"  : 55,
        "lvl"    : 20,
        "damage" : 60,
        "damage_type" : "����",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("blade", 1) < 10 )
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���ϰ����\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("juedao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ľ���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}


mapping query_action(object me, object weapon) 
{ 
      int i, level; 
      level = (int) me->query_skill("juedao", 1); 
      for (i = sizeof(action); i > 0; i--) 
              if (level > action[i-1]["lvl"]) 
                      return action[NewRandom(i, 20, level / 5)]; 
    
} 

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<20 )
                return notify_fail("��������������޷�������ϰ��\n");

        me->receive_damage("qi", 15);

        return 1;
}
