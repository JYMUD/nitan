inherit SKILL;

string *dodge_msg = ({
        "$nһ�������ضɺ�����Ծ�����ߣ������$N��һ�С�\n",
        "$n�������һ�ݣ�ʹ��һ�С������䳾�����ܹ���$N�Ĺ�����\n",
        "����$n�������һ�ݣ�ʹ��һ�С�÷����Ū�����ܹ���$N�Ĺ�����\n",
        "$nʹ��������ɳ����ǡ�ö����$N�Ĺ��ơ�\n",
        "$nһ�С�����öݡ�����̬����ض��˿�ȥ��\n"
        "����$nһ�С�̤ѩѰ÷������̬����ض��˿�ȥ��\n"
});

int valid_enable(string usage)
{
        return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˣ����������÷��׮��\n");

        if( query("neili", me)<40 )
                return notify_fail("����������������÷��׮��\n");

        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}