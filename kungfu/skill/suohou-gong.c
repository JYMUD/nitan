#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *action_msg = ({
        "$N�������������������ָ���ţ�����$n�ľ�����ץ",
        "ֻ��һ�󾢷�ֱ����ǰ$N�����������ֱָȡ$n����ɤ�ʺ�",
        "$N����һ�ӣ���$n�����������������ţ����ּ�̽������$n�ĺ�ͷץ��",
        "$N���μ��������䵽$n�����һ˫����Ĵ���ץ��$n�ĺ�",
        "$N˫������������޹ǣ����������һ�㣬������ס$n�Ĳ��Ӳ���",
});

mapping *action = ({
([      "action": "$Nһ�����ȣ�˫���繳��ꫣ�����$n��$l",
        "force" : 100,
        "attack": 28,
        "dodge" : 17,
        "parry" : 0,
        "damage": 13,
        "lvl"   : 0,
        "damage_type" : "ץ��"
]),
([      "action": "$N����һԾ��ֱ�˶��ϣ�����ֱֱץ��$n��$l",
        "force" : 130,
        "attack": 35,
        "dodge" : 20,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 10,
        "damage_type" : "ץ��"
]),
([      "action": "$N˫��ƽ�죬ʮָ΢΢���¶���������ץ��$n��$l",
        "force" : 160,
        "attack": 39,
        "dodge" : 32,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 20,
        "damage_type" : "ץ��"
]),
([      "action": "$N������Ϣ��������$n��ǰ���͵�һצ����ץ��$n��$l",
        "force" : 172,
        "attack": 42,
        "dodge" : 38,
        "parry" : 19,
        "damage": 29,
        "lvl"   : 40,
        "damage_type" : "ץ��"
]),
([      "action": "$N˫��ƽ����ǰ�����ֻ�ס���ţ����ֶ�Ȼץ��$n��$l",
        "force" : 187,
        "attack": 45,
        "dodge" : 41,
        "parry" : 21,
        "damage": 33,
        "lvl"   : 60,
        "damage_type" : "ץ��"
]),
([      "action": "$N�ͺ�һ����˫�ֻ���Ϊצ��һǰһ��ץ��$n��$l",
        "force" : 203,
        "attack": 51,
        "dodge" : 49,
        "parry" : 22,
        "damage": 36,
        "lvl"   : 80,
        "damage_type" : "ץ��"
]),
([      "action": "$N����б��$n����֮�䣬����ȡĿ������ֱ��$n�ĺ�",
        "force" : 245,
        "attack": 56,
        "dodge" : 53,
        "parry" : 27,
        "damage": 41,
        "lvl"   : 100,
        "damage_type" : "ץ��"
]),
([      "action": "$N���һ����˫צ����������׼$n��$l����ץ��",
        "force" : 270,
        "attack": 61,
        "dodge" : 58,
        "parry" : 38,
        "damage": 45,
        "lvl"   : 120,
        "damage_type" : "ץ��"
])
});

int valid_enable(string usage)
{
        return usage == "claw" ||  usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������������֡�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�ѧ������\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ̫�����޷���������\n");

        if ((int)me->query_skill("claw", 1) < 80)
                return notify_fail("��Ļ���ץ���������޷�ѧ������\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("suohou-gong", 1))
                return notify_fail("��Ļ���ץ�����ˮƽ���ޣ��޷����������������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

/*
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("suohou-gong", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}
*/
mapping query_action(object me, object weapon)
{
        int lvl_temp = random((int)me->query_skill("suohou-gong", 1));
        if( lvl_temp>100 && query("neili", me)>800 )
        {
                if (lvl_temp <= 150)
                {
                        addn("neili", -50, me);
                        return ([
                                "action":"$N����һ̧���������ᣬ������ϢϮ��$n��������צͻȻ������������\n֮�������Һϻ�ֱȡ$n�ĺ�����",
                                "damage_type": "����",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(100),
                        ]);
                }
                else
                {
                        addn("neili", -80, me);
                        return ([
                                "action":"$N���������������׺ݣ���¶�׹⣬���в���$n��Ҫ����λ���ƺ�Ҫ��$n���̻����\n"
                                 "$N˫������������У���������������$n��������������òҿ��ޱȡ�",
                                "damage_type": "ץ��",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(200),
                        ]);
                }
        }
        return ([
                "action"     : action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"ץ��":"����",
                "dodge"      : -35+random(20),
                "parry"      : 25+random(30),
                "force"      : 80+random(100),
        ]);
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������������ϰ��\n");

        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<80 )
                return notify_fail("�������������������\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suohou-gong/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n������"NOR"\n");
        write(@HELP

    ����Ϊؤ����似��

        ѧϰҪ��
                ��������20��
                ����100
HELP
        );
        return 1;
}
