inherit FORCE;

mapping *action = ({
([  "action": "$N飛身一躍而起，身法陡然加快，朝着$n$l快速攻出數十拳",
    "lvl"   : 0,
    "damage_type" : "瘀傷"
]),
([  "action": "$N沉身運氣，一拳擊向$n，剎那間，$N全身竟浮現出一道金光",
    "lvl"   : 0,
    "damage_type" : "瘀傷"
]),
});

string main_skill() { return "jiuyang-shengong"; }

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shaolin-jiuyang", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("shaolin-jiuyang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[random(i)];
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("yinyang-shiertian", 1))
                return notify_fail("你已將九陽神功融匯貫通，合成了普天之下最強"
                                   "的武功，不必再分開學習了。\n");

        if ((int)me->query_skill("jiuyang-shengong", 1))
                return notify_fail("你已將三種九陽神功全部融匯貫通，不必再分開"
                                   "學習了。\n");

        if( query("gender", me) == "無性" && query("shaolin-jiuyang", me)>9 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的少林九"
                                   "陽神功。\n");

        if( query("con", me)<34 )
                return notify_fail("你的先天根骨孱弱，無法修鍊少林九陽神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功太差，無法學習少林九陽神功。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為太淺，無法學習少林九陽神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("少林九陽神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"jiuyang-sub/" + func;
}
