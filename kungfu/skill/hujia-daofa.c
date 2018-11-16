// hujia-daofa.c ���ҵ���

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����$w���ƣ�һ��"HIM"���Ʋ�������"NOR"������������$nl��ȥ",
        "lvl"    : 0,
        "skill_name" : "�Ʋ�����",
]),
([        "action" : "$Nһ��"HIC"��ɳŸ�Ӳ���"NOR"���������¶��ϻ��˸��뻡��$wһ��һ�գ�ƽ��
����$n�ľ���",
        "lvl"    : 8,
        "skill_name" : "ɳŸ�Ӳ�",
]),
([        "action" : "$Nʹ��һ��"HIB"������������"NOR"����$w��������һ��ѹ��$n ",
        "lvl"    : 16,
        "skill_name" : "��������",
]),
([        "action" : "$Nһ��"HIG"���������ȡ�"NOR"��$w������б����$n��ȥ ",
        "lvl"    : 24,
        "skill_name" : "��������",
]),
([        "action" : "$N����$w��ת��Ծ��һ��"RED"����´��ʡ�"NOR"��һ���׹�����$n���ؿ�",
        "lvl"    : 32,
        "skill_name" : "��´���",
]),
([        "action" : "$N����$w��ʹ��һ��"HIW"���׺���᡹"NOR"���������ã����ҿ�����������$n",
        "lvl"    : 40,
        "skill_name" : "�׺����",
]),
([        "action" : "$Nһ��"GRN"��������ů��"NOR"�����Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
        "lvl"    : 48,
        "skill_name" : "������ů",
]),
([        "action" : "$Nļ��ʹһ��"HIM"���˷��ص���"NOR"����ʱ�����������䵶��������˷�ӿ��
$nȫ��",
        "lvl"    : 56,
        "skill_name" : "�˷��ص�",
]),
});

string main_skill() { return "daojian-guizhen"; }
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("con", me)<30 )
                return notify_fail("���о��˰��죬ֻ���ø�����Щ�ʼ���޷�������е����С�\n");

        if( query("str", me)<30 )
                return notify_fail("���о��˰��죬�о�������Щ�ͣ�ʼ���޷�����ʩչ��\n");

        /*
        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("���Ѿ�����ҽ����ͺ��ҵ������ߺ�һ�ˡ�\n");
        */
        if( query("max_neili", me)<1400 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 120)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ���ҵ�����\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("hujia-daofa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ĺ��ҵ�����\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        /*
        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("���Ѿ�����ҽ����ͺ��ҵ������ߺ�һ�ˡ�\n");
        */

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<60 )
                return notify_fail("������������������˺��ҵ�����\n");

        if( query("neili", me)<100 )
                return notify_fail("������������������˺��ҵ�����\n");

        me->receive_damage("qi", 50);
        addn("neili", -80, me);
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
        int d_e1 = 50;
        int d_e2 = 30;
        int p_e1 = 0;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 180;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("hujia-daofa",1);
        if (random(me->query_skill("blade")) > 80
        &&  me->query_skill("force") > 100
         && query("neili", me)>500
         && objectp(weapon=query_temp("weapon", me) )
         && query("id", weapon) == "lengyuedao" )
        {
                addn("neili", -100, me);
                return ([
                        "action": "$Nʹ��һ��" HIM "����ѩ�׷ס�" NOR "��$w�����򳤰�â���������䣬ֱ����$n",
                        "damage": 400,
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                        "damage_type": "����"
                ]);
        }
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
                "damage_type" : "����",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("hujia-daofa", 1)) < 100 ||
            ! objectp(query_temp("weapon", me)))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("hujia-daofa", 1);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIC "$n" HIC "ͻȻʹ��һ�С���ѩ�׷ס��������򳤰�â���������䣬ֱ����$N"
                            "������Ϊ���ƣ���$N����������\n" NOR]);
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (damage > victim->query_str())
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "�����������꡹һ�����죬�ѱ�$N�ĵ������ˣ�$n��ʱѪð���ɣ�����\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"hujia-daofa/" + action;
}

int help(object me)
{
        write(HIC"\n���ҵ�����"NOR"\n");
        write(@HELP

    ���ҵ���Ϊ����ʼ����������������쳾ݼҴ��������ɺ���
��������˷����ҽ��������¡�

        ѧϰҪ��
                �����ڹ�20��
                ����50
HELP
        );
        return 1;
}
