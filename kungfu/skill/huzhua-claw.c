// huzhua-gong.c ��צ��

#include <combat.h>
#include <ansi.h>


inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N˫צһ�ţ�б���������̤�й���һʽ���ڻ����ġ�������Ѹ�磬�񲻿ɵ�����$n�ؿ����Ĺ�ȥ",
        "force" : 100,
        "attack": 30,
        "dodge" : 25,
        "parry" : 5,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "�ڻ�����" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N��������˫�ۻ��ţ�����һչ��һ�С��ͻ���ɽ����˫צ���ɣ����϶��£�����$n����",

        "force" : 120,
        "attack": 41,
        "dodge" : 30,
        "parry" : 5,
        "damage": 30,
        "lvl"   : 10,
        "skill_name" : "�ͻ���ɽ" ,
        "damage_type" : "����"
]),
([      "action": "$N�ù����ƣ�����һʽ��������ʳ�����������ϣ��缲��㣬�۵�$n��ǰ������$n���������Ѩ",
        "force" : 120,
        "attack": 55,
        "dodge" : 45,
        "parry" : 30,
        "damage": 65,
        "lvl"   : 40,
        "skill_name" : "������ʳ" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N����������������Х������һʽ����Х��ɽ������$nһ�֮�䣬�������ǰ���Ͱ�$n˫��",
        "force" : 170,
        "attack": 64,
        "dodge" : 36,
        "parry" : 18,
        "damage": 70,
        "lvl"   : 60,
        "skill_name" : "��Х��ɽ" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N΢΢һ����һ�С�����β������Ȧ��$n��󣬼���Ʈ�磬ֱ��$n���ץȥ",
        "force" : 180,
        "attack": 77,
        "dodge" : 58,
        "parry" : 5,
        "damage": 80,
        "lvl"   : 80,
        "skill_name" : "����β" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N��Ӱ���Σ�����ֱ�ϣ�����һʽ���޻����֡����������ߣ�������ת����$n����Ϯȥ",
        "force" : 220,
        "attack": 87,
        "dodge" : 42,
        "parry" : 22,
        "damage": 95,
        "lvl"   : 100,
        "skill_name" : "�޻�����" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N˫��һ�ţ�һԾ���𣬰����ʹ��һʽ�����ڻ�Ծ����Я������֮�ƣ����׼л�֮������$nץȥ",
        "force" : 250,
        "attack": 85,
        "dodge" : 40,
        "parry" : 29,
        "damage": 110,
        "lvl"   : 120,
        "skill_name" : "���ڻ�Ծ" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N����һ����һʽ�������������ù��Է����ƣ���צ��Ȼ̽����ץ��$n����",
        "force" : 300,
        "attack": 96,
        "dodge" : 75,
        "parry" : 45,
        "damage": 107,
        "lvl"   : 140,
        "skill_name" : "��������" ,
        "damage_type" : "ץ��"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "qinna-shibada"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����צ��������֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�ѧ��צ����\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("�������̫�����޷�����צ����\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhua-claw"))
                return notify_fail("��Ļ���צ�����ˮƽ���ޣ��޷���������Ļ�צ����\n");

        if ((int)me->query_skill("jimie-zhua", 1) < (int)me->query_skill("huzhua-claw"))

                return notify_fail("��ļ���צ���ˮƽ���ޣ��޷���������Ļ�צ����\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhua-claw", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("����������ϰ��\n");

        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<80 )
                return notify_fail("���������������צ����\n");

        if ((int)me->query_skill("jiemie-zhua", 1) < (int)me->query_skill("huzhua-claw", 1))
                return notify_fail("��ļ���צ���ˮƽ���ޣ��޷���������Ļ�צ����\n");

        me->receive_damage("qi", 60);
        addn("neili", -75, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huzhua-claw/" + action;
}
