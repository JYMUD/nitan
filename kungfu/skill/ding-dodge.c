// ding-dodge.c ���ֲ� 

inherit SKILL;

string *dodge_msg = ({
        "$n�������ĵ���������һ�����պñܹ�$N���������ơ�\n",
        "����$nǡ����������һ���������$N��һ�С�\n",
});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˣ����������ֲ���\n");
        if( query("neili", me)<40 )
                return notify_fail("�������������\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

