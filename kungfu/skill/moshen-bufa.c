// This program is a part of NITAN MudLIB

inherit SKILL;

string *dodge_msg = ({
        "$nһ����Ц��������𣬾���������������ܹ�$N�Ĺ���������һ������Ͷȥ��\n",
        "$N����$Nʱ��$n����Ҫ���ӭս����֪������������ܿ��������Ǻ���ش���ĸо���\n",
        "$n�������������ձܿ�$N�Ĺ�������б�ɶ�����Զ��Ͷȥ����̬�������㡣\n",
        "$n���񻯳�һ��û�����������̣���������������Ʈ�ƻζ���ÿһ�̶����ϱ任λ�á�\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˣ�������ħ�񲽷���\n");
        if( query("neili", me)<50 )
                return notify_fail("�������������\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}


