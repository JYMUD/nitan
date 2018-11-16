// tiyunzong.c ������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "ֻ��$nһ��"HIW"���׺׳��졹"NOR"���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
        "$nһ��"BLU"�����ӷ���"NOR"������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
        "$nʹ��"HIY"������չ�᡹"NOR"����һ��ƮȻ�ݳ��������ŵء�\n",
        "����$nһ��"HIC"���׺׳��졹"NOR"����Ʈ��������һ�ݣ����ѱܿ���\n",
        "$n������ת��һ��"HIB"�����ӷ���"NOR"ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$nһ��"YEL"������չ�᡹"NOR"����һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻���һ��"HIC"���׺׳��졹"NOR"�����Դܿ����ߣ����˿�ȥ��\n",
        "$n����΢�Σ�һ��"MAG"�����ӷ���"NOR"�о����յرܿ���$N��һ�С�\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("������Ṧ��Ϊ���ޣ��������������ݡ�\n");

        if( query("max_neili", me)<800 )
                return notify_fail("��������Ϊ̫ǳ���������������ݡ�\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 || query("neili", me)<10 )
                return notify_fail("�������̫���ˣ��޷���ϰ�����ݡ�\n");
        me->receive_damage("qi", 50);
        addn("neili", -10, me);
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

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("tiyunzong", 1);

        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tiyunzong", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("tiyunzong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "һ�С��׺׳��졹���������ϱ�ֱ���������࣬"
                                            "$N��ȻʧȥĿ�꣬����ʧ�֣�\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "һ�������ӷ���������ݳ�����֮Զ��"
                                            "$Nһ��ʧ�֣�����֮����¶������\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "ʹ��������չ�᡹����һ��ƮȻ�ݳ���"
                                            "��Ȼ��������������ŵء�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "һ�С��׺׳��졹���������ϱ�ֱ���������࣬"
                                 "����$N" HIY "���Կ���$n����ͼ��\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "һ�������ӷ���������ݳ�����֮Զ��"
                                 "$N���̸������ֻ���ֱ�룬��Ϯ$n��\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "ʹ��������չ�᡹����һ��ƮȻ�ݳ���"
                                 "ͻȻ����$N�ٶȸ��죬Ҳ�ȵȺ��ڴˣ�\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}


string perform_action_file(string action)
{
      return __DIR__"tiyunzong/" + action;
}

int help(object me)
{
        write(HIC"\n�����ݣ�"NOR"\n");
        write(@HELP

    ������Ϊ�䵱����Ṧ�ķ���

        ѧϰҪ��
          ̫����10��
HELP
        );
        return 1;
}
