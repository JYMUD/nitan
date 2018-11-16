#include <ansi.h>
inherit SKILL;
//By dream �򵥰棬���޸�

string *dodge_msg = ({
    "ֻ��$nһ��[1;32m������׽Ӱ��[2;37;0m������Ӱ���������ǵض����$N��һ�С�\n",
    "$n����һ��[1;36m�����о��ݡ�[2;37;0m������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
    "$nʹ��[1;34m�������硹[2;37;0m�����ҵ�����ѹ��$Nȫ���������Ծ������˿ա�\n"
    "����$n��Ӱ�������磬һ��[1;31m���������С�[2;37;0m�����ɶ����$N�Ĺ�����\n",
    "$n������ת��һ��[1;35m�����¥�С�[2;37;0m�ܹ���$N��һ�С�\n",
    "$nʹ��һ��[1;37m�����ŭ����[2;37;0m����ʱ$N��$n����Ӱ���������ˡ�\n"
});

int valid_enable(string usage) 
{ 
        return usage == "dodge"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("������Ṧ��Ϊ���ޣ��������������ȡ�\n");

        if ((int)me->query_skill("bingxin-jue", 1) < 80)
                return notify_fail("����ľ���Ϊ�������������������ȡ�\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("��������Ϊ̫ǳ���������������ȡ�\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

int practice_skill(object me)
{
        if( query("qi", me)<200 )
                return notify_fail("�������̫���ˣ������������ȡ�\n");

        if( query("neili", me)<200 )
                return notify_fail("�������̫���ˣ�������ϰ�����ȡ�\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
string perform_action_file(string action)
{
      return __DIR__"fengshen-tui/" + action;
}
