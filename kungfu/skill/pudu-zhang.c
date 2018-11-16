// pudu-zhang.c �ն��ȷ�

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$Nʹһ��"HIB"����ţת�ǡ�"NOR"������$w���¶��ϣ������ޱȵ���$n��С����ȥ��",
        "lvl" : 0,
        "skill_name" : "��ţת��"
]),
([        "action":"$N�첽�����һ��"HIW"��Ұ��׷�硹"NOR"������ƽ��$w�����������ȶˣ�����$n���ؿڡ�",
        "lvl" : 9,
        "skill_name" : "Ұ��׷��"
]),
([        "action":"$N�߾�$w��һ��"HIM"���ͻ�������"NOR"��ȫ��Ծ������$w§ͷ�Ƕ�����$n��ȥ��",
        "lvl" : 18,
        "skill_name" : "�ͻ�����"
]),
([        "action":"$Nһ��"HIY"��ʨ��ҡͷ��"NOR"��˫�ֳ������֣���׼$n�͵�һ������ͬƽ�ع���һ�����硣",
        "lvl" : 27,
        "skill_name" : "ʨ��ҡͷ"
]),
([        "action":"$N���$w��һ��"HIR"��������β��"NOR"���ȶ˻���������ԲȦ�����ͳ��أ���$n�������С�",
        "lvl" : 36,
        "skill_name" : "������β"
]),
([        "action":"$Nȫ�������$w�̵غ�ɣ�ͻ��һ��"HIG"����������"NOR"����Ӱ��$n��������",
        "lvl" : 45,
        "skill_name" : "��������"
]),
([        "action":"$N˫�ֺ�ʮ������һ��"HIY"����ɮ�в���"NOR"��$w������ɳ���������$nײȥ��",
        "lvl" : 53,
        "skill_name" : "��ɮ�в�"
]),
([        "action":"$Nһ��"CYN"���Ⱥ��նɡ�"NOR"��$w�������������Ծ����ֱ��$n���ؿڴ��롣",
        "lvl" : 60,
        "skill_name" : "�Ⱥ��ն�"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage=="parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("��������������޷�ѧϰ�ն��ȷ���\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ����̫ǳ���޷�ѧϰ�ն��ȷ���\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("pudu-zhang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷�����������ն��ȷ���\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("������������������ն��ȷ���\n");
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
        int d_e1 = -35;
        int d_e2 = 0;
        int p_e1 = 30;
        int p_e2 = 55;
        int f_e1 = 200;
        int f_e2 = 250;
        int m_e1 = 150;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("pudu-zhang", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }
string perform_action_file(string action)
{
        return __DIR__"pudu-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n�ն��ȷ���"NOR"\n");
        write(@HELP

    �ն��ȷ�Ϊ������ʮ������֮һ��

        ѧϰҪ��
                ��Ԫһ����20��
                ����100
HELP
        );
        return 1;
}
