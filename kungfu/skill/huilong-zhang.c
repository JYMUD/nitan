// huilong-zhang.c �����ȷ�

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N΢һ������һ�С�������״����$w���Ŵ̶���֨֨��������ɨ��$n�Ľ���",
        "force" : 100,
        "attack": 10,
        "dodge" : -5,
        "parry" : 9,
        "damage": 15,
        "lvl"   : 0,
        "skill_name" : "������״",
        "damage_type":"����"
]),
([      "action": "$Nһ�С�����Ǳ�С���������ס�ȶˣ����ƾ���һ��������ƾ���Ե���$n�ļ�ͷ",
        "force" : 110,
        "attack": 15,
        "dodge" : -10,
        "parry" : 15,
        "damage": 15,
        "lvl"   : 30,
        "skill_name" : "����Ǳ��",
        "damage_type":"����"
]),
([      "action": "$Nһ�С������رڡ�������$wƹƹ���ҵ��������ã���$n�����ұܣ��Ǳ�����",
        "force" : 120,
        "attack": 20,
        "dodge" : -5,
        "parry" : 19,
        "damage": 20,
        "lvl"   : 60,
        "skill_name" : "�����ر�",
        "damage_type":"����"
]),
([      "action": "$Nһ�С�ǳ����ˮ��������$w�������ض���һ�ᣬͻȻ�͵�һ�ȴ���$n��$l",
        "force" : 140,
        "attack": 25,
        "dodge" : -5,
        "parry" : 22,
        "damage": 20,
        "lvl"   : 70,
        "skill_name" : "ǳ����ˮ",
        "damage_type":"����"
]),
([      "action": "$N��$w��ס�Լ������ţ�һ��ָ��$n��һ�С��������졹�������к��ų���$n",
        "force" : 160,
        "attack": 30,
        "dodge" : -15,
        "parry" : 28,
        "damage": 30,
        "lvl"   : 80,
        "skill_name" : "��������",
        "damage_type":"����"
]),
([      "action": "$Nһ�С�������ˮ����ȫ����ֱ�������ų���ǰ�У��䲻������������$n��ȥ",
        "force" : 180,
        "attack": 35,
        "dodge" : 5,
        "parry" : 32,
        "damage": 30,
        "lvl"   : 90,
        "skill_name" : "������ˮ",
        "damage_type":"����"
]),
([      "action": "$N�����ɫ��һ�С����ɷ��衹����$n˵���䣬һ����$n�Ŵ�����ͱ�˹�ȥ",
        "force" : 220,
        "attack": 40,
        "dodge" : -5,
        "parry" : 37,
        "damage": 40,
        "lvl"   : 110,
        "skill_name" : "���ɷ���",
        "damage_type":"����"
]),
([      "action": "$Nһ�С��������������⽫$wˤ����ϣ���$n������һ�Ź��𣬻���$n��$l",
        "force" : 250,
        "attack": 45,
        "dodge" : -5,
        "parry" : 45,
        "damage": 40,
        "lvl"   : 120,
        "skill_name" : "������",
        "damage_type":"����"
]),
([      "action": "$N����һ�С�����������һ������������$w��������������$n���ɲ�",
        "force" : 280,
        "attack": 50,
        "dodge" : -5,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 130,
        "skill_name" : "������",
        "damage_type":"����"
]),
([      "action": "$Nһ�С��������������������Ų��ƣ�$wȴֱ�ɰ�գ���ƫ���е�����$n��$l",
        "force" : 310,
        "attack": 55,
        "dodge" : -5,
        "parry" : 58,
        "damage": 50,
        "lvl"   : 140,
        "skill_name" : "������",
        "damage_type":"����"
]),
([      "action": "$N�߾�$w��һ�С�������������������Ȱ�Ʈ������׼$n�������һ�ȴ���",
        "force" : 330,
        "attack": 61,
        "dodge" : -5,
        "parry" : 62,
        "damage": 60,
        "lvl"   : 150,
        "skill_name" : "������",
        "damage_type":"����"
]),
([      "action": "$Nһ�С�����Х���졹�����ȶ�����$w���ǧ�ٸ����ƣ���������$nȫ������Ҫ��",
        "force" : 350,
        "attack": 65,
        "dodge" : -5,
        "parry" : 67,
        "damage": 60,
        "lvl"   : 160,
        "skill_name" : "����Х����",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("staff", 1) < 80)
                return notify_fail("��Ļ����ȷ����̫ǳ��\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("huilong-zhang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ļ����ȷ���\n");

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
        level = (int) me->query_skill("huilong-zhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("������������������ȷ���\n");

        if( query("neili", me)<75 )
                return notify_fail("������������������ȷ���\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huilong-zhang/" + action;
}