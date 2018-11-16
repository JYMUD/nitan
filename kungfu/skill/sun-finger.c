// This program is a part of NT MudLIB
// sun-finger.c

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

mapping *action = ({
([      "action" : "$Nһʽ"GRN"������������"NOR"��������ָ���籡������������ָ���������������$n��$l",
        "lvl" : 0,
        "skill_name" : "��������"
]),
([      "action" : "$N����һת��һ���絽$n���$n��æת��$N���������Ծ�أ�
һʽ"YEL"��³�����ա�"NOR"������ʳָ������ָ��$n��$l",
        "lvl" : 20,
        "skill_name" : "³������"
]),
([      "action" : "$N����̤��һ���������������ʳָЮ���ۻ���������$n��$l��
��ʽ����̹��������һʽ"HIW"��������ѩ��"NOR"",
        "lvl" : 40,
        "skill_name" : "������ѩ"
]),
([      "action" : "$N��ӰƮ��һʽ"MAG"���������졹"NOR"�����϶��£���������繳������$n���Ҽ磬$n������ܣ�$N���ֳ��Ƶ���$n��$l",
        "lvl" : 60,
        "skill_name" : "��������"
]),
([      "action" : "ֻ��$N���Ϻ���һ�죬����һ�գ�һʽ"RED"�����ս�����"NOR"������ʳָбָ����$n��$l��ȥ",
        "lvl" : 70,
        "skill_name" : "���ս���"
]),
([      "action" : "$N����б����ͻȻ�����Ϊָ���͵�һ���죬һʽ"HIM"�����ﳯ����"NOR"��ʹ��һ��ָ��������$n��$l",
        "lvl" : 90,
        "skill_name" : "���ﳯ��"
]),
([      "action" : "$N����һԾ������$n������ϥһ��������ʳָ����һʽ"BLU"����������"NOR"������$n�ĺ���",
        "lvl" : 100,
        "skill_name" : "��������"
]),
([      "action" : "$Nһ�����, һʽ"HIY"��������̩��"NOR"���þ�ȫ����$n��$l��ȥ",
        "lvl" : 130,
        "skill_name" : "������̩"
]),
});
mapping *action_staff = ({
([      "action" : "$N�����Ц����$wƽ�أ���׼ʱ��һ�Ȼӳ����������������Ѹ���ޱȵ�ֱ��$n$l",
        "force" : 100,
        "dodge" : 15,
        "damage" : 50,
        "lvl" : 0,
        "damage_type" : "����",
]),
([      "action" : "$N��������Ⱦ������󴫶�����һ��ָ�񹦻���$w֮�ϣ��������أ�ƽƽ�����ش���$n",
        "force" : 150,
        "dodge" : -10,
        "damage" : 70,
        "lvl" : 20,
        "damage_type" : "����",
]),
([      "action" : "ֻ��$N��Ϣ���񣬽Ų����ţ����ߵ��ƣ�һʽ����������$n$l����ʽ��������",
        "force" : 200,
        "dodge" : 0,
        "damage" : 90,
        "lvl" : 40,
        "damage_type" : "����",
]),
([      "action" : "$N���²���΢�䣬�������ߣ��������أ���Ʈ�ݵ�һ����$n������������ȴҲ��ʧ��������",
        "force" : 250,
        "dodge" : 10,
        "damage" : 120,
        "lvl" : 60,
        "damage_type" : "����",
]),
([      "action" : "$Nƽ��һ�ȣ����е�$w���ƽ������أ�ʹ��ʱ�Ա���ǰ��ɬ����ʵ�Ǿ������أ�����֮��",
        "force" : 300,
        "dodge" : -15,
        "damage" : 140,
        "lvl" : 80,
        "damage_type" : "����",
]),
});
int valid_enable(string usage)
{
        //return usage == "finger" || usage == "parry" || usage == "staff";
        return usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{
/*
        if( query("gender", me) != "����" )
                return notify_fail("һ��ָ���Ǵ�������������ο�����ϰ��\n");

        if( query("str", me)<34 )
                return notify_fail("������������������޷����һ��ָ��\n");

        if( query("dex", me)<30 )
                return notify_fail("����������������޷�����һ��ָ��\n");
*/

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��һ��ָ������֡�\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("����ڹ���򲻹����޷�ѧһ��ָ��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("�������̫�����޷���һ��ָ��\n");

        if ((int)me->query_skill("finger", 1) < 150)
                return notify_fail("��Ļ���ָ����򲻹����޷�ѧһ��ָ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("sun-finger", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷����������һ��ָ��\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<120 )
                return notify_fail("�������������һ��ָ!\n");

        me->receive_damage("qi", 60);
        addn("neili", -100, me);
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
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 390;
        int f_e2 = 490;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sun-finger", 1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me)
{
  if(me->query_skill("kurong-changong") > 10) return 1.0;
  else return 0.6;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy())
                return 0;

        if (damage_bonus < 150)
                return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(3);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 100) / 3, me);

                        if( query("neili", victim) <= (damage_bonus/4+50) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/4, victim);

                                return HIR "ֻ�����͡���һ����$n" HIR "��$N" HIR "���һָ����" NOR +
                                       HIY + name + NOR + HIR "���������ɵ�һ�͡�\n" NOR;
                }
        } else
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(2);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 120) / 3, me);

                        return HIR "ֻ�����͡���һ����$n" HIR "��$N" HIR "�ȶ˷�������������" NOR +
                               HIY + name + NOR +HIR "���������ɵ�һ�͡�\n" NOR;
                }
        }

}

string perform_action_file(string action)
{
        return __DIR__"sun-finger/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yiyang-zhi", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int help(object me)
{
        write(HIC"\nһ��ָ��"NOR"\n");
        write(@HELP

    ԭΪ������϶��������书������һ�ƴ�ʦ������Ю�˼�����
��ɽ�۽�������ϵ۳ƺš���һ�ƴ�ʦ��һ��ָ���������˽�����
���������˼�������ȫ�����С�
    ����ȫ�������ƻ�����

        ѧϰҪ��
                ����
                ������������������80��
                ����700
HELP
        );
        return 1;
}
