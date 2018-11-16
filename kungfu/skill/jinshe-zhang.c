// jinshe-zhang.c ����������
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "ǧ�߳���",
        "action" : "$N˫��һ��һ��"HIY"��ǧ�߳�����"NOR"�ó�������Ӱ£��$n��$l",
        "lvl"    : 0
]),
([        "skill_name" :  "ħ�����",
        "action" : "$N����һ����˫�������Ƴ���һ��"HIY"���������ߡ�"NOR"ǿ�����Ʒ�ֱ��$n��$l",
        "lvl"    : 10
]),
([        "skill_name" : "˫������",
        "action" : "$N˫�Ʒ׷ɣ�һ��"HIY"��˫�����项"NOR"ֱȡ$n��$l",
        "lvl"    : 20
]),
([        "skill_name" : "����ʽ",
        "action" : "$N�����������ߣ�һ��"HIY"������ʽ��"NOR"��ɭɭ�Ʒ��޿ײ����ػ���$n��$l",
        "lvl"    : 30
]),
([        "skill_name" : "����ʽ",
        "action" : "$N�������˫��ƽ�ƣ����������һ��"HIY"������ʽ��"NOR"����$n��$l",
        "lvl"    : 40
]),
([        "skill_name" : "��������",
        "action" : "$N����������ǰ�������Ƴ���һ��"HIY"���������ơ�"NOR"����$n$l",
        "lvl"    : 50
]),
([        "skill_name" : "���߷���ҧ",
        "action" : "$Nʹ��"HIY"�����߷���ҧ��"NOR"��������շ��𣬴ӿ��е�ͷ��$n��$l���ƹ���",
        "lvl"    : 60
]),
([        "skill_name" : "������Ӱ",
        "action" : "$Nʹ��һ��"HIY"��������Ӱ��"NOR"�����ƻ���Ϊʵ����$n��$l",
        "lvl"    : 70
]),
([        "skill_name" : "���߲�˿��",
        "action" : "$N���ƻ��˸�ȦȦ�������Ƴ���һ��"HIY"�����߲�˿�֡�"NOR"����$n$l",
        "lvl"    : 80
]),
([        "skill_name" : "�����ΰ˷�",
        "action" : "$Nʹ��"HIY"�������ΰ˷���"NOR"������ɢ���˴�ͬʱ��$n��$l���ƹ���",
        "lvl"    : 90
]),
([        "skill_name" : "����̽ͷ",
        "action" : "$Nʹ�����������Ʒ�"HIY"������̽ͷ��"NOR"������Ȱ�����$n��ǰ��һ������$n��$l",
        "lvl"    : 100
]),
([        "skill_name" : "��������",
        "action" : "$N�������ᣬȫ�����һ��"HIY"���������졹"NOR"��˫��������£�$n��ȫ��������������֮��",
        "lvl"    : 110
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("����������㣬�޷������������ơ�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹����޷������������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("jinshe-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ��������ơ�\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<30 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        if( query("neili", me)<15 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
string *parry_msg = ({
        "$nʹ����ճ���־���˫��һ������ƫ��$N��$w��\n",
});

string *unarmed_parry_msg = ({
        "$nʩչ�����������ƣ����赭д�Ļ�����$N�Ĺ��ơ�\n",
});

string query_parry_msg(object weapon)
{
        if (weapon)
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -10;
        int d_e2 = 10;
        int p_e1 = 30;
        int p_e2 = 60;
        int f_e1 = 100;
        int f_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinshe-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"jinshe-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n���������ƣ�"NOR"\n");
        write(@HELP

    �������������ڡ��������š����˽����ɾ���ѩ�˵Ķ����书��
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
