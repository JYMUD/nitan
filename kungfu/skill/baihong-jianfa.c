// baihong-jianfa �׺罣��

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *action_msg = ({
        "$N������ȭ�����ֽ������飬һ���ɡ��׺�һ�֡���$w����һ����â������$n��$l",
        "$Nʹ��һ�С�ӥ���������������Ʈ������$w�͵�����$n��$l",
        "$N����һ�Σ���Ȼһʽ��������ӿ������$w������粨�Σ�Ю��һ�󾢷���$nɨȥ",
        "$Nһ����[������һ�٣��漴������$w���һ���⻷��һ�С������޹⡹������ϵĻҳ�ɨ$n��$l",
        "$N��ת���ӣ��ƺ���Ҫ���ܣ���Ȼ����һת��ʹ��һ�С����ֽ��������⻯�������ǹ�����$n��$l",
        "$N������һ�����������Ž�����һ�С������㺣������$w�����ü�����â����$n��$l",
        "$N�����������࣬һ�С���ӥ���衹���ӳ�����$w��ƮȻ����$n��$l",
        "$N���־�$w����������һ�ڣ�һ�С���˪ѩ�꡹��$w�������㺮������$n",
        "$N��������ȭ�����һ�У�ͻȻ���纮˪���ӳ�����$w����$n��$l����һ�С���ѩ��ɽ��",
        "$N����$wһָ������¶��΢΢��Ц�ݣ��������ٵ�����ȫ��һ�С��׺��������$w���������â����������$n��$l",
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(21),
                "attack": 20 + random(11),
                "dodge" : -30 + random(11),
                "parry" : -30 + random(11),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("��������������׺罣����\n");
        if( query("neili", me)<70 )
                return notify_fail("��������������׺罣����\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baihong-jianfa/" + action;
}

