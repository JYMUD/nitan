// This program is a part of NITAN MudLIB
// youming-guizhao.c ��ڤ��צ

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N��צǰ�죬����˿˿����������һʽ��Ԫ����ϡ����͵���$n�Ķ��Ų���",
        "$N˫�����ģ�����һ����ǽ����$n����Ȼһצ�����ȴ��ġ�������ǽֱ��$n��$l",
        "$Nʹ����Ѫ������˫צ����$n��ס$l��������������������һ������Ҫ��$n�����Ƭ",
        "$N˫צ£ס$n��ʹһʽ�����������������ڹ���צ��͸��$n���ڣ�ֱϮ����ؽ�",
        "$N��͸ָ�⣬��$n����ʵʵ��ץʮ��צ��������Ϯ�塹��������������ס$n",
        "$Nһʽ���������֡�����צ���·����γ�����צӰ���ұ�һ�죬���Ȱ�ץ��$n��$l",
        "$N̽����ǰ��˳��$n���ֱ���Եֱ�ϣ�����Ϊצ��һ�С��»�Ԧħ��ץ��$n��$l",
        "$N��շ��䣬һצͻǰ����ħצ���¡�����ȫ������ָ�⣬����ޱȵز���$n",
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
       if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
               return notify_fail("��צ��������֡�\n");
       if ((int)me->query_skill("claw", 1) < 50)
               return notify_fail("��Ļ���צ����򲻹����޷�ѧϰ��\n");
       if( query("max_neili", me)<1000 )
               return notify_fail("�������̫�����޷�����ڤ��צ��\n");
       return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(60),
                "attack": 70 + random(10),
                "dodge" : -70 + random(10),
                "parry" : -70 + random(10),
                "damage_type" : "ץ��",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query_skill("youming-guizhao", 1) < 199 )
                return notify_fail("�����ڤ��צ��Ϊ������ֻ����ѧ(learn)�������������ȡ�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����ڤ��צ������֡�\n");

        if( query("qi", me)<80 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<80 )
                return notify_fail("���������������ڤ��צ��\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"youming-guizhao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( query_temp("lingjiu/youming", me )
         && !query_temp("youming_hit", me) )
        {
                set_temp("youming_hit", 1, me);
                set_temp("apply/name", ({query("name", me)+"�Ĺ�Ӱ"}), me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                delete_temp("apply/name", me);
                delete_temp("youming_hit", me);
        }
}
