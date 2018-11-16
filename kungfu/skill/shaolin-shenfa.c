// shaolin-shenfa.c ������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$nһʽ"HIW"��һέ�ɽ���"NOR"��ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n",
        "$nһʽ"BLU"�������Ӳ���"NOR"��˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n",
        "$nһʽ"HIC"���Ʋ����Ρ�"NOR"���㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
        "$nһʽ"HIG"������Ӱ��"NOR"��һת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n",
        "$nһʽ"HIY"���������ա�"NOR"��ȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
        "$nһʽ"HIB"������˫�ɡ�"NOR"�������������������ݷ����У���$Nͷ����Ծ������\n",
        "$nһʽ"HIY"��������ˮ��"NOR"��˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
        "$nһʽ"GRN"���ɷ�鳲��"NOR"�����������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("�������̫���ˣ��޷�����ϰ��������\n");

        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // ���ӱ���ͨ���� Խ��Խ��
string river_go_msg() {        return HIW"$N����һ��«έ����ˮ�У������ŷ���Ծ��«έ������ƮƮ���ɹ���ˮ�档\n"NOR;}
string river_come_msg() {        return HIW"ֻ��$N����һ��«έ�Ӷ԰���������̬���������ڰ��ߡ�\n"NOR;}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shaolin-shenfa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shailin-shengfa", 1);

        // һ��������㷨
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                // ȥ�����е��˺�д��

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "һʽ���ɷ�鳲�������������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(3));
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "һʽ��һέ�ɽ�����ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(1));
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "һʽ������Ӱ����һת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

string perform_action_file(string action)
{
        return __DIR__"shaolin-shenfa/" + action;
}

int help(object me)
{
        write(HIC"\n��������"NOR"\n");
        write(@HELP

    ������Ϊ���ֱ����Ṧ���������Ṧ�������¡�

        ѧϰҪ��
                ��Ԫһ����10��
HELP
        );
        return 1;
}

