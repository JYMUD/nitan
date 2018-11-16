// fengmo-zhang.c ��ħ�ȷ�

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nб��$w, һ��"HIB"��������ʯ��"NOR"��б���������$n��$l",
        "lvl"    : 0,
        "skill_name" : "������ʯ"
]),
([        "action" : "$Nһ����ȣ�ʹ��һ��"GRN"��³�������"NOR", ����$w���¶���ɨ��$n��$l",
        "lvl"    : 39,
        "skill_name" : "³�����"
]),
([        "action" : "$Nʹ��һ��"BLU"������������"NOR"����$w�Ӽ�ͷ˦��������$n��$l",
        "lvl"    : 69,
        "skill_name" : "��������"
]),
([        "action" : "$N����һ�Σ�һ��"RED"���������"NOR"������$w���籩�����$n���",
        "lvl"    : 79,
        "skill_name" : "�������"
]),
([        "action" : "$Nһ��������һ��"HIW"�����羭�졹"NOR", $w����������������$n��$l",
        "lvl"    : 89,
        "skill_name" : "���羭��"
]),
([      "action" : RED "$N����ͻ��ɷ��������$w������$n���Ի��䡣��һ�ȳ����ֿ��ֺݣ����ǡ���ħ�ȷ����еĶ���"NOR,
        "lvl"    : 99,
        "skill_name" : "��ħ�ȷ�"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ���㣬�޷�ѧϰ��ħ�ȷ���\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("����ڹ����̫ǳ���޷�ѧϰ��ħ�ȷ���\n");

        if ((int)me->query_skill("staff", 1) < 30)
                return notify_fail("��Ļ����ȷ�̫ǳ���޷�ѧϰ��ħ�ȷ���\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("fengmo-zhang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������ķ�ħ�ȷ���\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -15;
        int p_e1 = 10;
        int p_e2 = 45;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 200;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("fengmo-zhang", 1);
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
                "damage_type" : "����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("���������������ħ�ȷ���\n");

        if( query("neili", me)<75 )
                return notify_fail("���������������ħ�ȷ���\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fengmo-zhang/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n��ħ�ȷ���"NOR"\n");
        write(@HELP

    ��ħ�ȷ�Ϊؤ����似��

        ѧϰҪ��
                ��������20��
                ����200
HELP
        );
        return 1;
}