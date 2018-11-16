// qianye-shou.c ����ǧҶ��

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nһʽ"HIB"���Ϻ����"NOR"��������Σ���������ͻȻ����$n�ı����Ѩ",
        "lvl" : 0,
        "skill_name" : "�Ϻ����"
]),
([        "action" : "$N����һ�Σ�һʽ"HIY"������������"NOR"����������$n�ļ�ͷ����ȭ����$n���ؿ�",
        "lvl" : 10,
        "skill_name" : "��������"
]),
([        "action" : "$Nһʽ"HIG"������������"NOR"�����ֻ�£��צ��һ���־����$n���ʺ�Ҫ��",
        "lvl" : 20,
        "skill_name" : "��������"
]),
([        "action" : "$N�������У�����ֱ����һʽ"HIW"�������Ӱ��"NOR"����Ʈ��������$n������",
        "lvl" : 30,
        "skill_name" : "�����Ӱ"
]),
([        "action" : "$Nʹһʽ"CYN"��ˮ��׽�¡�"NOR"����ȭ�ϸ�����̽��ͻ����ץ��$n���ɲ�",
        "lvl" : 38,
        "skill_name" : "ˮ��׽��"
]),
([        "action" : "$N˫ȭ���裬һʽ"HIC"������ȥ����"NOR"�����ֻ��ۣ�£��Ȧ״���ͻ�$n�����",
        "lvl" : 45,
        "skill_name" : "����ȥ��"
]),
([        "action" : "$Nһʽ"HIM"��ˮ�ݳ�û��"NOR"��ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",
        "lvl" : 51,
        "skill_name" : "ˮ�ݳ�û"
]),
([        "action" : "$N˫�ֱ�ȭ��һʽ"RED"������������"NOR"����Ӱ���ɣ�ͬʱ��$nʩ���žŰ�ʮһ��",
        "lvl" : 56,
        "skill_name" : "��������"
]),
([        "action" : "$Nһʽ"HIR"������տա�"NOR"��ȭ���������֣��������ޣ�����������$n�ĵ���",
        "lvl" : 60,
        "skill_name" : "����տ�"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo == "longzhua-gong"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ǧҶ�ֱ�����֡�\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("����ڹ���򲻹����޷�ѧ����ǧҶ�֡�\n");

        if( query("max_neili", me)<200 )
                return notify_fail("�������̫�����޷�������ǧҶ�֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qianye-shou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷��������������ǧҶ�֡�\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<40 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<40 )
                return notify_fail("�����������������ǧҶ�֡�\n");
        me->receive_damage("qi", 35);
        addn("neili", -25, me);
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
        int d_e1 = -50;
        int d_e2 = -15;
        int p_e1 = 15;
        int p_e2 = 40;
        int f_e1 = 160;
        int f_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qianye-shou", 1);
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

mixed hit_ob(object me, object target, int damage)
{
        string msg;
        mixed result;
        int j;

        j = me->query_skill("qianye-shou", 1);

        if ((random(10) > 5) && j > 150 &&
            me->query_skill("buddhism", 1) >180 &&
            query("neili", me)>1000 && query("max_neili", me)>2500 )
        {
                result = ([ "damage" : damage ]);
                msg = CYN"$N��ƮƮ�ĳ�һ�ƣ��Ƶ���;����Ȼ΢΢ҡ�Σ���ʱһ�Ʊ����ƣ����Ʊ����ƣ����Ʊ���ơ�\n"NOR;
                msg += "���$nֻ��ٵ���̣�$N����Ʊ�ʮ���ƣ������û�Ϊ��ʮ���ơ�\n";
                msg +="$n����������������Ӱ���ں��ġ�\n";
                result += ([ "msg" : msg ]);

                return result;
        }
}
string perform_action_file(string action)
{
        return __DIR__"qianye-shou/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n����ǧҶ�֣�"NOR"\n");
        write(@HELP

    ����ǧҶ��Ϊ������ʮ������֮һ��
    ������צ��������

        ѧϰҪ��
                ��Ԫһ����20��
                ����100
HELP
        );
        return 1;
}
