// ding-unarmed.c һ��һ��ȭ

inherit SKILL;

string *action_msg = ({
        "$N��������һĨ����$n��$l��ȥ",
        "$N����һ�ᣬ����$n��$l",
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 210 + random(50), 
                "attack": 30 + random(10), 
                "dodge" : 30 + random(10), 
                "parry" : 30 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<40 )
                return notify_fail("�������������һ��һ��ȭ��\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
        return 1;
}

