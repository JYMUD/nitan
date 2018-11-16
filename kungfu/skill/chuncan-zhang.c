inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ���Ƽ��������˫�Ƽ�����һ�ŵ����İ�����������$n��$l",
        "force" : 30,
        "dodge" : 15,
        "parry" : 20,
        "damage": 1,
        "lvl" : 0,
        "skill_name" : "�Ƽ����",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ�������˿�����������أ�������ӯ��ͬʱ��$n��$l��ȥ",
        "force" : 55,
        "dodge" : 28,
        "parry" : 25,
        "damage": 3,
        "lvl" : 20,
        "skill_name" : "�����˿",
        "damage_type" : "����"
]),
([      "action" : "$Nͻ��һ�С���˿���ࡹ��˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
        "force" : 70,
        "dodge" : 42,
        "parry" : 38,
        "damage": 9,
        "lvl" : 40,
        "skill_name" : "��˿����",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ��ǧ˿���ơ���˫�������һ����裬�����ѻ���$n��$l��",
        "force" : 91,
        "dodge" : 53,
        "parry" : 49,
        "damage": 12,
        "lvl" : 80,
        "skill_name" : "ǧ˿����",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ���̲ϴ���������������������˫��һ��һ�ͣ����Ƽ򵥣�ȴ��$n�޷�����",
        "force" : 102,
        "dodge" : 61,
        "parry" : 57,
        "damage": 18,
        "lvl" : 120,
        "skill_name" : "�̲ϴ���",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�������Ʒ�������֡�\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("����ڹ���򲻹����޷�ѧ�����Ʒ���\n");

        if( query("max_neili", me)<300 )
                return notify_fail("�������̫�����޷��������Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("��Ļ����Ʒ����̫ǳ��\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chuncan-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ĵ����Ʒ���\n");

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
        level = (int) me->query_skill("chuncan-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
            if (level > action[i-1]["lvl"])
                return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<50 )
                return notify_fail("������������������Ʒ���\n");

        me->receive_damage("qi", 45);
        addn("neili", -25, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chuncan-zhang/" + action;
}