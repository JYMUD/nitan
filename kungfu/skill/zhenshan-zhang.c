inherit SKILL;

mapping *action = ({
([      "action": "$Nʹ��һ�С�����ɽ�ӡ����������һ�£����ִ��������Ʒ�����$n��$l",
        "force" : 100,
        "attack": 18,
        "dodge" : 30,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 0,
        "damage_type": "����",
        "skill_name" : "����ɽ��",
]),
([      "action": "$N����Ծ��һʽ��������ʯ����˫�����϶�������$n��$l",
        "force" : 200,
        "attack": 25,
        "dodge" : 40,
        "parry" : 30,
        "damage": 45,
        "lvl"   : 30,
        "damage_type": "����",
        "skill_name" : "������ʯ",
]),
([      "action": "$N˫�ƺ����ĳ���һ�С����������������������ɳ��ʯ��ֱ����$n��$l",
        "force" : 250,
        "attack": 35,
        "dodge" : 50,
        "parry" : 55,
        "damage": 45,
        "lvl"   : 60,
        "damage_type": "����",
        "skill_name" : "��������",
]),
([      "action": "$N˫�������������Ӱ���أ�һ�С�������ġ�����$n$l",
        "force" : 290,
        "attack": 42,
        "dodge" : 70,
        "parry" : 75,
        "damage": 43,
        "lvl"   : 120,
        "damage_type": "����",
        "skill_name" : "�������",
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

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
        level = (int)me->query_skill("zhenshan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����ɽ�Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�����ɽ�ơ�\n");

        if( query("max_neili", me)<450 )
                return notify_fail("�������̫�����޷�����ɽ�ơ�\n");

        if (me->query_skill("strike", 1) < me->query_skill("zhenshan-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ɽ�ơ�\n");

        return 1;
}


int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˣ�����Ϣһ�°ɡ�\n");

        if( query("neili", me)<60 )
                return notify_fail("���������������ɽ�ơ�\n");

        if (me->query_skill("zhenshan-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 50);

        addn("neili", -54, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhenshan-zhang/" + action;
}
