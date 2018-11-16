// luoying-shenjian.c ��Ӣ��

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "��Ӣ�ͷ�",
        "action" : "$Nʹһ��"HIW"����Ӣ�ͷס�"NOR"����������Ʈ������$w����ʵʵ�ó���㽣���׷���������$n$l",
        "lvl"    : 0
]),
([        "skill_name" : "�����һ�",
        "action" : "$N�趯$w��һʽ"MAG"�������һ���"NOR"��������$n����һ�Σ�����$w�������佣��Ю�Ż�����������$n��$l",
        "lvl"    : 10
]),
([        "skill_name" : "��������",
        "action" : "$N������$nһת������$w����һָ��һʽ"BLU"���������꡹"NOR"�ó����콣Ӱ����$n$l�����ӳ�����",
        "lvl"    : 20
]),
([        "skill_name" : "���Ƿɻ�",
        "action" : "$N����ƮȻ�����ڰ��������һ������Ȼһʽ"RED"�����Ƿɻ���"NOR"����$w�������޵�������$n��$l",
        "lvl"    : 30
]),
([        "skill_name" : "������",
        "action" : "$N�������࣬һʽ"HIW"��ϸ���ɷ��ء�"NOR"ͷ�½��ϣ�һ��"HIR "�������䡹"NOR"����$w���һ����������$n��$l",
        "lvl"    : 40
]),
([        "skill_name" : "���컨��",
        "action" : "$Nһ�����ʹ��"HIM"�����컨�꡹"NOR"������$w�ó����컨�꣬Ѹ����������$n��$l",
        "lvl"    : 50
]),
([        "skill_name" : "�仨����",
        "action" : "$N��̾һ��������$w����һ����һʱ"HIB"���仨���⡹"NOR"��$w��ȻԾ��ٿ�Ļ��������¶���һ���ƮȻ����$n��$l",
        "lvl"    : 60
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

int valid_learn(object me)
{
        object ob;

        if( !objectp(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�����ѧϰ������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹�����������Ӣ�񽣡�\n");

        if( query("max_neili", me)<250 )
                return notify_fail("���������Ϊ��������������Ӣ�񽣡�\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("luoying-shenjian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ӣ�񽣡�\n");

        return 1;
}
int practice_skill(object me)
{
        object ob;

        if( query("qi", me)<35 || query("neili", me)<15 )
                return notify_fail("�����������������û�취��ϰ��Ӣ�񽣡�\n");
        if( !objectp(ob=query_temp("weapon", me) )
                 || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�����ϰ��������\n");
        me->receive_damage("qi", 35);
        addn("neili", -15, me);
        write("�㰴����ѧ����һ����Ӣ�񽣡�\n");
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
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -65;
        int p_e2 = -55;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 150;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenjian", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"luoying-shenjian/" + action;
}

int help(object me)
{
        write(HIC"\n��Ӣ�񽣣�"NOR"\n");
        write(@HELP

    ��Ӣ��Ϊ�����һ�������ҩʦ������
    ���һ��������ڡ�����ͤ�����ԣ�����һ�����������һ�Ӱ��
���񽣣��̺��������������Ȼ��ҩʦ��ƽ��������书������
֮һ������Ӣ�񽣡�

        ѧϰҪ��
                �̲���30��
                ����100
HELP
        );
        return 1;
}
