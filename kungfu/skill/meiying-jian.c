//meiying-jian ��Ӱ����
// Made by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N����$w��������£�������Ȼ����$n��$l��ȥ�Ƽ�������",
    "force" : 60,
    "damage":100,
    "dodge" : 20,
    "lvl"   : 60,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([  "action" : "$N���е�$w��ס�Ĳ���������ָ��$n��$l�����ָ���$n��$l",
    "force"  : 80,
    "dodge"  : 35,
    "damage" : 100,
    "lvl"    : 100,
    "skill_name" : "��Ӱ����",
    "damage_type" : "����"
]),
([  "action" : "$N���е�$w�����ζ���ȥ���ò��������ͻȻֱ��$n��$l",
    "force"  : 100,
    "dodge"  : 55,
    "damage" :100,
    "lvl"    : 140,
    "skill_name" : "�������",
    "damage_type" : "����"
]),
([  "action" : "$N���е�$w��Ȼ������࣬�漴����$n��$l��ȥ�������쳣",
    "force"  : 120,
    "dodge"  : 75,
    "damage" : 100,
    "lvl"    : 160,
    "skill_name" : "����Ϊʵ",
    "damage_type" : "����"
]),
([  "action" : "$N������������$wһ��һ�գ�����бб�ӳ�������$n��$l",
    "force"  : 140,
    "dodge"  : 90,
    "damage" : 100,
    "lvl"    : 200,
    "skill_name" : "ѹ¶����",
    "damage_type" : "����"
]),
([  "action" : "$N���һ��������$w��Ȼ�ó������Ӱ����������$n��$l",
    "force"  : 160,
    "dodge"  : 100,
    "damage" : 100,
    "lvl"    : 220,
    "skill_name" : "ɨ�·���",
    "damage_type" : "����"
]),
([  "action" : "$Nб������������������������$wбб�̳�������$n��$l",
    "force"  : 170,
    "dodge"  : 120,
    "damage" : 100,
    "lvl"    : 260,
    "skill_name" : "�ǹ�����",
    "damage_type" : "����"
]),
([  "action" : "$N����һ�䣬����$w���س�����Ѹ���ޱȵ���$n$lֱ�̹�ȥ",  
    "force"  : 180,
    "dodge"  : 150,
    "damage" : 100,
    "lvl"    : 300,
    "skill_name" : "��۵糸",
    "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 2500)
        return notify_fail("�������������\n");

    if ((int)me->query_skill("force") < 200)
        return notify_fail("����ڹ��ķ����̫ǳ��\n");

    if ((int)me->query_skill("dodge") < 200)
        return notify_fail("����Ṧ���̫ǳ��\n");

    if ((int)me->query_dex() < 40)
        return notify_fail("��ĺ�������������\n");

    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("meiying-jian",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (me->query_skill("meiying-jian", 1) >= 400)
        return notify_fail("����Ŀǰ����Ϊֻ��ͨ���о��ü��ܲ�����������ߡ�\n");

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("��ʹ�õ��������ԡ�\n");

    if ((int)me->query("qi") < 100)
        return notify_fail("���������������Ӱ������\n");

    if ((int)me->query("neili") < 100)
        return notify_fail("���������������Ӱ������\n");

    me->receive_damage("qi", 80);
    me->add("neili", -80);

    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"meiying-jian/" + action;
}

