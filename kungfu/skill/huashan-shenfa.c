// huashan-shenfa.c ��ɽ��

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$nһʽ"HIY"���������᡹"NOR"�������������������ݷ����У���$Nͷ����Ծ������\n",
"$nһʽ"HIC"��������ϼ��"NOR"����һ����磬�滺��������$N���������ơ�\n",
"$nһʽ"HIB"����س�����"NOR"����ӯ��һԾ��һת�ۼ���Ƶ���$N�����\n",
"$nһʽ"HIY"��ȴ����ɡ�"NOR"��һת��䣬���Ʈ����һ��Զ\n",
"$nһʽ"HIM"�����ճ�����"NOR"��ȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
"$nһʽ"HIY"�������ա�"NOR"��������һֻ�����������ˮ�ػ������ࡣ\n",
"$nһʽ"HIW"���������ǡ�"NOR"��˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
"$nһʽ"GRN"���������Ρ�"NOR"�����ζ��ر��Ʈ����������$N�޷����塣\n",
"$nһʽ"HIM"���������롹"NOR"������һ����ʸ������Χ��$N���ٵ������˼�Ȧ��\n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("�������̫���ˣ���������ɽ����\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n��ɽ����"NOR"\n");
        write(@HELP

    ��ɽ��Ϊ��ɽ�����Ṧ����

        ѧϰҪ��
          ��ϼ��10��
HELP
        );
        return 1;
}
