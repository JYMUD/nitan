// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N����$wð������������ৡ���һ�����治��س�$n��$l����",
        "force" : 20,
        "dodge" : 10,
        "parry" : 25,
        "damage": 5,
        "lvl"   : 0,
        "skill_name"  : "ͣ����·",
        "damage_type" : "����"
]),
([      "action": "$N�����³������Ӳ�ס��ת������$w����һ�ŵ�����$n��$l����ȥ",
        "force" : 30,
        "dodge" : 30,
        "parry" : 40,
        "damage": 10,
        "lvl"   : 20,
        "skill_name"  : "ͯ�ӹһ�",
        "damage_type" : "����"
]),
([      "action": "$N����$wһ�ӣ���ʽ�󿪴��أ�ֻ��˲ʱ��㵶�⳯$n��$l����ȥ",
        "force" : 40,
        "dodge" : 35,
        "parry" : 45,
        "damage": 15,
        "lvl"   : 40,
        "skill_name"  : "�ƴ�����",
        "damage_type" : "����"
]),
([      "action": "$N���е�$w����ƫ�棬��ת���䣬�����ޱ�һ�п���$n��$l",
        "force" : 60,
        "dodge" : 45,
        "parry" : 45,
        "damage": 20,
        "lvl"   : 60,
        "skill_name"  : "���ż�ɽ",
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("���������Ϊ������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("moshen-daofa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ħ�񵶷���\n");

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
        level = (int) me->query_skill("moshen-daofa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<60 )
                return notify_fail("�������������ħ�񵶷���\n");

        if( query("neili", me)<60 )
                return notify_fail("�������������ħ�񵶷���\n");

        me->receive_damage("qi", 45);
        addn("neili", -43, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-daofa/" + action;
}