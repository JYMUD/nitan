// xuantian-zhi.c ��������ָ
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N��ָ�ӳ���һʽ"BLU"����Ȼ���꡹"NOR"������$n����Ե",
        "lvl" : 0,
        "skill_name" : "��Ȼ����"
]),
([        "action" : "$Nȫ��֮������һָ��һʽ"HIC"���������项"NOR"��ָ��$n����ǰ",
        "lvl" : 15,
        "skill_name" : "��������"
]),
([        "action" : "$N�����������Ѩ������һʽ"MAG"��������֡�"NOR"����$n��$l����",
        "lvl" : 25,
        "skill_name" : "�������"
]),
([        "action" : "$N˫Ŀŭ�ӣ�һʽ"CYN"���������ġ�"NOR"��˫ָ����$n�Ķ�����硢�ۡ���
����",
        "lvl" : 45,
        "skill_name" : "��������"
]),
([        "action" : "$Nһʽ"HIR"���������ˡ�"NOR"�������������⣬��ָ���Ƶ���$n��$l",
        "lvl" : 60,
        "skill_name" : "��������"
]),
([        "action" : "$N���������ʮָ�濪��һʽ"HIW"�����߱��项"NOR"��Сָ����$n��̫ԨѨ",
        "lvl" : 70,
        "skill_name" : "���߱���"
]),
([        "action" : "$N˫�ų�������������һʽ"HIG"���������ࡹ"NOR"����$n��ȫ��",
        "lvl" : 80,
        "skill_name" : "��������"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ָ������֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�ѧ����ָ��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������̫�����޷�������ָ��\n");

        if ((int)me->query_skill("finger", 1) < 80)
                return notify_fail("��Ļ���ָ����򲻹����޷�������ָ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("xuantian-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��������������ָ��\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("jing", me)<40 )
                return notify_fail("��ľ�̫���ˡ�\n");
        if( query("neili", me)<20 )
                return notify_fail("���������������������ָ��\n");
        me->receive_damage("jing", 35);
        addn("neili", -15, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("xuantian-zhi", 1);
        flvl=query("jiali", me);
        if (lvl < 100 || flvl < 20 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xuantian_zhi",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return HIW "$n" HIW "ֻ�о�����֮�����ģ�ȫ��̱����Ƥ���ϣ����Ӿ�������һ�㺮˪��\n" NOR;
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 240;
        int f_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xuantian-zhi", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"xuantian-zhi/" + action;
}

int help(object me)
{
        write(HIC"\n��������ָ��"NOR"\n");
        write(@HELP

    ������̺�ľ���书��÷ׯ��ׯ���ڰ��ӵ�����ָ����������
���������ھ���������������֮�С�

        ѧϰҪ��
                �����ķ�80��
                ����150
HELP
        );
        return 1;
}

