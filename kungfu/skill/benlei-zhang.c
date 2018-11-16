inherit SKILL;

mapping *action = ({
([      "action": "$N˫������һ�С��硹�־���һ�ƻ���$n���ţ���һ��ȴ����$nС��",
        "force" : 185,
        "dodge" : 11,
        "parry" : 12,
        "attack": 9,
        "damage": 12,
        "lvl"   : 0,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$N˫�ƻ������Ī�⣬һ�С��꡹�־���˲Ϣ֮����$n����������һʮ����",
        "force" : 205,
        "dodge" : 18,
        "parry" : 17,
        "attack": 13,
        "damage": 17,
        "lvl"   : 20,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$Nһ����Х������һ�ƣ�һ�С�˪���־���ȥ����죬��$n��$l�ͻ���ȥ��",
        "force" : 217,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 21,
        "lvl"   : 40,
        "skill_name" : "˪�־�",
        "damage_type": "����"
]),
([      "action": "$N˫�ƽ����������ޣ�һ�С����־�������ת׾������$n��$l",
        "force" : 225,
        "dodge" : 24,
        "parry" : 21,
        "attack": 22,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$Nһ�С������־�������һȭ���������ƽ���������ȭ��һ����˫������������$n��$l",
        "force" : 255,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 41,
        "lvl"   : 80,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$N˫���뻮������˫�����ƣ�һ�С������־���һ����ɽ������������ֱ��$n����",
        "force" : 267,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 49,
        "lvl"   : 100,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$NͻȻ�������ת��һ�С������־�����Ӱ���裬��ʱ֮�佫$n����˷�����ס��",
        "force" : 280,
        "dodge" : 24,
        "parry" : 21,
        "attack": 37,
        "damage": 51,
        "lvl"   : 120,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
([      "action": "$N�����Ц������������۷��裬һ�С��ס��־����Ʒ���������������$n��ȥ",
        "force" : 320,
        "dodge" : 36,
        "parry" : 35,
        "attack": 41,
        "damage": 58,
        "lvl"   : 140,
        "skill_name" : "���־�",
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�����������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹����޷�ѧ���������ơ�\n");

        if( query("max_neili", me)<100 )
                return notify_fail("�������̫�����޷������������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("��Ļ����Ʒ����̫ǳ��\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("benlei-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�������������������ơ�\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -35;
        int p_e2 = 15;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("benlei-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }


int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<100 )
                return notify_fail("����������������������ơ�\n");

        me->receive_damage("qi", 55);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"benlei-zhang/" + action;
}