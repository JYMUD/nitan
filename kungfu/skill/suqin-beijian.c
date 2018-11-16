#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N����Ծ������$w��ӣ�һ�С�������ʿ����ն��$n��",
        "force"  : 60,
        "attack" : 35,
        "parry"  : 10,
        "dodge"  : 30,
        "damage" : 17,
        "lvl"    : 0,
        "skill_name" : "������ʿ",
        "damage_type" : "����"
]),
([      "action" : "$N����$w�����������Σ�һ�С���ڹ��ԡ�����$n���ұ����ն��",
        "force"  : 71,
        "attack" : 45,
        "parry"  : 22,
        "dodge"  : 45,
        "damage" : 24,
        "lvl"    : 20,
        "skill_name" : "��ڹ���",
        "damage_type" : "����"
]),
([      "action" : "$N����һ��������һԾ����һ�С���н��������������$n�̳�����",
        "force"  : 82,
        "attack" : 51,
        "parry"  : 18,
        "dodge"  : 53,
        "damage" : 33,
        "lvl"    : 40,
        "skill_name" : "��н����",
        "damage_type" : "����"
]),
([      "action" : "$N���쳤Х��б����ǰ��һ�С�����Ϊ�᡹��$w����ֱ��������$n��$l",
        "force"  : 112,
        "attack" : 58,
        "parry"  : 20,
        "dodge"  : 52,
        "damage" : 45,
        "lvl"    : 60,
        "skill_name" : "����Ϊ��",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("��������������޷���ϰ���ر�����\n");

        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("��Ļ����������̫ǳ���޷���ϰ���ر�����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("suqin-beijian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������ر�����\n");

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

        level = (int) me->query_skill("suqin-beijian",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<40 )
                return notify_fail("����������������ر�����\n");

        if( query("neili", me)<30 )
                return notify_fail("����������������ر�����\n");

        me->receive_damage("qi", 33);
        addn("neili", -26, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suqin-beijian/" + action;
}