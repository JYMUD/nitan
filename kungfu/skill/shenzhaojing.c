// ���վ��� shenzhaojing.c

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) 
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

mapping *action = ({
([      "action" : "$NٿȻԾ��������һȭ����һȭ������Ӱ��ȥ�ƿ켫����$n���ؿڴ�ȥ",
        "dodge"  : 81,
        "force"  : 323,
        "attack" : 119,
        "parry"  : 94,
        "damage" : 68,
        "lvl"    : 0,
        "damage_type": "����"
]),
([      "action" : "$N˿��������ɫ������ƽ�죬�����������վ��񹦵ľ���������һ������$n",
        "dodge"  : 73,
        "force"  : 362,
        "attack" : 138,
        "parry"  : 51,
        "damage" : 73,
        "lvl"    : 200,
        "damage_type": "����"
]),
([      "action" : "$N����΢΢һչ����Ȼ������$n��ǰ����Ȼ��˫����ʩ����$n���Ķ�ȥ",
        "dodge"  : 78,
        "force"  : 389,
        "attack" : 152,
        "parry"  : 53,
        "damage" : 87,
        "lvl"    : 220,
        "damage_type": "����"
]),
([      "action" : "$N�˺�һ����˫�ƻ��գ���ջ���һ��ԲȦ����ʱһ�����ȵ�����ֱӿ$n����",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 163,
        "parry"  : 67,
        "damage" : 93,
        "lvl"    : 250,
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("shenzhaojing", 1);

        if(lvl >= 180)
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";

}

int valid_learn(object me)
{
        if( query("str", me)<32 )
                return notify_fail("�����������������޷��������վ��񹦡�\n");

        if( query("con", me)<32 )
                return notify_fail("����������������޷��������վ��񹦡�\n");

        if( query("gender", me) == "����" && query("shenzhaojing", me)>29 )
                return notify_fail("���޸����ԣ�������������������������վ��񹦡�\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ���վ��񹦡�\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż���㣬����ѧ���վ��񹦡�\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ѧ���վ��񹦡�\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ������������վ��񹦡�\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���������Զ������������վ��񹦡�\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -30;
        int p_e2 = 10;
        int f_e1 = 140;
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenzhaojing", 1);
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


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);

        if (damage_bonus < 160
           || lvl < 180
           || query("neili", me)<300
           || query_temp("weapon", me )
           || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "shenzhaojing"
           || me->query_skill_mapped("unarmed") != "shenzhaojing"
           || me->query_skill_prepared("unarmed") != "shenzhaojing")
                return 0;

        // ���վ��������еļ���������˺���ʹ������
        // ����max_hit �������书���Ǿ��޽��еģ�����
        // �����ֵļ����Լ��˺�ֵ�ּ������˺��������
        // ���书��������
        if (damage_bonus > victim->query_con()/10)
        {
                victim->receive_wound("qi", damage_bonus, me);
                victim->affect_by("shenzhao",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 100 + random(lvl / 10) ]));
                return HIR "$n" HIR "һ���Һ���ȫ��������������"
                       "�����߹ǡ��۹ǡ��ȹ�ͬʱ���ۡ�\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("���վ���ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
        return 400;
}

string perform_action_file(string action)
{
        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}


int help(object me)
{
        write(HIC"\n���վ���"NOR"\n");
        write(@HELP

    �����Ǿ����ˣ��������������ҡ���ĸ˫�����ҲƲ��٣�ȴ��
����ף�ֻ���������䣬�ύ�����ϵ����ѡ�
    ĳ�����˴����Ĵ�������������Ͽ�󣬴���������ƺ�����ϣ�
�ڴ������ð����д򶷵��������Ӵ������������������¹�������
�����������������������Χ��һ�����ߡ�һ��������������ɽ��
��һ����½�������Դ�ƽ����������ʹһ�ڳ������������ǽýݣ�
���������Ὥ�ݳ��������߱�������ī��÷���ϡ����ǵ�ʦ����÷
�����������ȣ��ֵв�ס����ͽ�ܵĶ��У��������ӡ�
    ������ߴ����н�ҩ������÷���Ϻ󣬱��������ˡ�������
������һ���̵ú����ͨ�˷Σ��������β��õ��ˡ���ô������
�죬÷���ϴӻ���ȡ��һ����ֽ�����������䣬����������������
�����ˣ�����ô����ͽ�������������һ�����ף�����û�н�����
������ʲô�ã����ǽ�����Ȼ���棬�������������վ��ˣ��ⲿ��
�վ��������˸��㣬�úõ����գ��˾���Ȼ���ɣ��������ǧ��
�����󴫷��ˡ������վ��������������ġ�

        ѧϰҪ��
                ƾ��Ե�򶡵�ѧϰ
HELP
        );
        return 1;
}
