inherit SKILL;

mapping *action = ({
([      "action" : "$N�ֳ�$wһ�����£�Ѹ���ޱȣ��Ʋ��ɵ�",
        "force"  : 210,
        "dodge"  : 20,
        "parry"  : 25,
        "lvl"    : 0,
        "damage" : 44,
        "damage_type" : "����",
]),
([      "action" : "$N�������¶��ϻ��˸��뻡��$w������£�����$n�ľ���",
        "force"  : 250,
        "dodge"  : 30,
        "parry"  : 40,
        "lvl"    : 25,
        "damage" : 51,
        "damage_type" : "����",
]),
([      "action" : "$N��Ȼ��$w����컨��׹�������ѹ��$n",
        "force"  : 270,
        "dodge"  : 35,
        "parry"  : 50,
        "lvl"    : 50,
        "damage" : 56,
        "damage_type" : "����",
]),
([      "action" : "$Nһ��$w���������Ű�һ����$n��ȥ����ס$n���е���·",
        "force"  : 280,
        "dodge"  : 45,
        "parry"  : 55,
        "lvl"    : 70,
        "damage" : 62,
        "damage_type" : "����",
]),
([      "action" : "$Nת��Ծ������$w�����뵶������һ���������$n",
        "force"  : 305,
        "dodge"  : 50,
        "parry"  : 75,
        "lvl"    : 90,
        "damage" : 70,
        "damage_type" : "����",
]),
([      "action" : "$N����$w���ҿ���ɱ��$w���������׹⣬���·�������$n",
        "force"  : 330,
        "dodge"  : 55,
        "parry"  : 85,
        "lvl"    : 110,
        "damage" : 75,
        "damage_type" : "����",
]),
([      "action" : "$N��$wʹ�ú����·������ذ���أ�ƫ����ó��棬$wЮ��������$n��$l",
        "force"  : 350,
        "dodge"  : 52,
        "parry"  : 90,
        "lvl"    : 130,
        "damage" : 80,
        "damage_type" : "����",
]),
([      "action" : "$N���һ�������е�$w���糤��һ����$nֱ������",
        "force"  : 380,
        "dodge"  : 61,
        "parry"  : 95,
        "lvl"    : 150,
        "damage" : 85,
        "damage_type" : "����",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<600 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 60)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ��ʤ������\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("baisheng-daofa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������İ�ʤ������\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 45;
        int d_e2 = 20;
        int p_e1 = -10;
        int p_e2 = -25;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 110;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("baisheng-daofa", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("������������������˰�ʤ������\n");

        if( query("neili", me)<70 )
                return notify_fail("������������������˰�ʤ������\n");

        me->receive_damage("qi", 45);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-daofa/" + action;
}