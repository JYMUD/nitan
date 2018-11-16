// wuxiang-zhi.c - ��������ָ��

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N��˫��£������֮�У�һ��"HIW"���������١�"NOR"����������������ӿ��������$n",
        "lvl"   : 0,
        "skill_name" : "��������"
]),
([        "action" : "$N΢΢һЦ��һ��"HIW"���ǻ�����١�"NOR"���������ڣ�ָ�����������������ĥ��͸���޷����",
        "lvl"   : 10,
        "skill_name" : "�ǻ������"
]),
([        "action" : "$N����վ����˿������������$n��ǰ���һ�������������������"HIW"����������١�"NOR"",
        "lvl"   : 30,
        "skill_name" : "���������"
]),
([        "action" : "$Ņͷ���죬һָ"HIW"���Ժ�����١�"NOR"��Ϯ$n$l������ȴ��˿���������������·���һ��",
        "lvl"   : 60,
        "skill_name" : "�Ժ������"
]),
([        "action" : "$Nһ��"HIW"��ӱ������١�"NOR"��$n������ŵ�һ�ƿ�֮����ȴ��$P΢Ц��ͷ��ȴ�����κζ���",
        "lvl"   : 100,
        "skill_name" : "ӱ�������"
]),
([        "action" : "��������������$n��ɫͻ�䣬$Nȴ�������ڣ����޶����ֵļ��������������"HIW"��Բ������١�"NOR"",
        "lvl"   : 150,
        "skill_name" : "Բ�������"
]),
});

/*
mapping *action = ({
([     "action": "$N����ǰ̤��һ������ָ�й�ֱ����һʽ��������Ϣ������$n��$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "������Ϣ",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С��������������ᳪһ����ţ����ҿ�������һ����һ�ž���������$n",
       "force" : 90,
       "attack": 30,
       "parry" : 5,
       "dodge" : 20,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "��������",
       "damage_type" : "����"
]),
([     "action": "$N����Ʈ��������һʽ���޷����졹����ָ����$n��$l",
       "force" : 150,
       "attack": 50,
       "parry" : 35,
       "dodge" : 25,
       "damage": 80,
       "lvl"   : 80,
       "skill_name" : "�޷�����",
       "damage_type" : "����"
]),
([     "action": "$N��̤���ǲ���ͻȻһ�С�������ա�����ָ�����벻���ĽǶȹ���$n�ĸ���ҪѨ",
       "force" : 180,
       "attack": 70,
       "parry" : 35,
       "dodge" : -10,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "�������",
       "damage_type" : "����"
]),
([     "action": "$Nһ�С����������������$n��ת��һָ����$n����ʤ��",
       "force" : 230,
       "attack": 70,
       "parry" : 30,
       "dodge" : 15,
       "damage": 130,
       "lvl"   : 160,
       "skill_name" : "�������",
       "damage_type" : "����"
]),
([     "action": "$N��ϥ������һ�С����ޱߡ�������Ĵָ����һ�����磬����$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "���ޱ�",
       "damage_type" : "����"
]),
([     "action": "$N˫Ŀ���գ�һ�С���ɫ���ࡹ���ۼ�ȫ��������һָ���һ����ɫ����ֱ��$n",
       "force" : 250,
       "attack": 100,
       "parry" : 50,
       "dodge" : 25,
       "damage": 180,
       "lvl"   : 200,
       "skill_name" : "��ɫ����",
       "damage_type" : "����"
]),
});
*/
int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "xuni-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ָ������֡�\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���򲻹����޷�ѧ����ָ��\n");

        if( query("max_neili", me)<300 )
                return notify_fail("�������̫�����޷�������ָ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("wuxiang-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��������������ָ��\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 10;
        int d_e2 = 30;
        int p_e1 = -45;
        int p_e2 = -25;
        int f_e1 = 450;
        int f_e2 = 550;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuxiang-zhi", 1);
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

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("����������ϰ��\n");

        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<70 )
                return notify_fail("�����������������ָ��\n");

        me->receive_damage("qi", 50);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuxiang-zhi/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n�����ָ��"NOR"\n");
        write(@HELP

    �����ָ�����ָ߼�ָ�������ܻ�����ȡ�Է�ʮ���֡�����ǻۣ�
���磬�Ժ���ӱ��Բ������

        ѧϰҪ��
                һָ��50��
                ������Ϊ2500
HELP
        );
        return 1;
}
