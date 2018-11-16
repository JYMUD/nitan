// mingwang-jian.c ����������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$NŭĿԲ����ʹ��һ��"HIB"��������"NOR"������$wһ����ֱ��$n��$l",
        "skill_name" : "����",
        "lvl" : 0
]),
([        "action" : "$Nʹ��һʽ"HIW"�����ֳ�����"NOR"������һ������â����$n��$l",
        "skill_name" : "���ֳ���",
        "lvl" : 10
]),
([        "action" : "$Nʹ��һ��"HIY"��ɽ����"NOR"������Ծ���գ�$w��ɽ��������$n��$l",
        "skill_name" : "ɽ��",
        "lvl" : 20
]),
([        "action" : "$Nʹ��"HIC"��ǧ��ת��"NOR"����$w�����ĳ�һ�㣬��Ȼһ������$n��$l",
        "skill_name" : "ǧ��ת",
        "lvl" : 30
]),
([        "action" : "$Nʹ��һ��"HIM"����ħ�衹"NOR"��ȫ��������$w�У�����ֱָ$n��$l",
        "skill_name" : "��ħ��",
        "lvl" : 40
]),
([        "action" : "$N���������ʹ��һʽ"MAG"�����衹"NOR"��һ���������Ӱ����$n��$lɨȥ",
        "skill_name" : "����",
        "lvl" : 50
]),
([        "action" : "$Nʹ��һ��"GRN"�����ڡ�"NOR"������$w������������$n��$l",
        "skill_name" : "����",
        "lvl" : 60
]),
([        "action" : "$N����һԾ���Ӹ�����ʹ��"BLU"���������졹"NOR"����ʱ�����������$n��$l",
        "skill_name" : "��������",
        "lvl" : 80
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
//int valid_combine(string combo) { return combo=="xuedao-daofa"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<400 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 70)
                return notify_fail("����ڹ����̫ǳ��\n");

        if (me->query_skill("sword", 1) < me->query_skill("mingwang-jian", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������Ĳ�������������\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<30
         || query("neili", me)<15 )
                return notify_fail("����������������������˲�����������\n");
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
        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = 0;
        int p_e2 = 20;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 40;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("mingwang-jian", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"mingwang-jian/" + action;
}

int help(object me)
{
        write(HIC"\n������������"NOR"\n");
        write(@HELP

    ѩ��ѩɽ�½�����

        ѧϰҪ��
                ���󹦻�С���๦20��
                ����100
HELP
        );
        return 1;
}
