#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N˫��ƽ�죬�����ӳ���һʽ"GRN"������էչ��"NOR"��ָ����ӯƯ�������ᷴ��$n��$l",
        "lvl" : 10,
        "skill_name" : "����էչ"
]),
([        "action" : "$N������ָ����һ�գ�һʽ"HIG"���ط������"NOR"����ָ��Ȼңң����$n��$nֻ������ɼ���Ϯ���Լ��崦��Ѩ",
        "lvl" : 0,
        "skill_name" : "�ط����"
]),
([        "action" : "$NͻȻ����Ծ���գ�һ������ת���������䣬һʽ"MAG "�����Ƿɻ���"NOR"������$n��ͷ��",
        "lvl" : 10,
        "skill_name" : "���Ƿɻ�"
]),
([        "action" : "$NͻȻԾ��˫�������������罣�����缲�������һʽ"HIM "���꼱���"NOR"������$n��ȫ��",
        "lvl" : 10,
        "skill_name" : "�꼱���"
]),
([        "action" : "$N���ֻ������ĳ��죬������ֲ�£ʳָ��ָ�����������һʽ"CYN"���Ǻ����졹"NOR"��ֱָ$n������",
        "lvl" : 20,
        "skill_name" : "�Ǻ�����"
]),
([        "action" : "$NͻȻ������ˣ�����һʽ"HIW"�������׷ɡ�"NOR"��ƽ�����˫����$n�ĺ�����������",
        "lvl" : 30,
        "skill_name" : "�����׷�"
]),
([        "action" : "$NͻȻ����Ծ������Ю�ž�����ӿ�ĳ����������������ƺ�ͻ�������һʽ"HIR"������׷�¡�"NOR"��������ǰ��$n��$l��ȥ",
        "lvl" : 30,
        "skill_name" : "����׷��"
]),
([        "action" : "$Nʹһʽ"HIC"�������®��"NOR"��ȫ��ͻȻ������ת��˫�ƺ�ǰ�����͵�����$n���ؿ�",
        "lvl" : 40,
        "skill_name" : "�����®"
]),
([        "action" : "$Nǰ��һ�࣬һʽ"HIB"�����ƺ�ȡ�"NOR"�������罣��һ����������Ϯ��$n������",
        "lvl" : 50,
        "skill_name" : "���ƺ��"
]),
([        "action" : "$Nʹһʽ"HIW"���׺羭�졹"NOR"��˫���������Ȧ������һ������$n��$l�ȥ",
        "lvl" : 70,
        "skill_name" : "�׺羭��"
]),
([        "action" : "$N˫��ʳָ����ָһ�ͣ�һʽ"HIM"������������"NOR"��һ��ǿ�ҵ�����ӿ��$n��ȫ��",
        "lvl" : 60,
        "skill_name" : "��������"
]),
([        "action" : "$Nһʽ"HIC"����Ӣ���졹"NOR"��˫������ǰ��ת���ƻ����裬����ǵ�ֱָ��$n��$nֻ�������ƻ����ۻ����ҡ�",
        "lvl" : 99,
        "skill_name" : "��Ӣ����"
])
});
/*
mapping *action = ({
([      "action" : "$N������ָ����һ�գ�һʽ���ط����������ָ��Ȼ����$n�崦��Ѩ",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "�ط����"
]),
([      "action" : "$N��Ȼһ������ת���������䣬һʽ�����Ƿɻ���������$n��ͷ��",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "����",
        "skill_name"  : "���Ƿɻ�"
]),
([      "action" : "$NͻȻԾ��˫�������������罣��һʽ���꼱��񡹣�����$n��ȫ��",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "����",
        "skill_name"  : "�꼱���"
]),
([      "action" : "$NͻȻ������ˣ�һʽ�������׷ɡ���ƽ�����˫����$n��������",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "����",
        "skill_name"  : "�����׷�"
]),
([      "action" : "$NͻȻ����Ծ�����Ʒ�����һʽ������׷�¡���������ǰ��$n��$l��ȥ",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "����",
        "skill_name"  : "����׷��"
]),
([      "action" : "$Nʹһʽ���׺羭�졹��˫���������Ȧ������һ������$n��$l�ȥ",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "����",
        "skill_name"  : "�׺羭��"
]),
([      "action" : "$Nһʽ����Ӣ���졹��˫������ǰ��ת���ƻ����裬����ǵ�ֱָ��$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "����",
        "skill_name"  : "��Ӣ����"
]),
//��������
([      "action" : "[1;32m$Nһʽ�������项��˫��������������ǰ�ڶ�����ʱһ�����������ٳ���$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "����",
        "skill_name"  : "[1;32m������[2;37;0m"
]),
([      "action" : "[1;37m$N����Ӣ��������������ɣ�һ�С�����ն������Ȼ��շ��𣬵�ͷ��$nնȥ[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "����",
        "skill_name"  : "[1;37m����ն[2;37;0m"
]),
([      "action" : "[1;36m$N����Ӣ�������뷵豹��澳�磬����ȫ��������һ�С������̡����纣�˰��

������$nӿȥ����ʱ���ɷ�Χ��ɳʯ�������ۼ�$n���޴�����[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "����",
        "skill_name"  : "[1;36m������[2;37;0m"
])
});
*/
int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����Ӣ���Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧ��Ӣ���ơ�\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("�������̫�����޷�����Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������Ӣ���ơ�\n");

        /*
        if( query("character", me) == "���ռ�թ" )
                return notify_fail("ѧϰ��Ӣ������Ҫ������ػ���û�д˵��ػ����޷�����ġ�\n");
        */

        if( query("str", me)<22 )
                return notify_fail("������������㣬�޷�������Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("��Ļ����Ʒ�������죬�޷�������Ӣ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("��Ļ����Ʒ�������죬�޷�������Ӣ���ơ�\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -35;
        int d_e2 = -15;
        int p_e1 = -45;
        int p_e2 = -35;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenzhang", 1);
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
        if( query("qi", me)<300 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<100 )
                return notify_fail("���������������Ӣ���ơ�\n");

        me->receive_damage("qi", 45);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n��Ӣ���ƣ�"NOR"\n");
        write(@HELP

    ��Ӣ������̥����Ӣ�񽣣����ƴ�����������ѷ��
    ��������ɨҶ�Ȼ�����

        ѧϰҪ��
                �̲���15��
                ����100
HELP
        );
        return 1;
}
