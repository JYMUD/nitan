// xiaoyaoyou.c ��ң��ȭ��

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$nһ��"RED"�����ѵ�ˮ��"NOR"�������$N��һ�С�\n",
        "$n�������һ�ݣ�ʹ��һ��"HIW"��ϸ���ɷ��ơ�"NOR"���ܹ���$N�Ĺ�����\n",
        "$nʹ��"BLU"���黳���ȡ�"NOR"��ǡ�ö����$N�Ĺ��ơ�\n"
        "����$nһ��"HIY"�����ѵ�ˮ��"NOR"����Ʈ��������һ�ݣ����ѱܿ���\n",
        "$n������ת��һ��"MAG"��ϸ���ɷ��ơ�"NOR"ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$n����һ�ã�һ��"HIY"���黳���ȡ�"NOR"$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻��أ�һ��"GRN"�����ѵ�ˮ��"NOR"���Դܿ����ߣ����˿�ȥ��\n",
        "$n����΢�Σ�һ��"HIB"���黳���ȡ�"NOR"�о����յرܿ���$N��һ�С�\n"
});
mapping *action = ({
([      "action" : "$Nһ�������һ�С����б�꡹ֱϮ$n��$l�����ް��ۼ�",
        "force"  : 30,
        "dodge"  : 30,
        "damage" : 2,
        "lvl"    : 0,
        "skill_name"  : "���б��",
        "damage_type" : "����"
]),
([      "action" : "$Nת��������һ�С��������ϡ��������㣬���ƻ���$n������",
        "force"  : 50,
        "dodge"  : 40,
        "damage" : 5,
        "lvl"    : 10,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N�鲽����һ�С���Ҷ���⡹������һת������$n",
        "force"  : 60,
        "dodge"  : 45,
        "damage" : 10,
        "lvl"    : 20,
        "skill_name"  : "��Ҷ����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С���·δ������˫�ƻ���������Ӱ����ƮƮ������$n",
        "force"  : 70,
        "dodge"  : 55,
        "damage" : 15,
        "lvl"    : 34,
        "skill_name"  : "��·δ��",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С������������������ָ΢΢�ſ�������n������",
        "force"  : 90,
        "dodge"  : 70,
        "damage" : 20,
        "lvl"    : 45,
        "skill_name"  : "�������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��һ�С���ң���䡹��һ���ĳ����·�ʳ����˼��̻�",
        "force"  : 110,
        "dodge"  : 75,
        "damage" : 25,
        "lvl"    : 59,
        "skill_name"  : "��ң����",
        "damage_type" : "����"
]),
([      "action" : "$N����Ʈ����һ�С�������������˫�������������$n",
        "force"  : 120,
        "dodge"  : 80,
        "damage" : 30,
        "lvl"    : 80,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
});

int valid_enable(string usage)
{
        return usage == "dodge"
            || usage == "parry"
            || usage == "strike";
}

int valid_combine(string combo)
{
        return combo == "jueming-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("ѧϰ��ң���Ʒ�������֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�ѧ��ң���Ʒ���\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ̫�����޷�����ң���Ʒ���\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xiaoyaoyou", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ң���Ʒ���\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xiaoyaoyou", 1))
                return notify_fail("��Ļ����Ṧˮƽ���ޣ��޷������������ң���Ʒ���\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("�������̫���ˣ��޷���ϰ��ң�Ρ�\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int)me->query_skill("xiaoyaoyou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }

string perform_action_file(string action)
{
        return __DIR__"xiaoyaoyou/" + action;
}

int help(object me)
{
        write(HIC"\n��ң�Σ�"NOR"\n");
        write(@HELP

    ��ң����ؤ�ﱾ���Ṧ����

        ѧϰҪ��

           ��������10�����к��߹�ָ��
HELP
        );
        return 1;
}
