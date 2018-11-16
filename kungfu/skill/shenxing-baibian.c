// shenxing-baibian.c ���аٱ�
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$nһʽ"HIC"��������ˮ��"NOR"�����㣬�Ų��ƣ�������������ˮ��ֱ�������ࡣ\n",
"$nһʽ"BLU"��Ǳ��ҹ�С�"NOR"����Ȼһ������ȫ�����ض��У���ʱ������$N���������ơ�\n",
"$nһʽ"HIW"���Ʋ����Ρ�"NOR"���㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
"$nһʽ"MAG"������Ӱ��"NOR"��һת��䣬����˷�Ʈ����������$n����Ӱ����$N�����޴롣\n",
"$nһʽ"HIB"���貨΢����"NOR"����̤�㣬��תǬ������һ�Σ��㵽����Զ�ĵط���\n",
"$nһʽ"HIM"�����ϲ�¥��"NOR"�����ڿ��У������������һ�㣬��$Nͷ���ڿն�����\n",
"$nһʽ"HIW"�����ӳ�ˮ��"NOR"������һ����ȫ��Ϊһ����Ӱ�����ĵش�$Nͷ��Ʈ�䡣\n",
"$nһʽ"HIG"�����·ת��"NOR"�����������ݰ㼱ת����ʱһ������ӿ������$N���Զ�����\n",
"$nһʽ"GRN"�������ﲨ��"NOR"������ٿ�Ĵ�$N����ǰֱ�Ƶ����$N�ɴ������ۣ��������ԡ�\n",
"$nһʽ"HIY"�����ӻ�ͷ��"NOR"������ٿ�Ĵ�$N����ǰƮ��������һ˦������֮����\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if( query("kar", me)<25
              || query("int", me)<21 )
                return notify_fail("��������Ե�������аٱ䡣\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<8 )
                return notify_fail("�������̫���ˣ����������аٱ䡣\n");
        me->receive_damage("qi", 40);
        addn("neili", -8, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        if( query("skybook/luding/dubi", me))return 1.4;
        else        return 0.9; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shenxing-baibian", 1) < 50 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shenxing-baibian", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                 result += (["msg" : HIC "$n" HIC "ʩչ���аٱ䣬�����ϣ�һת��䣬����˷�Ʈ����������$n����Ӱ��\n"
                                    HIC "$N" HIC "�����޴룬ͷ�Է��裬ֻ�������涼��$n����Ӱ����������������ա�\n" NOR]);
                return result;
        }
}

int help(object me)
{
        write(HIC"\n���аٱ䣺"NOR"\n");
        write(@HELP

    ���аٱ���������ľɣ���������������Ṧ�������������ĸ��С�

        ѧϰҪ��
           һ���Ļ�Ե���������ѧϰ
HELP
        );
        return 1;
}
