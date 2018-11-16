#include <ansi.h>

inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N���΢Ц��һ��"HIR"���һ�����"NOR"����$w����$n�����˰˰���ʮ�ĵ��������ݺᣬѸ�ײ��ɵ�",
        "lvl"    : 0,
        "skill_name"  : "�һ�����",
]),
([        "action" : "$N�����ڹ�һ��"GRN"����ľ����"NOR"��$w�ϴ����ޱȾ���������һ���󻡣����϶�������$n��$l",
        "lvl"    : 20,
        "skill_name"  : "��ľ����",
]),
([        "action" : "$N�ֱ�һ����һ��"HIM"���Ź����¡�"NOR"��˫�ֳ�$w����һ��ѩ�����⣬�����������У�����$n��$l",
        "lvl"    : 40,
        "skill_name"  : "�Ź�����",
]),
([        "action" : "$N����$w�������ã����ҿ���ʹ��һ��"RED"���һ����ơ�"NOR"���������󵶷磬��������$n",
        "lvl"    : 60,
        "skill_name"  : "�һ�����",
]),
([        "action" : "$Nһ��"MAG"������ȡ����"NOR"�����Ծ����أ�����$w������ǰ��Ю�����ȵķ�������$n��$l",
        "lvl"    : 80,
        "skill_name"  : "����ȡ��",
]),
([        "action" : "$N�ڿն��𣬰����һ��"HIW"����ʯ��١�"NOR"������$w�ӳ����������ĵ�Ӱ����$n��ȫ���ȥ",
        "lvl"    : 100,
        "skill_name"  : "��ʯ���",
]),
});

int valid_enable(string usage) { return  (usage =="parry")|| (usage =="blade"); }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("���������һ�ѵ�������ȼľ������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("����������㣬û�а취��ȼľ����������Щ���������ɡ�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��û�а취��ȼľ������\n");

        if ((int)me->query_skill("blade", 1) < 100)
                return notify_fail("��Ļ����������̫ǳ��û�а취��ȼľ������\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("ranmu-daofa", 1))
                return notify_fail("��Ļ�������ˮƽ���������޷����������ȼľ������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 30;
        int d_e2 = 10;
        int p_e1 = -20;
        int p_e2 = -40;
        int f_e1 = 100;
        int f_e2 = 250;
        int m_e1 = 190;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("ranmu-daofa", 1);

        if (random(me->query_skill("ranmu-daofa", 1)) > 120 &&
             me->query_skill("force") > 100 &&
             query("neili", me)>1000 &&
             query_temp("weapon", me) &&
             random(10) > 6)
        {
                addn("neili", -100, me);
                return ([
                "action": HIR "$N" HIR "��Ȼ����һ����ţ����弱��"
                          "��ת������ͨ�죬���Ĺ���ɲ�Ǽ�����" +
                          query("name", query_temp("weapon", me) )
                          + HIR "һ�������������\n��һ�����ȵ�������"
                          "Ϯ��$n" HIR "��" NOR,
                "dodge" : -110,
                "attack": 340,
                "force" : 302,
                "damage": 289,
                "parry" : -70,
                "damage_type": "����"]);
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
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("�������������ȼľ������\n");

        if( query("neili", me)<90 )
                return notify_fail("�������������ȼľ������\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;
        if (random(damage) > victim->query_str()/10)
        {
                result = ([ "damage": damage ]);
                result += (["msg" : HIW "$N���еĴ󵶶�ʱ����һ�Ż��棬��������������$n���ڣ�$n" BLINK +
                                    HIR "��Ѫ" NOR + HIW "���������\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"ranmu-daofa/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\nȼľ������"NOR"\n");
        write(@HELP

    ȼľ���������ֶ���������
    Τ���ơ����±޷���ȼľ��������Ϊ��������������
    ����������ͬʱ��ϰ��

        ѧϰҪ��
                �׽150��
                ���޵�150��
                ������Ϊ1500
HELP
        );
        return 1;
}
