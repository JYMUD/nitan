// kongming.c ����ȭ

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$Nʹһ��"HIW"������ס�ˡ�"NOR"��˫����ƮƮ�ع���$n$l",
        "lvl":0,
        "skill_name": "����ס��"
]),
([        "action": "$N����һƽ,����һ��,һ��"HIW"������ʢ����"NOR"ֱ��$n��$l",
        "lvl":10,
        "skill_name": "����ʢ��"
]),
([        "action": "$N������$nһת��˫������,һ��"HIW"���ղ�װˮ��"NOR"����$n$l",
        "lvl":20,
        "skill_name": "�ղ�װˮ"
]),
([        "action": "$N����һ��,����һ��,һ��"HIW"���黳���ȡ�"NOR"����$n��$l",
        "lvl":30,
        "skill_name": "�黳����"
]),
([        "action": "$Nʹһ��"HIW"����ɽ���"NOR"��$n��$l��Χ��$N��������Ӱ֮��",
        "lvl":40,
        "skill_name": "��ɽ����"
]),
([        "action": "$N��ɫһ����ʹ��"HIW"�����Ŀ�����"NOR"��Χ��$n��$l��������",
        "lvl":50,
        "skill_name": "���Ŀ���"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ȭ������֡�\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������̫�����޷�������ȭ��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�������ȭ��\n");

        if ((int)me->query_skill("unarmed", 1) < 120)
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�������ȭ��\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("kongming-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������Ŀ���ȭ��\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<70 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -5;
        int d_e2 = -20;
        int p_e1 = -50;
        int p_e2 = -60;
        int f_e1 = 400;
        int f_e2 = 500;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("kongming-quan", 1);
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

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int)me->query_skill("kongming-quan", 1) < 100
           || ! living(me)
            || query_temp("weapon", me )
            || query_temp("weapon", ob) )
                return;

        ap = ob->query_skill("force") + ob->query_skill("count", 1);
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("kongming-quan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "˫��һ��$N" + HIG
                                            "��ʱ�����Լ�������ȫȻ��ա�\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIG "$n" HIG "����񵲣���$N" HIG
                                            "ֻ�����Լ�ȫȻ��׽����$n" HIG "��"
                                            "������\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "������ȭ���Ҹ���"
                                            "$N" HIG "ֻ���������޴���ʹ��˵��"
                                            "�������ܡ�\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("kongming-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("kongming-quan", 1)) < 100 ||
            !living(me) || !query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("kongming-quan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "�������ȭ�ġ��ա��־���$N" HIC "�Ĺ�����Ȼ��ա�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "�������ȭ�ġ��ᡱ�־����������߰����$N��\n"
                                    HIC "$N" HIC "�����޼ƿ�ʩ��ֻ���ջع��ơ�\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

string perform_action_file(string action)
{
        return __DIR__"kongming-quan/" + action;
}

int help(object me)
{
        write(HIC"\n����ȭ��"NOR"\n");
        write(@HELP

    ����ȭ������ͯ�ܲ�ͨ���һ�����������������书��
    ���ӡ����¾������о仰������������Ϊ���������ޣ�����֮
�á��仧���Ϊ�ң������ޣ�����֮�á�������˵����ֻ��Ϊ�м�
�ǿյģ�����ʢ���Ĺ��ã���������ʵ�ĵ�һ�����������װ��ô
�������췿�ݣ������Ŵ���ֻ��Ϊ�����ı��м�Ŀ�϶�����Ӳ���
ס�ˡ�����������ʵ�ĵģ������Ŵ������пգ�שͷľ�����ķ���
��������ôһ��ѣ��Ǿ�һ���ô�Ҳû���ˡ�ȫ�������ϳ˵��书��
Ҫּ���ڡ��ա��ᡱ���֣��Ǿ�����ν�������ȱ�����ò��ס���
ӯ���壬���ò��������ȭ��������������书������ǿ�мܡ�

        ѧϰҪ��
                ����100
HELP
        );
        return 1;
}
