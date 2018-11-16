// dongyang-dao ���󵶷�

inherit SKILL;

mapping *action = ({
([      "action": "$N���һ��������$wֱ������������һ���",
        "force" : 40,
        "attack": 30,
        "dodge" : 32,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 95,
        "damage_type" : "����"
]),
([      "action": "$NͻȻ���У�����$n��$l",
        "force" : 80,
        "attack": 35,
        "dodge" : 33,
        "parry" : 8,
        "damage": 110,
        "lvl"   : 10,
        "damage_type" : "����"
]),
([      "action": "$N���е�$w�����任�����������ͻȻֱ��$n��$l",
        "force" : 110,
        "attack": 40,
        "dodge" : 37,
        "parry" : 12,
        "damage": 110,
        "lvl"   : 30,
        "damage_type" : "����"
]),
([      "action": "$N���е�$w��Ȼ��ת������һ�ŵ�Ӱ��ֱ��$n",
        "force" : 130,
        "attack": 45,
        "dodge" : 45,
        "parry" : 15,
        "damage": 125,
        "lvl"   : 50,
        "damage_type" : "����"
]),
([      "action": "$N����$wһ����˫�ֳ����������У�����$n��$l",
        "force" : 140,
        "attack": 40,
        "dodge" : 47,
        "parry" : 18,
        "damage": 125,
        "lvl"   : 80,
        "damage_type" : "����"
]),
([      "action": "$N��Хһ�������е�$w��ס�Ļζ����������ѵ�����$n",
        "force" : 180,
        "attack": 45,
        "dodge" : 55,
        "parry" : 25,
        "damage": 135,
        "lvl"   : 100,
        "damage_type" : "����"
]),
([      "action": "$Nһת���ѱ���ȫ������$n��ͻȻ˫��һת��$w��$N������˳���",
        "force" : 200,
        "attack": 45,
        "dodge" : 55,
        "parry" : 31,
        "damage": 140,
        "lvl"   : 120,
        "damage_type" : "����"
]),
([      "action": "$N��ȻǰϮ������$w����һ����â�����Ĵ���$n",
        "force" : 210,
        "attack": 50,
        "dodge" : 60,
        "parry" : 33,
        "damage": 160,
        "lvl"   : 150,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("dongyang-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ķ��󵶷���\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("dongyang-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ķ��󵶷���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("dongyang-dao",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<75 )
                return notify_fail("����������������󵶷���\n");

        if( query("neili", me)<55 )
                return notify_fail("����������������󵶷���\n");

        me->receive_damage("qi", 60);
        addn("neili", -42, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dongyang-dao/" + action;
}