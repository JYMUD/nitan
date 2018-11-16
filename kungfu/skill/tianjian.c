
#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N�������أ��͵ش���$n����ʽ��Ϊ����",
        "force"  : 20,
         "attack" : 40,
        "dodge"  : 20,
        "parry"  : 20,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type": "����"
]),
([      "action" : "$N����$w�ڰ�ջ���һ����Բ����Ȼ�佣��һ����$w�Ѵ���$n$l",
        "force"  : 40,
        "attack" : 60,
        "dodge"  : 20,
        "damage" : 40,
        "lvl"    : 10,
        "damage_type": "����"
]),
([      "action" : "$N�������ֻ����ս�������$w���������۾�һ�����$n",
        "force"  : 60,
        "attack" : 80,
        "dodge"  : 15,
        "damage" : 50,
        "lvl"    : 20,
        "damage_type": "����"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("��Ļ����������̫ǳ���޷�ѧϰ�׻ƽ�����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tianjian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������׻ƽ�����\n");

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
        level = (int) me->query_skill("tianjian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<10 )
                return notify_fail("��������������׻ƽ�����\n");

        me->receive_damage("qi", 5);        

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianjian/" + action;
}


void skill_improved(object me)   
{
        int lvl;

        lvl = me->query_skill("tianjian", 1);  
        if( lvl >= 30 &&  
            !query("can_perform/tianjian/lian", me) )   
        {
                tell_object(me, HIC "��ͨ�����콣��" HIR "������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/tianjian/lian", 1, me);  
                me->improve_skill("martial-cognize", 1500000);
        }
}

