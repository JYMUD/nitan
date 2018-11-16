#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����Ծ��һ��"MAG"�����չ�᡹"NOR"������$w���¶��ϣ�����$n������",
        "lvl"    : 0,
        "skill_name" : "���չ��",
]),
([        "action" : "$Nһ��"MAG"���ʷ����ࡹ"NOR"������$wֱ����$n��$l",
        "lvl"    : 20,
        "skill_name" : "�ʷ�����",
]),
([        "action" : "$Nһ��"HIY"���������"NOR"������$w�ڿ�һ��һ���������࣬�͵���$n��ͷ����",
        "lvl"    : 40,
        "skill_name" : "�����",
]),
([        "action" : "$N̤��һ��������$n��٬һЦ������$wȴ����ͣ����һ��"HIG "������Ϸ�"NOR"��ɨ��$n��$l",
        "lvl"    : 50,
        "skill_name" : "����Ϸ��",
]),
([        "action" : "$NԾ�ڰ�գ�һ��"HIR"�����ɷ��衹"NOR"������$w������ϴ�գ�����Ϸ�����������ֵ�$n����",
        "lvl"    : 60,
        "skill_name" : "���ɷ���",
]),
([        "action" : "$N��ǰ����������$wȦת��磬һ��"HIM"��������项"NOR"������$nǰ��",
        "lvl"    : 75,
        "skill_name" : "�������",
])
});

int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("���������һ�����޲������޷���\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ����̫ǳ���޷����ɷ�޷���\n");

        if( query("max_neili", me)<200 )
                return notify_fail("���������Ϊ̫�����޷����ɷ�޷���\n");

        if ((int)me->query_skill("whip") < 20)
                return notify_fail("��Ļ����޷��ȼ�̫�ͣ��޷�ѧ�ɷ�޷���\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("feifeng-bian", 1))
                return notify_fail("��Ļ����޷�ˮƽ���ޣ��޷���������ķɷ�޷���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int d_e1 = -40;
        int d_e2 = -35;
        int p_e1 = 5;
        int p_e2 = 20;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 100;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("feifeng-whip", 1);
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
                "damage_type" : random(2) ? "����": "����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<50 )
                return notify_fail("��������������ɷ�޷���\n");

        if( query("neili", me)<45 )
                return notify_fail("��������������ɷ�޷���\n");

        me->receive_damage("qi", 30);
        addn("neili", -39, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"feifeng-bian/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point() { return 1.0; }

int help(object me)
{
        write(HIC"\n�ɷ�޷���"NOR"\n");
        write(@HELP

    �ɷ�޷�Ϊ���ϴ���μҵ��书���������������������ӵ���
�����������

        ѧϰҪ��
                Ů��
                �����ڹ�20��
                ����100
HELP
        );
        return 1;
}