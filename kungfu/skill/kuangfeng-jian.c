// kuangfeng-jian ���콣

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����Ծ������$w��ӣ�ն��$n��",
        "lvl"    : 0,
        "skill_name" : "��ƽ�˾�"
]),
([        "action" : "$N����$w�����������Σ���$n���ұ����ն��",
        "lvl"    : 20,
        "skill_name" : "������ӿ"
]),
([        "action" : "$N����һ����ˢˢˢˢ�Ľ�����$n�أ������������Ĵ�����",
        "lvl"    : 40,
        "skill_name" : "������"
]),
([        "action" : "$N����һ����Х��б����ǰ��$w����ֱ����Ѹ���ޱȣ�����$n��$l",
        "lvl"    : 60,
        "skill_name" : "������ɢ"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("���������Ϊ�������޷���ϰ���콣��\n");

        if ((int)me->query_skill("dodge", 1) < 90)
                return notify_fail("��Ļ����Ṧ���̫ǳ���޷���ϰ���콣��\n");

        if ((int)me->query_dex() < 28)
                return notify_fail("��������������޷���ϰ���콣��\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("kuangfeng-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ŀ��콣��\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("��������������������콣��\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
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
        int d_e1 = 15;
        int d_e2 = 35;
        int p_e1 = -15;
        int p_e2 = 5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 80;
        int m_e2 = 180;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("kuangfeng-jian", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int i;

        lvl = me->query_skill("sword-cognize", 1);
        i = random(lvl);

        if( /*query("family/family_name", me) == "��ɽ����" && */
            i > 40 && random(2) == 0)
        {
                if (i < 100)
                {
                        victim->receive_wound("qi", damage_bonus / 3);
                        return HIC "ֻ��$N" HIC "����һ̽����â���ǣ�����$n��\n" NOR;
                }
                if (i < 200)
                {
                        victim->receive_wound("qi", damage_bonus / 2);
                        return HIY "ֻ��$N" HIY "һ����Х��������ɣ�$n" HIY "�������У�\n" NOR;
                } else
                {
                        victim->receive_wound("qi", damage_bonus);
                        return HIW "����$N" HIW "΢΢һЦ�������ƶ�������$n" HIW "��Ȼ���У�\n" NOR;
                }
        }
}
string perform_action_file(string action)
{
        return __DIR__"kuangfeng-jian/" + action;
}
int help(object me)
{
        write(HIC"\n���콣��"NOR"\n");
        write(@HELP

    ���콣Ϊ��ɽ���ڵĽ�����
    ���ס����콣�����Ƿⲻƽ������ɽ����ʮ��������Ƴ���
�ĵ��⽣��������һ������һ�������ػ���־������Ҫִ�ƻ�ɽһ
�ɣ�������˻�ɽ��������֮�󣬸�����Ϊ����������������ƾ��
�ı�������һ�����ʽ�����콣����

        ѧϰҪ��
                ��ɽ�ڹ�60��
                �����Ṧ60��
                ������25����
                ����300
HELP
        );
        return 1;
}
