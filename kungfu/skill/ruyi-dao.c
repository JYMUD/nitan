// ruyi-dao.c ���⵶

#include <ansi.h>;

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����$wбָ��һ��"BLU"��ͣ����·��"NOR"������һ�٣�һ����$n��$l��ȥ",
        "lvl"    : 0,
        "skill_name" : "ͣ����·",
]),
([        "action" : "$Nһ��"HIW"��ͯ�ӹһ���"NOR"����������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
        "lvl"    : 8,
        "skill_name" : "ͯ�ӹһ�",
]),
([        "action" : "$Nչ���鲽������Ծ�䣬һ��"MAG"���ƴ����¡�"NOR"������һ������ն��$n",
        "lvl"    : 16,
        "skill_name" : "�ƴ�����",
]),
([        "action" : "$Nһ��"HIG"�����ż�ɽ��"NOR"��$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
        "lvl"    : 24,
        "skill_name" : "���ż�ɽ",
]),
([        "action" : "$N����$wһ����һ��"CYN"����Ϫ���㡹"NOR"��˫�ֳ����������У�����$n���ؿ�",
        "lvl"    : 33,
        "skill_name" : "��Ϫ����",
]),
([        "action" : "$N����$w��ʹ��һ��"BLU"���Ź����ġ�"NOR"���������ã����ҿ�����������$n",
        "lvl"    : 42,
        "skill_name" : "�Ź�����",
]),
([        "action" : "$Nһ��"YEL"���������ۡ�"NOR"�����Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
        "lvl"    : 51,
        "skill_name" : "��������",
]),
([        "action" : "$N����פ�أ�һ��"HIC"��������Ϣ��"NOR"���ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
        "lvl"    : 60,
        "skill_name" : "������Ϣ",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<350 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("����ڹ����̫ǳ��\n");

        if (me->query_skill("blade", 1) < me->query_skill("ruyi-dao", 1))
                return notify_fail("��Ļ����������̫ǳ������������������⵶����\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<50 )
        return notify_fail("����������������⵶��\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
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
        int d_e2 = 25;
        int p_e1 = -5;
        int p_e2 = -25;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 150;//110;
        int m_e2 = 350;//220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("ruyi-dao", 1);
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
int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        return 1.3;
}

string perform_action_file(string action)
{
        return __DIR__"ruyi-dao/" + action;
}

int help(object me)
{
        write(HIC"\n���⵶��"NOR"\n");
        write(@HELP

    ���⵶����ң�ɵĵ�����

        ѧϰҪ��
                ��ڤ��10��
                ����50
HELP
        );
        return 1;
}
