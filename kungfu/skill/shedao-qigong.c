// shedao-qigong  �ߵ��湦
#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

/*
mapping *action = ({
([        "action" : "$Nһ��һ������һʽ����������������β���غ�������ɨ��$n��$l",
        "lvl"    : 0,
        "skill_name" : "��������"
]),
([        "action" : "$N���һ��������$w����һƬ���⣬һ�С�ҹս�˷�������$n��$l��ɨ��ȥ",
        "lvl"    : 10,
        "skill_name" : "ҹս�˷�"
]),
([        "action" : "$N��Ȼһ����Х��һ�С����Ǹ��¡�������$w�ó������׹⣬��Ϯ$n�ظ�ҪѨ",
        "lvl"    : 15,
        "skill_name" : "���Ǹ���"
]),
([        "action" : "$N���ζ�Ȼ�������ɶ࣬һʽ��ǧ��ѹ����������$w���ź�Х�ƿ����������",
        "lvl"    : 20,
        "skill_name" : "ǧ��ѹ��"
]),
([      "action" : "$N����$n�Ų�δ�ȣ�������ǰ���У���Ȼһָ����β�𴦣�������ѰѨ����ֱȡ��$n�����¡�Ѫ��Ѩ��",
        "lvl"    : 25,
        "skill_name" : "����ѰѨ"
]),
([      "action" : "$N��ͷһת��Ѹ��һ�С���ɨǧ����������Ѹ�ݣ�������������$n����·��ɨ��ȥ",
        "lvl"    : 30,
        "skill_name" : "��ɨǧ��"
]),
([        "action" : "��Ȼ�䣬$N�����ȹ⻪��ʢ��$w���ơ���������������ʱ��$nȦ�ڵ���",
        "lvl"    : 35,
        "skill_name" : "��������"
]),
([        "action" : "$N����$w���������ҷ������������뺣��ʮ��ʮ����һʽ�����ƶϷ塹��$n��$l��ɨ��ȥ",
        "lvl"    : 40,
        "skill_name" : "���ƶϷ�",
]),
([      "action" : "$N�߸�Ծ�𣬻��������е�$wһ�С�һ�����졹����һ����������$n��ͷֱ�����",
        "lvl"    : 50,
        "skill_name" : "һ������",
]),
([        "action" : "$Nһ�����ȡ�������ա�����$w��������һ�ã�˫����ס$wβ��ת���͵ú�ɨ����$n��$l",
        "lvl"    : 60,
        "skill_name" : "�������",
]),
([      "action" : "$N��Ȼ����һ�䣬ʹ�������߳��������ȷ��Ե�����֮��������$w����������Ӱ����$n",
        "lvl"    : 70,
        "skill_name" : "���߳���"
]),
([      "action" : "$N���ȴ�����$w�й�ֱ��������һ����̳�������$n��$l�������С����Ի�����",
        "lvl"    : 80,
        "skill_name" : "���Ի���"
]),
([        "action" : "$Nһʽ��һ�ȶ���������ͷһ$w������������ͷδ����һ�ɷ��ѽ�$n�Ƶ����Դ���",
        "lvl"    : 90,
        "skill_name" : "һ�ȶ���"
]),
([        "action" : "$N���С�Ⱥ�߿��衹��$wɨ��һ������Ӱ������˷�Χ��$n��Ҫ��$n��û��ʳ",
        "lvl"    : 100,
        "skill_name" : "Ⱥ�߿���"
]),
});
*/

mapping *action = ({
([        "action" : "$Nʹһ�С��ɺ����᡹����$wһ�ᣬ����$n��$l",
        "damage" : 25,
        "dodge": -30,
        "parry": -40,
        "force": 90,
        "damage_type" : "����",
        "skill_name" : "�ɺ�����"
]),
([        "action": "$Nʹ�������߳�����������΢��������$wٿ����$n��$l��ȥ",
        "damage" : 30,
        "dodge": -20,
        "parry": -10,
        "force": 140,
        "lvl"  : 30,
        "damage_type": "����",
        "skill_name" : "���߳���"
]),
([        "action": "$N����΢�������㷴�ߣ�����ת��ʹһ�С�����������������$w�Ѵ���$n$l",
        "damage" : 40,
        "dodge": -30,
        "parry": -20,
        "force": 190,
        "lvl"  : 70,
        "damage_type": "����",
        "skill_name" : "��������"
]),
([        "action" : "$Nʹһʽ��������衹��������$n������һ����˳����$w��һ�㣬$w��Ȼ���Լ��ʺ��䣬����$N��������һ����$w�ӹ����ʺ�����$n�������",
        "damage" : 50,
        "force" : 230,
        "dodge" : -45,
        "parry" : -40,
        "lvl" : 40,
        "lvl"  : 100,
        "damage_type" : "����",
        "skill_name" : "�������"
]),
([        "action": "$N�����ڵ���һ�����ʹһ�С�С����¡�����$n�������������$wֱ��$n",
        "damage" : 55,
        "dodge": -40,
        "parry": -30,
        "force": 270,
        "lvl"  : 120,
        "damage_type": "����",
        "skill_name" : "С�����"
]),
([        "action": "$N���һ����ʹһ�С�����ٶ�������������$n��ȪҪѨ������$nˤ���ڵ�",
        "dodge": -45,
        "parry": -50,
        "damage" : 60,
        "force": 330,
        "lvl"  : 140,
        "damage_type": "����",
        "skill_name" : "����ٶ�"
]),
([        "action": "$N˫��һ����������ݣ�һ�С�³�ﲦ��������ץ��$n�ҽ����ף�����$wֱ��$nС��",
        "dodge": -50,
        "damage" : 65,
        "parry": -50,
        "force": 370,
        "lvl"  : 160,
        "damage_type": "����",
        "skill_name" : "³�ﲦ��"
]),
([        "action": "$NͻȻһ���������һ�С����ཱུ������˫��һ�֣����ڼ�ͷ��˫��ֱ��$n",
        "dodge": -70,
        "damage" : 75,
        "parry": -30,
        "force": 400,
        "lvl"  : 180,
        "damage_type": "����",
        "skill_name" : "���ཱུ��"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||
               usage == "sword"||
               usage == "staff"||
               usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�ѧ�ߵ��湦.\n");

        if ((int)me->query_skill("shenlong-bashi", 1) < 100)
                return notify_fail("���������ʽ��򲻹����޷�ѧ�ߵ��湦��\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("�������̫�����޷�ѧ�ߵ��湦��\n");

        /*
        if ((int)me->query_skill("shenlong-bashi", 1) < (int)me->query_skill("shedao-qigong", 1))
                return notify_fail("���������ʽˮƽ���ޣ��޷�����ѧ�ߵ��湦��\n");
        */

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
        int d_e1 = -30;
        int d_e2 = -60;
        int p_e1 = 0;
        int p_e2 = -30;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 220;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shedao-qigong", 1);
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

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<70 )
                return notify_fail("��������������ߵ��湦��\n");

        me->receive_damage("qi", 55);
        addn("neili", -67, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shedao-qigong/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }