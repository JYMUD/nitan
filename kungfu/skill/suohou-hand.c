// suohou-hand ����������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int lvl_temp;
string *action_msg = ({
        "$N�������������������ָ���ţ�����$n�ľ�����ץ",
        "ֻ��һ�󾢷�ֱ����ǰ$N�����������ֱָȡ$n����ɤ�ʺ�",
        "$N����һ�ӣ���$n�����������������ţ����ּ�̽������$n�ĺ�ͷץ��",
        "$N���μ��������䵽$n�����һ˫����Ĵ���ץ��$n�ĺ�",
        "$N˫������������޹ǣ����������һ�㣬������ס$n�Ĳ��Ӳ���",
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }
int valid_combine(string combo) { return combo=="lianhua-zhang"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("��Ļ���������򲻵���\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�����������ֱ�����֡�\n");

        if( query("qi", me)<50 )
                return notify_fail("����������������������֡�\n");
        if( query("neili", me)<15 )
                return notify_fail("����������������������֡�\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
        lvl_temp = random((int)me->query_skill("suohou-hand", 1));
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n���������֣�"NOR"\n");
        write(@HELP

    ����������Ϊؤ����似��
    ���������ֻ�����

        ѧϰҪ��
                ��������20��
                ����100
HELP
        );
        return 1;
}

