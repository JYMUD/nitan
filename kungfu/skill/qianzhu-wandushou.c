// qianzhu-wandushou.c ǧ������
// Last Modified by winder on May. 17 2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����һ�ζ�����һ��"HIB"��С���꡹"NOR"��˫�ƴ���һ���ȷ�����$n��ǰ��",
        "lvl"    : 0,
        "skill_name" : "С����"
]),
([        "action" : "$N���λ���һ����������$n��ת��һ��"MAG"�������ֻ֡�"NOR"��˫�ƻó�������Ӱ����$n",
        "lvl"    : 20,
        "skill_name" : "�����ֻ�"
]),
([        "action" : "$N���һ����һ��"BLU"��������š�"NOR"��������޸���ɽ����һ���ȷ�������$n������",
        "lvl"    : 30,
        "skill_name" : "�������"
]),
([        "action" : "$Nһ����Ц��һ��"HIR"�����߾�ת��"NOR"������һ��������һ�������ĳ����ֱ������޹ǣ��Ƶ���;������ű䣬����Ȱ�ӡ��$n��$l",
        "lvl"    : 40,
        "skill_name" : "���߾�ת"
]),
([        "action" : "$N������ǰ��һ��"BLU"���ظ����硹"NOR"��˫�������ĳ���һ���Ƴ��ǵĺ���������͸������$n��Χ�Ŀ�����������",
        "lvl"    : 50,
        "skill_name" : "�ظ�����"
]),
([        "action" : "$N����һ�������κ����������򣬷���ײ��$n��һ��"YEL "���Ʒ��´̡�"NOR"�����罣��ֱ��$n������",
        "lvl"    : 60,
        "skill_name" : "�Ʒ��´�"
]),
([        "action" : "$Nһ���������������𣬰����һʽ"HIB"��������β��"NOR"�����ֻ���$n��$l",
        "lvl"    : 70,
        "skill_name" : "������β"
]),
([        "action" : "$N���һ���������嶾�񹦣�һ��"RED"���������"NOR"��ɲ�Ǽ�ȫ��ë�����̣�һ�Ա��̵�˫צ�����ĳ�$n��$lץȥ",
        "lvl"    : 80,
        "skill_name" : "�������"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="wudu-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ǧ�����ֱ�����֡�\n");

        if( query("max_neili", me)<100 )
                return notify_fail("�������̫�����޷���ǧ������");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<60 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<60 )
                return notify_fail("�������������ǧ�����֡�\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int lvl2;
        int flvl;

        lvl  = me->query_skill("qianzhu-wandushou", 1);
        lvl2 = me->query_skill("duji", 1);
        flvl=query("jiali", me);
        if (lvl + random(flvl) > victim->query_skill("dodge")
                         &&victim->affect_by("qzhu_poison",
                                  ([ "level" : lvl2 + lvl*3 + random(flvl),
                                     "id":query("id", me),
                                    "duration" : lvl / 50 + flvl/50 + random(lvl2 / 50) ])))
        {
                return HIW "$n" HIW "ͻȻ���Ť��,ʹ�಻��,����������ǧ���򶾹��ľ޶���\n" NOR;
        }
}
void skill_improved(object me)
{
        if( random(15)<1 && query("per", me)>5 )
        {
                tell_object(me, HIR"���Ȼ�������ڶ�����ܣ����϶�ʱ����һ�������\n" NOR );
                addn("per", -1, me);
        }
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
        int d_e1 = -55;
        int d_e2 = -20;
        int p_e1 = 10;
        int p_e2 = 35;
        int f_e1 = 190;
        int f_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qianzhu-wandushou", 1);
        if (random(me->query_skill("finger")) > 120 &&
            me->query_skill("force") > 100 &&
            me->query_skill("dodge") > 100 &&
            query("neili", me)>1500){
                addn("neili", -200, me);
                return ([
                "action": HIR "$Nü��������֣����ؽ�ҧ��ͻȻ���һ��������ʮָ�ֿ�����Ȱ����$n����Ѩ��"NOR,
                "force": 560,
                "damage" : 100,
                "damage_type": "����"]);
        }
           if (random(me->query_skill("finger")) > 80 &&
            me->query_skill("force") > 100 &&
            query("neili", me)>1000){
                addn("qi", -15, me);
                addn("neili", -100, me);
                return ([
                "action": HIR "$N��Ȼҧ��ʳָ��Ǳ�����������ر���ָ�⣬���ᵯ����һ���ھ�ֱϮ$n�ؿڣ�"NOR,
                "force": 420,
                 "damage" : 80,
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
                "damage_type" : random(2) ? "����" : "����",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qianzhu-wandushou", 1) >= 50 )
                return __DIR__"qianzhu-wandushou/" + action;
}

int help(object me)
{
        write(HIC"\nǧ�����֣�"NOR"\n");
        write(@HELP

    ǧ���������嶾�̵Ķ��Ź����ж�����������������ȡ��
�����ϵĶ��������ɶ�������Ȼ�����������������Լ�����ò��
ʹ�Լ���ĳ�ª�ޱȡ�

        ѧϰҪ��
                �嶾��20��
                ����100
HELP
        );
        return 1;
}
