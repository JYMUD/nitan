// shenkong-xing.c �����

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$nʹ��һ��"HIC"���Ŀա�"NOR"����������Ʈȥ \n",
        "$nʹ��һ��"HIW"�����Կա�"NOR"��˫��һ�㣬Ծ������֮�� \n",
        "$nʹ��һ��"HIM"�����ա�"NOR"������һ�䣬����$N��� \n",
        "$n���һ����ʹ��һ��"HIG"���󰲿ա�"NOR"����$Nͷ��Խ�� \n",
        "$nʹ��һ��"HIY"����ա�"NOR"��������Ʈȥ��˲��������$N��ǰ \n",
        "$nʹ��һ��"HIR"����տա�"NOR"����ʱ$N��Χ����$n����Ӱ \n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("�������̫���ˣ�����������С�\n");
        me->receive_damage("qi", 10);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

int help(object me)
{
        write(HIC"\n����У�"NOR"\n");
        write(@HELP

    �������ѩɽ�µ��ӱ����Ṧ����

        ѧϰҪ��
HELP
        );
        return 1;
}
