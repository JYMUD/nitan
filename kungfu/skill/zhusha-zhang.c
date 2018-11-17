//shusha-zhang.c 硃砂掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIB"「虛步推手」"NOR"，似掌非掌，雙手一揮，直向$n的$l擊去",
        "lvl"    : 0,
        "skill_name"  : "虛步推手"
]),
([        "action" : "$N身形一轉，一式"BLU"「雙封掌」"NOR"，左掌斜向外側，掌心向下，封向$n的$l",
        "lvl"    : 20,
        "skill_name"  : "雙封掌"
]),
([        "action" : "$N使一式"HIC"「破風穿雲」"NOR"，身形前沖，雙掌向前插出，直取$n的$l",
        "lvl"    : 40,
        "skill_name"  : "破風穿雲"
]),
([        "action" : "$N兩掌一分，一式"RED"「引針腰斬」"NOR"，左掌反擒$n的手部，右掌向$n的腰脅推劈",
        "lvl"    : 60,
        "skill_name"  : "引針腰斬"
]),
([        "action" : "$N右掌拍下，一式"GRN"「反摔掌」"NOR"，左掌以掌背反摔$n的頭部",
        "lvl"    : 80,
        "skill_name"  : "反摔掌"
]),
([        "action" : "$N突然身形一緩，使出一式"MAG"「偷漏掌」"NOR"，右腳前扣，右掌向外圈手，又外向里拍向$n的$l",
        "lvl"    : 100,
        "skill_name"  : "偷漏掌"
]),
([        "action" : "$N使一式"HIG"「單臂挑山」"NOR"，右掌向下伸出，掌心翻轉，猛地向上拍向$n的$l",
        "lvl"    : 120,
        "skill_name"  : "單臂挑山"
]),
([        "action" : "$N一聲大喝，一招"HIG"「開門見山」"NOR"，招式沉穩，雙掌暗紅，迎面拍向$n的頭部",
        "lvl"    : 150,
        "skill_name" : "開門見山"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練硃砂掌必須空手。\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 10)
                return notify_fail("你的歸元吐納法火候不夠，無法學硃砂掌。\n");
        if( query("max_neili", me)<20 )
                return notify_fail("你的內力太弱，無法練硃砂掌。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練硃砂掌。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("zhusha-zhang")) > 60 &&
                (victim->query_condition("warm_poison") < 50))
                victim->apply_condition("warm_poison", random(me->query_skill("zhusha-zhang")/20) + 1 + victim->query_condition("warm_poison"));
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -15;
        int d_e2 = 5;
        int p_e1 = 25;
        int p_e2 = 55;
        int f_e1 = 120;
        int f_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("zhusha-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n硃砂掌："NOR"\n");
        write(@HELP

    硃砂掌是鐵掌幫入門掌法。掌中蘊毒，幫中弟子在習得鐵掌之前，
仗此遊走江湖。

        學習要求：
                歸元吐納法10級
                內力修為20
HELP
        );
        return 1;
}
