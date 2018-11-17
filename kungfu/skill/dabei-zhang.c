#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N身形急晃，施出大悲掌「" HIG "浪濤勢" NOR "」，右掌帶着切骨之勁砍向$n",
        "force" : 180,
        "attack": 23,
        "dodge" : 25,
        "parry" : 17,
        "damage": 19,
        "lvl"   : 0,
        "skill_name"  : "浪濤勢",
        "damage_type" : "內傷"
]),
([      "action" : "$N一招「" HIG "深淵勢" NOR "」，雙掌斜出，萬千道掌寒勁從四面八方席捲$n",
        "force" : 240,
        "attack": 41,
        "dodge" : 25,
        "parry" : 27,
        "damage": 25,
        "lvl"   : 30,
        "skill_name"  : "深淵勢",
        "damage_type" : "內傷"
]),
([      "action" : "$N平掌為刀施展「" HIG "鯨吞勢" NOR "」，幻出一道剛猛的掌勁颶風般裹向$n",
        "force" : 330,
        "attack": 58,
        "dodge" : 36,
        "parry" : 35,
        "damage": 39,
        "lvl"   : 60,
        "skill_name"  : "鯨吞勢",
        "damage_type" : "內傷"
]),
([      "action" : "$N反轉右掌陡然施一招「" HIG "破穹勢" NOR "」，力注左掌，橫向$n攔腰砍去",
        "force" : 410,
        "attack": 96,
        "dodge" : 81,
        "parry" : 62,
        "damage": 53,
        "lvl"   : 90,
        "skill_name"  : "破穹勢",
        "damage_type" : "內傷"
]),
([      "action" : "$N手腕一翻，揮出一道無比凌厲的掌勁直斬$n，正是「" HIG "翻海勢" NOR "」",
        "force" : 460,
        "attack": 125,
        "dodge" : 35,
        "parry" : 47,
        "damage": 78,
        "lvl"   : 120,
        "skill_name"  : "翻海勢",
        "damage_type" : "內傷"
]),
([      "action" : "$N施出「" HIG "滔天勢" NOR "」，雙手凌空舞出一個大圈，勁氣至圈中直涌$n",
        "force" : 520,
        "attack": 110,
        "dodge" : 45,
        "parry" : 40,
        "damage": 85,
        "lvl"   : 150,
        "skill_name"  : "滔天勢",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大悲神掌必須空手。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的內功火候不夠，無法練習大悲神掌。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力太弱，無法練習大悲神掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不夠，無法練習大悲神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dabei-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的大悲神掌。\n");

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
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練大悲神掌。\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100)
                return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 2)
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                return HIW "只聽「呼」的一聲，$N" HIW "掌鋒划過，頓時將$n"
                       HIW "硬生生逼退數步！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"dabei-zhang/" + action;
}