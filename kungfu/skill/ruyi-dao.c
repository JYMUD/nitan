// ruyi-dao.c 如意刀

#include <ansi.h>;

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w斜指，一招"BLU"「停車問路」"NOR"，反身一頓，一刀向$n的$l撩去",
        "lvl"    : 0,
        "skill_name" : "停車問路",
]),
([        "action" : "$N一招"HIW"「童子掛畫」"NOR"，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "lvl"    : 8,
        "skill_name" : "童子掛畫",
]),
([        "action" : "$N展身虛步，提腰躍落，一招"MAG"「推窗望月」"NOR"，刀鋒一卷，攔腰斬向$n",
        "lvl"    : 16,
        "skill_name" : "推窗望月",
]),
([        "action" : "$N一招"HIG"「開門見山」"NOR"，$w大開大闔，自上而下划出一個大弧，筆直劈向$n",
        "lvl"    : 24,
        "skill_name" : "開門見山",
]),
([        "action" : "$N手中$w一沉，一招"CYN"「臨溪觀魚」"NOR"，雙手持刃攔腰反切，砍向$n的胸口",
        "lvl"    : 33,
        "skill_name" : "臨溪觀魚",
]),
([        "action" : "$N揮舞$w，使出一招"BLU"「張弓望的」"NOR"，上劈下撩，左擋右開，齊齊罩向$n",
        "lvl"    : 42,
        "skill_name" : "張弓望的",
]),
([        "action" : "$N一招"YEL"「風送輕舟」"NOR"，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "lvl"    : 51,
        "skill_name" : "風送輕舟",
]),
([        "action" : "$N盤身駐地，一招"HIC"「川流不息」"NOR"，揮出一片流光般的刀影，向$n的全身涌去",
        "lvl"    : 60,
        "skill_name" : "川流不息",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<350 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候太淺。\n");

        if (me->query_skill("blade", 1) < me->query_skill("ruyi-dao", 1))
                return notify_fail("你的基本刀法火候太淺，難以領會更高深的如意刀法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
        return notify_fail("你的體力不夠練如意刀。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
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
        int d_e1 = 45;
        int d_e2 = 25;
        int p_e1 = -5;
        int p_e2 = -25;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 150;//110;
        int m_e2 = 350;//220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("ruyi-dao", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "擦傷",
        ]);
}
int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        return 1.3;
}

string perform_action_file(string action)
{
        return __DIR__"ruyi-dao/" + action;
}

int help(object me)
{
        write(HIC"\n如意刀："NOR"\n");
        write(@HELP

    如意刀是逍遙派的刀法。

        學習要求：
                北冥神功10級
                內力50
HELP
        );
        return 1;
}
