inherit SKILL;

mapping *action = ({
([      "action" : "$N����͵ط���һʽ���̹ſ��졹���ż�����$n��$l",
        "force"  : 80,
        "damage" : 20,
        "dodge"  : 15,
        "lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "�̹ſ���"
]),
([      "action" : "$N��Ŷٵأ��ҽ�һʽ�����Ǹ��¡�������$n��$l",
        "force"  : 120,
        "damage" : 25,
        "dodge"  : 10,
        "lvl"    : 15,
        "damage_type" : "����",
        "skill_name"  : "���Ǹ���"
]),
([      "action" : "$N�������ţ��ҽź��ߣ�������׼��һʽ����ɨǧ��������$n",
        "force"  : 150,
        "damage" : 30,
        "dodge"  : 15,
        "lvl"    : 30,
        "damage_type" : "����",
        "skill_name"  : "��ɨǧ��"
]),
([      "action" : "$NͻȻԾ��˫������Ȧת��һʽ���ٲ����������$n��ȫ��",
        "force"  : 190,
        "damage" : 35,
        "dodge"  : 15,
        "lvl"    : 50,
        "damage_type" : "����",
        "skill_name"  : "�ٲ�����"
]),
([      "action" : "$N˫�Ž�������һʽ��������Ϣ�����ŽŲ���$n����������",
        "force"  : 220,
        "damage" : 40,
        "dodge"  : 20,
        "lvl"    : 70,
        "damage_type" : "����",
        "skill_name"  : "������Ϣ"
]),
([      "action" : "$Nһ�������ҽ����϶��¡����߻�ɽ������$n������ֱ������",
        "force"  : 260,
        "damage" : 45,
        "dodge"  : 35,
        "lvl"    : 90,
        "damage_type" : "����",
        "skill_name"  : "���߻�ɽ"
]),
([      "action" : "$Nʹһʽ���丸׷�ա���˫���ǰ����Ѹ���޼�����$n���ؿ�",
        "force"  : 300,
        "damage" : 50,
        "dodge"  : 30,
        "lvl"    : 100,
        "damage_type" : "����",
        "skill_name"  : "�丸׷��"
]),
([      "action" : "$N�������������һ����һʽ�����춯�ء���˫���͵�����$n��$l",
        "force"  : 330,
        "damage" : 60,
        "dodge"  : 35,
        "lvl"    : 120,
        "damage_type" : "����",
        "skill_name"  : "���춯��"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||  usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xiaoyaoyou";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("ѧϰ�����ȱ�����֡�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹����޷�ѧ�����ȡ�\n");

        if( query("max_neili", me)<500 )
                return notify_fail("�������̫�����޷��������ȡ�\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jueming-tui", 1))
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷���������ľ����ȷ���\n");

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
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 220;
        int f_e2 = 320;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jueming-tui", 1);
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

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<70 )
                return notify_fail("������������������ȡ�\n");

        me->receive_damage("qi", 60);
        addn("neili", -51, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jueming-tui/" + action;
}