// This program is a part of NITAN MudLIB
// liuhe-dao.c ؤ�����ϵ���

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action":"$N���һ��������$w�󿪴��أ������ӵ�ʹ�����Ǳ����졹��ն��$n��$l",
        "attack": 55,
        "dodge" : 56,
        "parry" : 54,
        "damage": 120,
        "lvl" : 0,
        "skill_name" : "�Ǳ�����",
        "damage_type":  "����"
]),
([      "action":"$N�˵���磬һ�С����Ǻ�ɽ�������ưԵ�֮��������$n��������Ϳ�����",
        "attack": 60,
        "dodge" : 60,
        "parry" : 65,
        "damage": 130,
        "lvl" : 10,
        "skill_name" : "���Ǻ�ɽ",
        "damage_type":  "����"
]),
([      "action":"$Nһ�š����է�ϡ���ͻȻ����$n���࣬Ѹ�͵�������ն����ʽ��Ȼ�ϳ�һ��ԲȦ",
        "attack": 60,
        "dodge" : 60,
        "parry" : 55,
        "damage": 140,
        "lvl" : 25,
        "skill_name" : "���է��",
        "damage_type":  "����"
]),
([      "action":"$N���챯Ц���漴�ӵ�ն��һʽ������޳�����$w��Ϊһ˿˿���⣬����$n$l",
        "attack": 70,
        "dodge" : 65,
        "parry" : 70,
        "damage": 140,
        "lvl" : 35,
        "skill_name" : "����޳�",
        "damage_type":  "����"
]),
([      "action":"$Nʩչ���ͺ�����������$n������$w���ſ�Ұ���磬�����ޱȵ���������",
        "attack": 63,
        "dodge" : 60,
        "parry" : 70,
        "damage": 145,
        "lvl" : 45,
        "skill_name" : "�ͺ�����",
        "damage_type":  "����"
]),
([      "action":"$N��ɫׯ�أ��ӵ�ʹ�����������ҡ���$w���϶�����$n����������һ�������׺䶥",
        "attack": 70,
        "dodge" : 70,
        "parry" : 75,
        "damage": 145,
        "lvl" : 60,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("��Ļ����������̫ǳ��\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 5;
        int p_e2 = -15;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 50;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("liuhe-dao", 1);
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
         || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("����������������ϵ�����\n");
        if( query("neili", me)<70 )
                return notify_fail("����������������ϵ�����\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuhe-dao/" + action;
}

int learn_bonus() { return 20; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n���ϵ�����"NOR"\n");
        write(@HELP

    �������ϵ�Ϊؤ��ĵ�����

        ѧϰҪ��
                ��������30��
                ����50
HELP
        );
        return 1;
}