inherit SKILL;

int is_ultimate_skill() { return 1; }

string *dodge_msg = ({
        "$n����һͨ���ܹ���$N�Ĺ��ơ�\n",
});

int valid_enable(string usage) { return (usage == "dodge");}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˣ��޷�������ϰ��\n");

        me->receive_damage("qi", 40);
        return 1;
}
