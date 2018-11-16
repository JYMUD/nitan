// sanhua-zhang.c ɢ����

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N���Ʊ���һʽ"HIG"������ݾ���"NOR"��˫�Ʊ�����£���������$n��$l",
        "lvl" : 0,
        "skill_name" : "����ݾ�"
]),
([      "action" : "$N��ָ������һʽ"GRN"�����ж���ܰ��"NOR"�������ƴ��巭�ɣ�����$n��$l��ȥ",
        "lvl" : 20,
        "skill_name" : "���ж���ܰ"
]),
([      "action" : "$Nʹһʽ"YEL"���ﺨ��˪�塹"NOR"���������У�����է��է�ϣ��͵ز���$n��$l",
        "lvl" : 40,
        "skill_name" : "�ﺨ��˪��"
]),
([      "action" : "$N˫��Ѫ�죬һʽ"MAG"��������÷����"NOR"���ó�����÷����䣬������$n��ȥ",
        "lvl" : 60,
        "skill_name" : "������÷��"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="nianhua-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ɢ���Ʊ�����֡�\n");

        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("����ڹ���򲻹����޷�ѧɢ���ơ�\n");

        if( query("max_neili", me)<300 )
                return notify_fail("�������̫�����޷���ɢ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("sanhua-zhang", 1))
                return notify_fail("��Ļ����Ʒ����ˮƽ���ޣ��޷����������ɢ���ơ�\n");

        if ((int)me->query_skill("weituo-gun", 1) < 60
        &&  (int)me->query_skill("cibei-dao", 1) < 60
        &&  (int)me->query_skill("pudu-zhang", 1) < 60
        &&  (int)me->query_skill("fengyun-shou", 1) < 60)
                return notify_fail("�������Τ�ӹ����ȱ������ն��ȣ��ͷ���������ѡһ������һ�����������ɢ���ơ�\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<30 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<20 )
                return notify_fail("�������������ɢ���ơ�\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
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
        int d_e1 = -25;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 140;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sanhua-zhang", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"sanhua-zhang/" + action;
}

int help(object me)
{
        write(HIC"\nɢ���ƣ�"NOR"\n");
        write(@HELP

    ɢ����Ϊ������ʮ������֮һ��
    �����黨ָ������

        ѧϰҪ��
                ��Ԫһ����20��
                ����100
HELP
        );
        return 1;
}
