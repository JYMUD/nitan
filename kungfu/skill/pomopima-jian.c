// pomopima-jian.c ��ī���齣��
// Last Modified by sir 11.1.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":       "$Nʹһ��"HIW"���׺���ա�"NOR"������$w��ƮƮ����$n��$lնȥ��",
        "lvl" : 0,
        "skill_name" : "�׺����"
]),
([        "action":       "$N�������磬$w����һ��"HIY"��������硹"NOR"���¶�������$n��$l",
        "lvl" : 10,
        "skill_name" : "�������"
]),
([        "action":       "$N����һת��һ��"GRN"������������"NOR"$w���ⲻ����ն��$n��$l",
        "lvl" : 20,
        "skill_name" : "��������"
]),
([        "action":       "$N�趯$w��һ��"CYN"���ĳ���ң��"NOR"Ѹ�����׵�����$n��$l",
        "lvl" : 30,
        "skill_name" : "�ĳ���ң"
]),
([        "action":       "$N����$wһ�Σ�һ��"HIG"����ɽ���ɡ�"NOR"��$n��$lбб����һ��",
        "lvl" : 40,
        "skill_name" : "��ɽ����"
]),
([        "action":       "$N�ὣ���磬�������һ��"HIC"������������"NOR"ֱ��$n$l",
        "lvl" : 50,
        "skill_name" : "��������"
]),
([        "action":       "$N�Ʋ�����ʹһ��"HIM"����ɽ��Ұ��"NOR"�������ն��$n��$l",
        "lvl" : 60,
        "skill_name" : "��ɽ��Ұ"
]),
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry";}
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("pomopima-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������ī���齣��\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("���������һ�ѽ���������������\n");

        if( query("qi", me)<30 || query("neili", me)<30 )
                return notify_fail("��������������������Ž�������������Ϣ��Ϣ�ɡ�\n");
        me->receive_damage("qi", 20);
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
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 125;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("pomopima-jian", 1);
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
        return __DIR__"pomopima-jian/" + action;
}

int help(object me)
{
        write(HIC"\n��ī���齣����"NOR"\n");
        write(@HELP

    ������̺�ľ���书��÷ׯ��ׯ�����������ұ��졣

        ѧϰҪ��
                �����ķ�10��
                ����100
HELP
        );
        return 1;
}