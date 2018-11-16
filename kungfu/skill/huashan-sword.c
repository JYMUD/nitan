// huashan-sword.c
// ����,��force

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "�з�����",
        "action": "$Nʹһ��"HIM"���з����ǡ�"NOR"������$w���Ⱪ������$n��$l��ȥ",
        "lvl" : 0
]),
([        "skill_name" :"�ޱ���ľ",
        "action": "$N������ת��һ��"GRN"���ޱ���ľ��"NOR"����$n��$l",
        "lvl" : 10
]),
([        "skill_name" :"���ڤڤ",
        "action": "$N�趯$w��һ��"BLU"�����ڤڤ��"NOR"Ю�������������$n��$l",
        "lvl" : 20
]),
([        "skill_name" :"ƽɳ����",
        "action": "$N����$w����һ��������"HIY"��ƽɳ���㡹"NOR"��$n��$l�̳�����",
        "lvl" : 30
]),
([        "skill_name" :"��������",
        "action": "$N����$w���Ⱪ����һ��"RED"���������á�"NOR"��$n$l��ȥ",
        "lvl" : 40
]),
([        "skill_name" :"�׺����",
        "action": "$N����$w����һ���⻡��ֱָ$n$l��һ��"HIW"���׺���ա�"NOR"��������������ȥ",
        "lvl" : 50
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;
        if( query("max_neili", me)<50 )
                return notify_fail("�������������û�а취����ɽ������\n");
        if( !(ob=query_temp("weapon", me)) || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");
        if (me->query_skill("sword", 1) < me->query_skill("huashan-sword", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������Ļ�ɽ������\n");

        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("����������������û�а취��ϰ��ɽ������\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e1 = 0;
        int d_e2 = 25;
        int p_e1 = -25;
        int p_e2 = -10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 120;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huashan-sword", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;

        if (me->query_skill("zixia-shengong", 1) < 100
        ||  me->query_skill_mapped("force") != "huashan-sword"
         || !query_temp("powerup", me )
        ||  damage < 100) return 0;

        if (random(damage / 2) > 50)
        {
                result = ([ "damage": damage ]);
                result += (["msg" : HIR "ֻ���Ϲ�������$n�rѪ�ĞR����$N" HIR "���ϵ���ϼ�����ˣ�\n" NOR]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"huashan-sword/" + action;
}
int help(object me)
{
        write(HIC"\n��ɽ������"NOR"\n");
        write(@HELP

    ��ɽ����Ϊ��ɽ���ڽ�����

        ѧϰҪ��
                ��ϼ��
                ����50
HELP
        );
        return 1;
}
