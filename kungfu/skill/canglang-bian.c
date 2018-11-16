// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$N�����������Ӷ�$w��ʹ��һ�С��󺣳�ɳ��������$w������$n��$l��ȥ��ȥ���䲻������\n�����Ƴ��ͣ���ͬѹ�˼�ǧ����ɳһ��",
        "$N�ֳ�$w���룬һ�С�����һ�ߡ���$wһ�˶�Ȼһ��������$nǰ�أ�������������$n��·��ס��\n��һ�������߳��������پ���$n����",
        "$N���һ��������������ʹ��һ�С������ſա������Ƽӿ죬ֻ��ʮ���ر�Ӱ�羪�Ϻ��˰���$n��$l�������",
        "$N����ת������$w��һʽ�������޲���������$wȥ������������˿���ƿ�֮����\n������֮���������$w�����������ѹε�����������",
        "$N�������߲���������ʹ��һ�С��׺�һ�ڡ���$w�Ϸ���������ɲ�Ǽ���ʮ����Ӱ������˷���$n����Ҫ������",
        "$N��Хһ����˫Ŀ�����ʢ��һ�С�ŭ�����Ρ�������չ�������ɨֱ����������������̼��ѽ�$nȫ���ס",
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 30)
        {
                return notify_fail("��ı̲��񹦻��̫ǳ��\n");
        }
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 110 + random(20),
                "attack": 80 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon, where;

        where = environment(me);

        if( !query("guanchao", where) )
                return notify_fail("����ϰ��һ������˱޷���������ôҲ���������˶��ֵľ��⡣\n");

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<60 )
                return notify_fail("����������������˱޷���\n");
        message_vision(HIC"$N��Ժ���������ӱޣ�ʹ�����뺣��ͬ���������о���������Ҳ�纣������һ�������޾���\n"NOR, me);
        addn("neili", random(3), me);
        me->recieve_damage("qi", 50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-bian/" + action;
}
