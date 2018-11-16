// bingcan-duzhang.c  ���϶���

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N����¶�������Ц�ݣ�˫��Я����˪����ɨ$n",
        "dodge" : -30,
        "attack": 79,
        "parry" : -37,
        "dmage" : 52,
        "force" : 430,
        "damage_type": "����"
]),
([      "action": "$NͻȻ������ת��������$n��˫�Ʒ���������$n��$l",
        "dodge" : -22,
        "attack": 96,
        "parry" : -34,
        "dmage" : 67,
        "force" : 490,
        "damage_type": "����"
]),
([      "action": "$N�����Ϻ����������֣������ޱȵ�����$n��$l",
        "dodge" : -20,
        "attack": 113,
        "parry" : 10,
        "dmage" : 82,
        "force" : 530,
        "damage_type": "����"
]),
([      "action": "$N�����һЦ��˫�ƴ��������ĺ�������$n��$l",
        "dodge" : 28,
        "attack": 139,
        "parry" : 36,
        "dmage" : 95,
        "force" : 580,
        "damage_type": "����"
]),
([      "action": "$N����һ����Х���ۼ�ȫ�����������$n",
        "dodge" : 27,
        "attack": 161,
        "parry" : 21,
        "dmage" : 105,
        "force" : 640,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if( !query("family", me) || 
            query("family/family_name", me) != "������" )
                return notify_fail("�㲻�����������ˣ��޷�ѧϰ���񹦡�\n");

        if ((int)me->query_skill("freezing-force", 1) < 0)
                return notify_fail("�����޵��ڹ��޷������϶��ơ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹����޷������϶��ơ�\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("�������̫�����޷������϶��ơ�");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bingcan-duzhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ı��϶��ơ�\n");

        if ((int)me->query_skill("freezing-force", 1) < (int)me->query_skill("bingcan-duzhang", 1))
                return notify_fail("��ı��Ϻ���ˮƽ���ޣ��޷���������ı��϶��ơ�\n");

        return 1;
}

/*
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
*/
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -20;
        int d_e2 = -40;
        int p_e1 = -35;
        int p_e2 = -55;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("bingcan-duzhang", 1);
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

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }


int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<30 )
                return notify_fail("����������������϶��ơ�\n");

        if (me->query_skill("bingcan-duzhang", 1) < 50)
                me->receive_damage("qi", 100);
        else
                me->receive_damage("qi", 150);

        addn("neili", -180, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("bingcan-duzhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("bingcan_duzhang",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "ֻ��һ�󼫺����ĵ����𣬿���������$N" HIW "���ϵı��Ϻ�����\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bingcan-duzhang/" + action;
}
