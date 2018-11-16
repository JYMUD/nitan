// yunlong-zhua.c -����צ
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nȫ��εض��𣬰����һ�����һʽ"HIM"����ӥϮ�á�"NOR"��Ѹ�͵�ץ��$n��$l",
        "lvl"    : 0,
        "skills_name" : "��ӥϮ��",
]),
([        "action" : "$N����ֱ����˫��ƽ�죬һʽ"GRN"����ӥչ�᡹"NOR"��˫צһǰһ��£��$n��$l",
        "lvl"    : 10,
        "skills_name" : "��ӥչ��",
]),
([        "action" : "$Nһʽ"HIG"���γ�ӥ�ɡ�"NOR"��ȫ����б��ƽ�ɣ�����һ����˫צ����$n�ļ�ͷ",
        "lvl"    : 20,
        "skills_name" : "�γ�ӥ��",
]),
([        "action" : "$N˫צ�����Ͼ٣�ʹһʽ"HIC"��ӭ������"NOR"��һ�����ֱ�Ϯ��$n����Ҹ����",
        "lvl"    : 30,
        "skills_name" : "ӭ������",
]),
([        "action" : "$Nȫ�������ǰ��һʽ"HIW"��������צ��"NOR"����צͻ�������Ȱ�ץ��$n���ؿ�",
        "lvl"    : 40,
        "skills_name" : "������צ",
]),
([        "action" : "$N���ػ��У�һʽ"HIY"���������ء�"NOR"������Ϯ�����д�Ѩ�����ַ�ץ$n���ɲ�",
        "lvl"    : 50,
        "skills_name" : "��������",
]),
([        "action" : "$N��������צ���棬һʽ"HIW"���������ա�"NOR"�������������ƿն�����Ѹ���ޱȵػ���$n",
        "lvl"    : 60,
        "skills_name" : "��������",
]),
([        "action" : "$N�ڿո߷����ɣ�һʽ"YEL"��ӥ�����"NOR"������ж�ʱ�Գ�һ������צӰ����������$n",
        "lvl"    : 60,
        "skills_name" : "ӥ������",
]),
([        "action" : "$N���Ĳ��ض���ʹһʽ"BLU"��������ˮ��"NOR"�����λ���һ����������$n",
        "lvl"    : 70,
        "skills_name" : "������ˮ",
]),
([        "action" : "$N΢΢һЦ��ʹһʽ"HIY"������ڡ�"NOR"��˫�ֻó�������,ֱ����$n��$l",
        "lvl"    : 80,
        "skills_name" : "�����",
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yunlong-shou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������צ������֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("��������񹦻�򲻹����޷�ѧ����צ��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("�������̫�����޷�������צ��\n");

        if ((int)me->query_skill("claw",1) < 100)
                return notify_fail("��Ļ���צ����򲻹����޷�ѧ����צ��\n");

        if ((int)me->query_skill("claw",1) < (int)me->query_skill("yunlong-zhua",1))
                return notify_fail("��Ļ���צ��ˮƽ���ޣ��޷�����ѧ����צ��\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<30 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<20 )
                return notify_fail("�����������������צ��\n");
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
        int d_e1 = 40;
        int d_e2 = 10;
        int p_e1 = -15;
        int p_e2 = -40;
        int f_e1 = 250;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("yunlong-zhua", 1);
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
                "damage_type" : random(2) ? "����" : "ץ��",
        ]);
}
int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        if ((int)me->query_skill("yunlong-xinfa",1) < 100)
        return 0.7;
        else if ((int)me->query_skill("yunlong-xinfa",1) > 200)
        return 1.4;
        else return ( ((int)me->query_skill("yunlong-xinfa",1)-100)/100*0.7+0.7 );
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("yunlong-zhua", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("zhua_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "remain": -1,
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "������ͻȻһ�����,����ҧ�ÿ������죬����������$N" HIW "ץ�ϵ���Ѫ��ץ����\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yunlong-zhua", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"yunlong-zhua/" + action;
}
int help(object me)
{
        write(HIC"\n����צ��"NOR"\n");
        write(@HELP

    ��ػ��������书���½��ϳ�����������Ѫ��ץ���𽭺�����
С֮���������ҡ�
    ���������ֻ�����

        ѧϰҪ��
                ����צ��40��
                �����ڹ�50��
                ������50��
                ����350
                ��Ӧ�������ķ�
HELP
        );
        return 1;
}
