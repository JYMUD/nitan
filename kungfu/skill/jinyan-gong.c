// jinyan-gong.c ���㹦

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "ȴ����$n����һת��һ��"HIY"�������伣��"NOR"ͻȻת����$N�����\n",
        "$n����ڵ���һ�㣬���ΰεض���"HIC"������˷���"NOR"�㿪����һ�С�\n",
        "$n����$N��������ʽһ��"HIW"���������ա�"NOR"Ʈ������������һƬ΢���е�����һ�㡣\n",
        "$nʹ��"HIY"�����жݱ䡹"NOR"��������һ�Ρ���һ������֪��ô�ģ��ӹ����ļ�϶�����˳�����\n",
        "$nʹ��"HIM"������ת����"NOR"���㲻��ص�Χ��$N����������Ȧ����$N��һ�б��˿�ȥ��\n",
        "$n����������Ȧ����������һ����Ȧ��������㹦��"HIC"�����������"NOR"�����θ߸ߵذ���������\n",
        "$n������ת������Ʈ�����Ƴ����ߣ����ǽ��㹦��"HIB"���������졹"NOR"����̬�����Ѽ���\n",
        "$n����Ʈ�������䷭��һ��"HIW"���������ޡ�"NOR"����������رܿ���$N�Ĺ��ơ�\n",
});

int valid_enable(string usage) { return usage=="dodge" || usage=="move"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 50)
                return notify_fail("������Ṧ��Ϊ���ޣ������������㹦��\n");

        if( query("max_neili", me)<500 )
                return notify_fail("��������Ϊ̫ǳ�������������㹦��\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˣ����������㹦��\n");

        if( query("neili", me)<60 )
                return notify_fail("�������̫���ˣ����������㹦��\n");

        me->receive_damage("qi", 58);
        addn("neili", -55, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jinyan-gong", 1);
        if (lvl < 30)  return 0;
        if (lvl < 50)  return 10;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 40;
        return 50;
}

string perform_action_file(string action)
{
        return __DIR__"jinyan-gong/" + action;
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n���㹦��"NOR"\n");
        write(@HELP

    ���㹦Ϊȫ���ɱ����Ṧ��

        ѧϰҪ��
          ���칦10��
HELP
        );
        return 1;
}
