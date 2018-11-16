// This program is a part of NT MudLIB
// liehuo-jian.c �һ�

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nһ�С��ĺ���Ʈ����$w�ƻó�ƬƬ���ƣ�����˷�������$n",
        "lvl" : 0,
        "skill_name" : "�ĺ���Ʈ",
]),
([        "action" : "$Nһ�С���ͨ�˴��������ָ������$n��$n�������ֱܷ�$w����·",
        "lvl" : 19,
        "skill_name" : "��ͨ�˴�",
]),
([        "action" : "$Nʹ��������һ������$w��һ������������һ�ɺ�������$n��$l",
        "lvl" : 29,
        "skill_name" : "����һ��",
]),
([        "action" : "$N�������ϵ���������ָ��һ�С���������������$w����һ�Ž���������$n��$l",
        "lvl" : 39,
        "skill_name" : "��������",
]),
([        "action" : "$Nһ�С����ٵ����������Ծ����أ�����$w�ó�һ��ѩ�׵��ٲ���ɨ��$n��$l",
        "lvl" : 59,
        "skill_name" : "���ٵ���",
]),
([        "action" : "$N���Ȱ�����ף�$wƽָ��һ�С�������ɫ��������������ɫ�������Ĵ���$n��$l",
        "lvl" : 79,
        "skill_name" : "������ɫ",
]),
([  "action" : "$Nһ�С��򴨹麣����$w��$n��������裬��$n�ۻ����ң������ڰ����ͻȻͣס����$n��$l",
        "lvl" : 99,
        "skill_name" : "�򴨹麣",
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 50)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ�һ𽣷���\n");

        if (me->query_skill("force", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("����ڹ����ӻ��������޷�����������һ𽣷���\n");

        if (me->query_skill("sword", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������һ𽣷���\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = query_temp("weapon", me)) ||
                (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( (int)query("qi", me) < 35 )
                return notify_fail("������������һ𽣷���\n");
        me->receive_damage("qi", 30);
        return 1;
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 25;
        int p_e2 = 5;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liehuo-jian", 1);
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
        return __DIR__"liehuo-jian/" + action;
}

int help(object me)
{
        write(HIR"\n�һ𽣷���"NOR"\n");
        write(@HELP

    �һ𽣷������̵Ľ�����

        ѧϰҪ��
                �����ڹ�10��
                ������Ϊ10
HELP
        );
        return 1;
}