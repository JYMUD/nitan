inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nʹһʽ���˼����������$w����΢�񣬻ó�һ���������$n��$l",
        "force" : 190,
        "attack": 130,
        "dodge" : 110,
        "parry" : 115,
        "damage": 115,
        "lvl"   : 0,
        "skill_name" : "�˼��",
        "damage_type": "����"
]),
([      "action": "$N����ǰ��ʹ�������������������������ޣ�$w��������$n��$l��ȥ",
        "force" : 240,
        "attack": 150,
        "dodge" : 115,
        "parry" : 125,
        "damage": 130,
        "lvl"   : 40,
        "skill_name" : "������",
        "damage_type": "����"
]),
([      "action": "$Nһʽ���������������Ʈ�����ߣ��˷�����������$wңҡָ��$n��$l",
        "force" : 260,
        "attack": 160,
        "dodge" : 125,
        "parry" : 128,
        "damage": 140,
        "lvl"   : 80,
        "skill_name" : "�����",
        "damage_type": "����"
]),
([      "action": "$N��������Ծ��һʽ�����޵������������ּ�ת������ն��$n��$l",
        "force" : 280,
        "attack": 170,
        "dodge" : 120,
        "parry" : 135,
        "damage": 155,
        "lvl"   : 120,
        "skill_name" : "���޵�",
        "damage_type": "����"
]),
([      "action": "$N����$w�й�ֱ����һʽ������������������Ϣ�ض�׼$n��$l�̳�һ��",
        "force" : 320,
        "attack": 180,
        "dodge" : 125,
        "parry" : 142,
        "damage": 160,
        "lvl"   : 160,
        "skill_name" : "������",
        "damage_type": "����"
]),
([      "action": "$N����$wбָ���죬��â���£�һʽ���켫��������׼$n��$lбб����",
        "force" : 360,
        "attack": 185,
        "dodge" : 125,
        "parry" : 151,
        "damage": 170,
        "lvl"   : 200,
        "skill_name" : "�켫��",
        "damage_type": "����"
]),
([      "action": "$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ�������ֻء���ת��$n",
        "force" : 390,
        "attack": 190,
        "dodge" : 130,
        "parry" : 159,
        "damage": 175,
        "lvl"   : 240,
        "skill_name" : "�����ֻ�",
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ�������������������ֻؽ���\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("����ڹ����̫ǳ���������������ֻؽ���\n");

        if ((int)me->query_skill("sword", 1) < 250)
                return notify_fail("��Ľ����������㣬�������������ֻؽ���\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������������ֻؽ���\n");

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
        level = (int) me->query_skill("lunhui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<120 )
                return notify_fail("������������������ֻؽ���\n");

        if( query("neili", me)<150 )
                return notify_fail("������������������ֻؽ���\n");

        me->receive_damage("qi", 100);
        addn("neili", -120, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lunhui-jian/" + action;
}