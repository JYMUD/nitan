inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ����ů������������$w�������Һ�ɨ����$n��$l",
        "force" : 60,
        "attack": 5,
        "dodge" : 10,
        "damage": 33,
        "lvl" : 0,
        "damage_type":  "����"
]),
([      "action":"$N̤��һ�������������ס�������$w���������һ���������$n��$l",
        "force" : 120,
        "attack": 15,
        "dodge" : 20,
        "damage": 51,
        "lvl" : 40,
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һ�С������ɪ����ббһ�������ó�������$n��$l",
        "force" : 150,
        "attack": 64,
        "dodge" : 25,
        "damage": 85,
        "lvl" : 80,
        "damage_type":  "����"
]),
([      "action":"$N����$w����������Ȧ��һʽ���������ǡ���һ���������$n��$l",
        "force" : 180,
        "attack": 95,
        "dodge" : 30,
        "damage": 125,
        "lvl" : 120,
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻵����޷�ѧϰ�ļ�������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ�ļ�������\n");

        if( query("neili", me)<200 )
                return notify_fail("�������̫��޷�ѧϰ�ļ�������\n");

        if (me->query_skill("sword", 1) < me->query_skill("siji-jianfa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������ļ�������\n");

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
        level = (int) me->query_skill("siji-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<150 )
                return notify_fail("��������������ļ�������\n");

        if( query("neili", me)<150 )
                return notify_fail("��������������ļ�������\n");

        me->receive_damage("qi", 125);
        addn("neili", -125, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"siji-jianfa/" + action;
}
