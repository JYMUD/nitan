// This program is a part of NT MudLIB
// hannbing-mianzhang.c ��������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nһʽ"HIB"���󽭶�ȥ��"NOR"��˫�ƴ󿪴�ϣ�ֱ��$n��$l��ȥ",
        "lvl" : 0,
        "skill_name" : "�󽭶�ȥ"
]),
([        "action" : "$N����һ�䣬һʽ"YEL"���ƺӾ�����"NOR"��˫��������ֱ������$n��$l",
        "lvl" : 10,
        "skill_name" : "�ƺӾ���"
]),
([        "action" : "$Nʹһʽ"GRN"������ɽɫ��"NOR"��������΢����棬������ϸ�����ֱȡ$n��$l",
        "lvl" : 20,
        "skill_name" : "����ɽɫ"
]),
([        "action" : "$N����һ�֣�һʽ"MAG"�������׺���"NOR"������������������$n�����ȥ",
        "lvl" : 30,
        "skill_name" : "�����׺�"
]),
([        "action" : "$N����һת��ʹ��һʽ"HIM"��ˮ�����١�"NOR"��ֻ��������Ӱ��ס��$n��ȫ��",
        "lvl" : 40,
        "skill_name" : "ˮ������"
]),
([        "action" : "$NͻȻ����һ����ʹ��һʽ"HIG"��С����硹"NOR"���������أ�������ӯ������$n��$l",
        "lvl" : 50,
        "skill_name" : "С�����"
]),
([        "action" : "$Nʹһʽ"HIW"����ѩ��ɽ��"NOR"��˫��Ю��籩ѩ֮�ƣ��͵�����$n��$l",
        "lvl" : 60,
        "skill_name" : "��ѩ��ɽ"
]),
([        "action" : "$Nһ��"HIW"��˪�����ء�"NOR"��˫�ƴ�����ɪ������������$n��$l",
        "lvl" : 70,
        "skill_name" : "˪������"
]),
([        "action" : "$N����Ȼһ�䣬ʹ��һʽ"HIW"�����������"NOR"����Ӱǧ����ã���$n�޷�����",
        "lvl" : 80,
        "skill_name" : "�������"
]),
([        "action" : "$N��Хһ����һʽ"HIW"����˪ѩ�꡹"NOR"��˫�ƻ��裬��ͬѩ������ת������$n��$l",
        "lvl" : 90,
        "skill_name" : "��˪ѩ��"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

        if ((int)query("max_neili", me) < 800)
                return notify_fail("�������̫�����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("hanbing-mianzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĺ������ơ�\n");

        return 1;
}


int practice_skill(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if ((int)query("qi", me) < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)query("neili", me) < 40)
                return notify_fail("��������������������ơ�\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("hanbing-mianzhang", 1);
        flvl = query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("ice_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return "$n��Ȼ��ɫ��䣬һ����ս�����˼�����\n";
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
        int d_e1 = -15;
        int d_e2 = 5;
        int p_e1 = 25;
        int p_e2 = 55;
        int f_e1 = 110;
        int f_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("hanbing-mianzhang", 1);
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

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"hanbing-mianzhang/" + action;
}

int help(object me)
{
        write(HIC"\n�������ƣ�"NOR"\n");
        write(@HELP

    ����������������������ΤһЦ�Ķ����书�����ƺ�ͻẮ��
��������ʱ�������亦�ޱȡ�

        ѧϰҪ��
                �����ڹ�120��
                ����800
HELP
        );
        return 1;
}