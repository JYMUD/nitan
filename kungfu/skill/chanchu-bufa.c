// chanchu_bufa.c ��ܲ���
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "ֻ��$nһ��"HIY"���ɾ��졹"NOR"���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
        "����$nһ��ʹ��"HIY"���������졹"NOR"������Ʈ��������һ�ݣ����ѱܿ���\n",
         "$nһ��"HIY"�����뵾�"NOR"����������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$nһ��"HIY"������˳桹"NOR"������һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n"HIY"��󸷭�׶ǡ�"NOR"���㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
        "$n����һ��"HIY"�������¡�"NOR"������΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("�������̫���ˣ���������ܲ�����\n");

        if( query("neili", me)<80 )
                return notify_fail("�������������\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);

        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("chanchu-bufa", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("chanchu-bufa", 1) / 2;

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : WHT "$n" WHT "��������һ�����ֽŷɿ�ؽ�������ϵĳ���������˼�ɵ�����һ�ݣ�\n"
                                            "$Nֻ����ǰ������һ��Ǻ�˳��̣�����һƬģ����\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : WHT "$n" WHT "�������һ��������ݳ�����֮Զ��"
                                            "$N�鼱֮�£���ͷ�ĺ��������ˣ�\n" NOR]); ;

                        break;
                default:
                        result += (["msg" : WHT "$n" WHT "һ������������"
                                            "��Ȼ����һ˿�ۼ���\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = WHT "$n" WHT "��������һ�����ֽŷɿ�ؽ�������ϵĳ���������˼�ɵ�����һ�ݣ�\n"
                                 "$N" WHT "�͵���ǰһ�壬��ͻ�����̣�����$n�����\n" NOR;
                        break;
                case 1:
                        result = WHT "$n" WHT "�������һ��������ݳ�����֮Զ��\n"
                                 "$Nһ�������ͳ嵽��$n��ǰ��\n" NOR;
                        break;
                default:
                        result = WHT "$n" WHT "һ������������"
                                 "$N����Ӱ��һ��������ҧס��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;
        lvl = me->query_skill("chanchu-bufa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 40;
        if (lvl < 280) return 70;
        if (lvl < 350) return 90;
        return 110;
}


int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point() { return 1.1; }

int help(object me)
{
        write(HIC"\n��ܲ�����"NOR"\n");
        write(@HELP

    ����ɽ�����Ṧ��

        ѧϰҪ��
           ��󡹦10��
HELP
        );
        return 1;
}
