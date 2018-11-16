//lingshe_zhangfa.c �����ȷ�

#include "ansi.h"
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nʹ��һ��"HIB"�����߳�����"NOR"������$w�󿪴���ɨ��$n��$l",
        "lvl"    : 0,
        "skill_name" : "���߳���"
]),
([        "action" : "$N����$w������죬һ��"BLU"��ҡͷ��β��"NOR"��$n��$l��ȥ",
        "lvl"    : 20,
        "skill_name" : "ҡͷ��β"
]),
([        "action" : "$N����$w���Ӹ�����ʹһ��"MAG"�������½���"NOR"����$n��$l",
        "lvl"    : 30,
        "skill_name" : "�����½�"
]),
([        "action" : "$Nһ��"HIM"������ͦ��"NOR"������$w����ɨ��$n��$l",
        "lvl"    : 40,
        "skill_name" : "����ͦ��"
]),
([        "action" : "$Nʹ��һ��"YEL"���������ߡ�"NOR"��$w�����ػ���$n��$lɨȥ",
        "lvl"    : 50,
        "skill_name" : "��������"
]),
([        "action" : "$N����$wһ�ӣ�ʹ��һ��"MAG"���߲����ҡ�"NOR"���������ɨ��$n��$l",
        "lvl"    : 60,
        "skill_name" : "�߲�����"
]),
([        "action" : "$Nʹ��һ��"RED"��������ɽ��"NOR"���߾�����$w����ͷ����$n��$l",
        "lvl"    : 80,
        "skill_name" : "������ɽ"
]),
([        "action" : "$Nʹ��һ��"HIR"�����߳�����"NOR"������$w��һ̽��ֱɨ$n��$l",
        "lvl"    : 100,
        "skill_name" : "���߳���"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("��Ļ����ȷ��������ң�����ѧϰ�����ȷ���\n");

        if ((int)me->query_skill("staff", 1) < me->query_skil("linshe-zhangfa", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ�������޷���������������ȷ���\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("������������������ȷ���\n");

        if( query("neili", me)<80 )
                return notify_fail("������������������ȷ���\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl,flvl;
        lvl = me->query_skill("lingshe-zhangfa",1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;
        if (!query_temp("weapon", me) || !query("snake_type", (query_temp("weapon", me))))
                       return;

       if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
              victim->affect_by("snake_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
       {
                return HIR "ֻ��$nʹ����һ����ȴ�Ǳ����ȶ��˵�С��ҧ�˸����ţ�\n" NOR;
       }
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
        int d_e2 = -20;
        int p_e1 = 5;
        int p_e2 = 40;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 210;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("lingshe-zhangfa", 1);
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"lingshe-zhangfa/" + action;
}
int help(object me)
{
        write(HIC"\n�����ȷ���"NOR"\n");
        write(@HELP

    �����ȷ�������ŷ����Ĵ����书���ȷ��׺ݣ�������ͷ����
��϶���ˣ�����������

        ѧϰҪ��
                ��󡹦20��
                ������Ϊ70
HELP
        );
        return 1;
}
