// taxue-wuhen.c ̤ѩ�޺�

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$nһʽ"YEL"������ƽɳ��"NOR"���������٣�������ǰ�߳���������Ȼ�����������ɵ�����һ�ԡ�\n",
"$nһʽ"HIW"����������"NOR"�������Ծ�������һ��һת����Ʈ��������֮�⡣\n",
"$nһʽ"HIY"���������ڡ�"NOR"��������������������ĥ��������֮��ת��ж����$N��һ�С�\n",
"$nһʽ"HIB"�����ɵ��ҡ�"NOR"��ֻ��$n���Ӻ�����˫��������һ�ţ����ӽ��Ƶ��������$N���Ѵ�$n���š�\n",
"$nһʽ"HIW"����ѩ��̲��"NOR"���ݸ߷��ͣ���������������Ʈ��������$N������룬ֻ�û������ء�\n",
"$nһʽ"HIW"����˿���꡹"NOR"��ͻȻ����һ�У���Ȼ�����ܾ��˵Ĵ򷨣���$N��æ���Ұ�ȫ����\n",
"$nһʽ"HIM"��������ѩ��"NOR"�����в��ܣ�ֻ΢΢һ����$N���籩�������Ľ����㼴��ա�\n",
"$nһʽ"HIY"������ǱԾ��"NOR"����Ȼ�����ΰ���ֱ��������ֱ��ӥ��������������ƮƮ������������֮�⡣\n",
"$nһʽ"HIW"��̤ѩ�޺ۡ�"NOR"�����μ�����ת�����¾ͻ�������֮�⡣\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("�������̫���ˣ�������̤ѩ�޺ۡ�\n");
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
mixed valid_damage(object me, object victim, int damage, object weapon)
{
        int ap, dp, level;
        object weapon1=query_temp("weapon", me);
        mapping prepare;
        string result, attack_skill;

        if ( victim->query_skill("taxue-wuhen", 1) < 100
        || !living(victim) )
                return;

        dp = COMBAT_D->skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
                dp += COMBAT_D->skill_power(victim, "force", SKILL_USAGE_DEFENSE);

        ap = COMBAT_D->skill_power(me, "dodge", SKILL_USAGE_DEFENSE);
        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        if( objectp(weapon1))attack_skill=query("skill_type", weapon1);
        else switch( sizeof(prepare) )
        {
                case 0: attack_skill = "unarmed"; break;
                case 1: attack_skill = (keys(prepare))[0]; break;
                case 2: attack_skill = (keys(prepare))[query_temp("action_flag", me)]; break;
        }

        ap += COMBAT_D->skill_power(me, attack_skill, SKILL_USAGE_ATTACK);

        ap /= 100;
        dp /= 100;

        if ( random(ap+dp) > ap ) {
                result =  "$n����һ������һ�ߣ�����������״��$N��ͷһ����һʱ�е���æ���ң�\n";
                result += "$n���л��ɳã����̶�$N�������ƣ�\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
         else if ( random(ap+dp) > ap ) {
                result = HIW "ֻ��$n��������,�Լ�����������Ӱ������裬����������״��$N��ͷһ����һʱ�е���æ���ң�\n" NOR;
                result += "$n׽��ʱ�������̶�$N�������ƣ�\n" ;
                COMBAT_D->do_attack(victim,me,query_temp("weapon", victim));
                addn("jingli", random(-20), victim);

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+2*dp) > ap ) {
                result = "$n����һ������һ�ߣ���Ȼ���׵رܿ���$N�Ĺ�����\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+3*dp) > ap ) {
                result = "$n����һ������һ�ߣ�$Nֻ��������������ȫ�ޡ�\n";

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else
                return;
}

string perform_action_file(string action)
{
        return __DIR__"taxue-wuhen/" + action;
}

