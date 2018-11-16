// dragon-strike.c ����ʮ����֮�𾪰���
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
int d_e1 = -60;
int d_e2 = -40;
int p_e1 = -20;
int p_e2 = 10;
int f_e1 = 350;
int f_e2 = 550;
int ttl = 17;
int seq = 7;
mapping *action = ({
        ([
                "action"      : "$N���һ����˫��ʹ��"+(order[random(13)])+"���𾪰��"NOR"������һ�а����$n",
                "skill_name" : "�𾪰���",
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]),
});


string main_skill() { return "dragon-strike"; }
int valid_enable(string usage) { return usage=="strike" ; }

int valid_learn(object me)
{
        if (me->query_skill("dragon-strike", 1) > 0)
                return notify_fail("���Ѿ�ѧȫʮ�����ˣ������ٵ���ѧϰ��\n");

        if( query("str", me)<31 )
                return notify_fail("�����������������������������ʮ���ơ�\n");

        if( query("con", me)<24 )
                return notify_fail("����������������������������ʮ���ơ�\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹���������������ʮ���ơ�\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬������������ʮ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("��Ļ����Ʒ���򲻹���������������ʮ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("zhenjing-baili", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<40 )
                return notify_fail("�����������������ʮ���ơ�\n");
        me->receive_damage("qi", 100);
        addn("neili", -40, me);
        return 1;
}
string query_skill_name(int level)
{
                        return action[0]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        return action[0];
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) {
        if (userp(me)) return 0.5; //��Ϊ�ǰ��Ʒ �������
  return 1;
}

int help(object me)
{
        write(HIC"\n����ʮ����֮�𾪰��"NOR"\n");
        write(@HELP

    ����ʮ������ؤ�����֮��������������͵��书��

        ѧϰҪ��
                �õ����߹�����ָ��
                ����1000
                �������25
                �������20
                �����Ʒ�180
HELP
        );
        return 1;
}