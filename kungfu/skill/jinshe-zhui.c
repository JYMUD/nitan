// jinshe-zhui.c ����׶��
//last Modified by Sega by 3/18/2000
//���ǰ����е������,�����ܴ��ױ�����,��������.

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "name":                "ǧ����",
        "action":"$N˫��һ�Σ�һ�С�ǧ���򻯡������е�$w�ó������⣬
��һ�����������$n��$l",
        "dodge":        -20,
        "force":        200,
        "damage":        300,
        "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
        "damage_type":  "����"
]),
([        "name":                "���Ī��",
        "action":"$N����һ����һ�����ð����ֻһɲ�Ǽ䣬����$wѸ�װ�Խ
�����ֵ�$w������һ�С����Ī�⡹�����ȷ���$n��$l",
        "dodge":        -30,
        "force":        300,
        "damage":        400,
        "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return usage=="throwing" ; }
int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<500 )
                return notify_fail("�������������û�а취������׶����\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹���û�а취������׶����\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("jinshe-zhui", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ���׶����\n");

        return 1;
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
int practice_skill(object me)
{
        object weapon;

/*
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "throwing" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
*/
        if( query("qi", me)<30
         || query("neili", me)<500 )
                return notify_fail("�����������������û�а취��ϰ����׶����\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
//        write("�㰴����ѧ����һ�����׶����\n");
        return 1;
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"jinshe-zhui/" + action;
}

int help(object me)
{
        write(HIC"\n����׶����"NOR"\n");
        write(@HELP

    ����׶�����ڡ��������š����˽����ɾ���ѩ�˵Ķ����书��
��ѩ����ʱȫ�Ҳ��ұ��¼����Ͻ������ţ���־���𡣺����置��
ʶ�嶾�̽���֮�úκ�ҩ��������������嶾�̵ġ�������������
�߽�������׶���ر�ͼ��������ɾ����书��
    ��ѩ������Ź֣�Ϊ�����ݣ��书���������˰�����Ѳ⡣��
����������������Ϊ֮ɫ�䣬���ǳ������Ѳ������ѩ�����µ�
���������š�������һ���书�������߽���������׶���ͽ�������
�ơ�

        ѧϰҪ��
                ����500
HELP
        );
        return 1;
}
