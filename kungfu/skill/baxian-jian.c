#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N��¶΢Ц��һ�С����Ƽ��ա�������$wһ�������Ⱪ��������$n��$l",
        "force"  : 50,
        "attack" : 15,
        "dodge"  : 10,
        "parry"  : 25,
        "damage" : 10,
        "lvl"    : 0,
        "skill_name" : "���Ƽ���",
        "damage_type":  "����"
]),
([      "action" : "$Nһ�С�����ָ·��������ͻ�������ж��䣬����$w�Ӻ�б����$n��$l",
        "force"  : 70,
        "attack" : 21,
        "dodge"  : 25,
        "parry"  : 30,
        "damage" : 15,
        "lvl"    : 20,
        "skill_name" : "����ָ·",
        "damage_type":  "����"
]),
([      "action" : "$N�������ߣ�һ�С��ܹ����İ塹�����׸������������$w��Ȼ���ϣ�����$n��$l",
        "force"  : 75,
        "attack" : 23,
        "dodge"  : 22,
        "parry"  : 32,
        "damage" : 20,
        "lvl"    : 40,
        "skill_name" : "�ܹ����İ�",
        "damage_type":  "����"
]),
([      "action" : "$N����һ�Σ����Ӷ��ϣ�ʹһ�С����ﳯ����������$w����һ������׼$n��������",
        "force"  : 90,
        "attack" : 29,
        "dodge"  : 10,
        "parry"  : 25,
        "damage" : 21,
        "lvl"    : 60,
        "skill_name" : "���ﳯ��",
        "damage_type":  "����"
]),
([      "action" : "$N����һչ��ʩչ�������Ӵ������Ӱ���棬����$w����$n��$l��ȥ",
        "force"  : 103,
        "attack" : 31,
        "dodge"  : 13,
        "parry"  : 22,
        "damage" : 23,
        "lvl"    : 80,
        "skill_name" : "���Ӵ���",
        "damage_type":  "����"
]),
([      "action" : "$Nһ�С��ɺ��׻�����������ӣ�����$w����б������ֱָ$n��$l",
        "force"  : 125,
        "attack" : 35,
        "dodge"  : 15,
        "parry"  : 25,
        "damage" : 28,
        "lvl"    : 100,
        "skill_name" : "�ɺ��׻�",
        "damage_type":  "����"
]),
([      "action" : "$N΢΢һ��ת��һ�С��Ź��ϵ���¿��������$wȴ�������´���������$n��$l",
        "force"  : 133,
        "attack" : 42,
        "dodge"  : 11,
        "parry"  : 27,
        "damage" : 33,
        "lvl"    : 120,
        "skill_name" : "�Ź��ϵ���¿",
        "damage_type":  "����"
]),
([      "action" : "$N��ɫ΢�䣬һ�С��������������ȡ������ж�ʱ��������ޱȣ�����$w���������$n",
        "force"  : 151,
        "attack" : 47,
        "dodge"  : 13,
        "parry"  : 32,
        "damage" : 36,
        "lvl"    : 140,
        "skill_name" : "��������������",
        "damage_type":  "����"
]),
([      "action" : "$N�������ף�����һ�С��������«ϵ����������$w�й�ֱ����Ѹ���ޱȵ���$n��ȥ",
        "force"  : 165,
        "attack" : 53,
        "dodge"  : 20,
        "parry"  : 34,
        "damage" : 43,
        "lvl"    : 160,
        "skill_name" : "�������«ϵ��",
        "damage_type":  "����"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ���ɽ�����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("baxian-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������İ��ɽ�����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
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

        lvl = (int)me->query_skill("baxian-jian", 1);
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
                "damage_type" : random(2) ? "����":"����",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<50 )
                return notify_fail("�������Ŀǰû�а취��ϰ���ɽ�����\n");

        if( query("neili", me)<50 )
                return notify_fail("��������������޷���ϰ���ɽ�����\n");

        addn("qi", -43, me);
        addn("neili", -44, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baxian-jian/" + action;
}