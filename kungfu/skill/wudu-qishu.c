// wudu-qishu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "poison"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技造詣太淺，無"
                                   "法領會深奧的五毒奇術。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("wudu-qishu", 1))
                return notify_fail("你的基本毒技水平有限，無"
                                   "法掌握更深奧的五毒奇術。\n");

        return 1;
}