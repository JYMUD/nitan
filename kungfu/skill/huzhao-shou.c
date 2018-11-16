inherit SKILL;

mapping *action = ({
([      "action": "�ں��������У�$Nʹһ�С����ڶ�ʳ����˫���繳��ꫣ�����$n��$l",
        "force" : 60,
        "dodge" : 17,
        "parry" : 1,
        "damage": 1,
        "damage_type" : "ץ��",
        "skill_name" : "���ڶ�ʳ",
]),
([      "action": "$N����һԾ���������ϣ�ʹ��һ�С�������ʳ��������ֱֱץ��$n��$l",
        "force" : 80,
        "dodge" : 20,
        "parry" : 5,
        "damage": 3,
        "damage_type" : "ץ��",
        "skill_name" : "������ʳ",
]),
([      "action": "$N˫��ƽ�죬ʮָ΢΢���¶�����һ�С�ɽ�����ѡ�����$n��$l",
        "force" : 120,
        "dodge" : 32,
        "parry" : 10,
        "damage": 5,
        "damage_type" : "ץ��",
        "skill_name" : "ɽ������",
]),
([      "action": "$Nʹ��һ�С�ҹ�ڷ�ߡ���������Ϣ��������$n��ǰ���͵�һצ����ץ��$n��$l",
        "force" : 132,
        "dodge" : 38,
        "parry" : 19,
        "damage": 5,
        "damage_type" : "ץ��",
        "skill_name" : "ҹ�ڷ��",
]),
([      "action": "$N˫��ƽ����ǰ�����ֻ�ס���ţ�һ�С����Ϲǡ���������$n��$l",
        "force" : 137,
        "dodge" : 41,
        "parry" : 21,
        "damage": 7,
        "damage_type" : "ץ��",
        "skill_name" : "���Ϲ�",
]),
([      "action": "$Nʹ�������ֻ�Х�����ͺ�һ����˫�ֻ���Ϊצ��һǰһ��ץ��$n��$l",
        "force" : 143,
        "dodge" : 49,
        "parry" : 22,
        "damage": 9,
        "damage_type" : "ץ��",
        "skill_name" : "���ֻ�Х",
]),
([      "action": "$Nʹ���������̶�����˫צ����������׼$n��$l����ץ��",
        "force" : 151,
        "dodge" : 58,
        "parry" : 38,
        "damage": 15,
        "damage_type" : "ץ��",
        "skill_name" : "�����̶�",
])
});

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("���Ѿ������˰ٻ���ȭ�������ٵ���ѧϰ�ˡ�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����צ�ֱ�����֡�\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhao-shou", 1))
                return notify_fail("��Ļ���צ������㣬�޷���������Ļ�צ�֡�\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "claw" || usage=="parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhao-shou",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("����������������Ϣһ�������ɡ�\n");

        if( query("neili", me)<80 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("qi", 80);
        addn("neili", -50, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huzhao-shou/" + action;
}
