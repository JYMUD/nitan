// yiwei-dujiang.c ��������һέ�ɽ�

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$nһʽ"HIW"��һέ�ɽ���"NOR"��ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n",
"$nһʽ"BLU"�������Ӳ���"NOR"��˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n",
"$nһʽ"HIG"���Ʋ����Ρ�"NOR"���㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
"$nһʽ"HIC"������Ӱ��"NOR"��һת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n",
"$nһʽ"HIY"���������ա�"NOR"��ȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
"$nһʽ"GRN"������˫�ɡ�"NOR"�������������������ݷ����У���$Nͷ����Ծ������\n",
"$nһʽ"HIY"��������ˮ��"NOR"��˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
"$nһʽ"HIG"���ɷ�鳲��"NOR"�����������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n",
});


int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if( query("dex", me)<25 || query("int", me)<25 )
               return notify_fail("������������һέ�ɽ�����С��Ū�����ȡ�\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("�������̫���ˣ��޷���ϰһέ�ɽ���\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("yiwei-dujiang", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

int difficult_level()
{
        return 300;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yiwei-dujiang", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yiwei-dujiang", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "һ�С����ѵ�ˮ�����ż�����һ�㣬����������"
                                            "��ʱ,$Nһ��ʧ�֣�\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "$n" HIY "һ�����׾Թ�϶��������һ�࣬����һ�ݣ�"
                                            "$N��Ȼһ�й�ȥ���Ѿ��ղ�סȥ�ƣ�\n" NOR]);
                        if (! ob->is_busy())
                                ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "ʹ�������Ӵ��֡�����һ��ƽƽ�ӳ���"
                                            "һ��ת��������¡�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "һ�С����ѵ�ˮ�����ż�����һ�㣬����������,"
                                 "����$N" HIY "���Զ���$n����ͼ����ռ���Ȼ���\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "һ�����׾Թ�϶��������һ�࣬����һ�ݣ�"
                                 "$Nš����ϣ�ȫ������$n��\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "ʹ�������Ӵ��֡�����һ��ƽƽ�ӳ���"
                                 "$N��Ц����������һ�����ߴ���ȥ����ղ���$n��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

string perform_action_file(string action)
{
        return __DIR__"yiwei-dujiang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }
int river_point() {return 2;} // ���ӱ���ͨ���� Խ��Խ��
string river_go_msg() {        return HIW"$N����һ��«έ����ˮ�У������ŷ���Ծ��«έ������ƮƮ���ɹ���ˮ�档\n"NOR;}
string river_come_msg() {        return HIW"ֻ��$N����һ��«έ�Ӷ԰���������̬���������ڰ��ߡ�\n"NOR;}

int help(object me)
{
        write(HIC"\nһέ�ɽ���"NOR"\n");
        write(@HELP

    ��������һέ�ɽ�

        ѧϰҪ��
           �����ڹ�10��
HELP
        );
        return 1;
}


