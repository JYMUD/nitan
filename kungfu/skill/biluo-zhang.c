// biluo-zhang.c ������
// Last Modified by sir 10.23.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$Nһʽ������ʽ�������ִ��磬��������$n��$l",
        "force"  : 30,
        "attack" : 5,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 10,
        "lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$N����΢̨��ֱ����ǰ��һʽ������ʽ��������$n��$l��ȥ",
        "force"  : 45,
        "attack" : 8,
        "dodge"  : 20,
        "parry"  : 35,
        "damage" : 13,
        "lvl"    : 10,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$Nʹһʽ�����ʽ��������΢��������˳�ƶ������͵ز���$n��$l",
        "force"  : 60,
        "attack" : 12,
        "dodge"  : 25,
        "parry"  : 20,
        "damage" : 15,
        "lvl"    : 25,
        "damage_type" : "����",
        "skill_name"  : "���ʽ"
]),
([      "action" : "$N˫����������������һʽ������ʽ�����Ʒ缤����������$n��ȥ",
        "force"  : 76,
        "attack" : 15,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 18,
        "lvl"    : 38,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$N˫�Ʋ��Ϸ�ת��ʹ��һʽ��Ǳ��ʽ����˫�Ʋ�£����ֱ����$n��$lϮȥ",
        "force"  : 52,
        "attack" : 18,
        "dodge"  : 33,
        "parry"  : 30,
        "damage" : 25,
        "lvl"    : 55,
        "damage_type" : "����",
        "skill_name"  : "Ǳ��ʽ"
]),
([      "action" : "$N����һ�䣬ʹһʽ������ʽ����˫�ƴ�����ɲ�ľ������͵ػ���$n��$l",
        "force"  : 90,
        "attack" : 20,
        "dodge"  : 38,
        "parry"  : 35,
        "damage" : 30,
        "lvl"    : 65,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$Nʹһʽ������ʽ����˫�������ƻã�ͬʱ��$n��$l��ȥ",
        "force"  : 120,
        "attack" : 22,
        "dodge"  : 42,
        "parry"  : 38,
        "damage" : 33,
        "lvl"    : 72,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$Nһʽ������ʽ���������䣬������Ʈ���������ѻ���$n��$l��",
        "force"  : 140,
        "attack" : 24,
        "dodge"  : 45,
        "parry"  : 45,
        "damage" : 38,
        "lvl"    : 80,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
([      "action" : "$Nͻ��һ�С�����ʽ����˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
        "force"  : 160,
        "attack" : 26,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 50,
        "lvl"    : 90,
        "damage_type" : "����",
        "skill_name"  : "����ʽ"
]),
});

int valid_enable(string usage) { return usage=="parry" || usage=="strike"; }
//int valid_combine(string combo) { return combo=="luoyan-hand"; }
int valid_combine(string combo)
{
        return combo == "henshan-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�������Ʒ�������֡�\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹����޷�ѧ�����Ʒ���\n");

        if( query("max_neili", me)<100 )
                return notify_fail("�������̫�����޷������Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("��Ļ����Ʒ����̫ǳ��\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("biluo-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ı����Ʒ���\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<60 )
                return notify_fail("������������������ơ�\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
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
        int d_e1 = 15;
        int d_e2 = 50;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 30;
        int f_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("biluo-zhang", 1);
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"biluo-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n�����ƣ�"NOR"\n");
        write(@HELP

    �������Ǻ�ɽ�ɵ��Ʒ���
    ����������ֻ�����

        ѧϰҪ��
                �����ķ�15��
                ����50
HELP
        );
        return 1;
}
