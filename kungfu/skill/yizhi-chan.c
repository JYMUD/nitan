// This program is a part of NT MudLIB
// yizhi-chan.c һָ��

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N˫ָ��£��һʽ"HIY"�����������"NOR"��������ϣ�������һǰһ�����$n���ظ���",
        "lvl" : 0,
        "skill_name" : "�������"
]),
([        "action" : "$N���ƻ��أ�һʽ"HIY"��������ա�"NOR"��������ָǰ���˸��뻡���͵�һ˦������$n��$l",
        "lvl" : 20,
        "skill_name" : "�������"
]),
([        "action" : "$N����������һʽ"HIY"�����Ź�ɡ�"NOR"��˫��ʳָ�˲������һ������������$n��ȫ��ҪѨ",
        "lvl" : 40,
        "skill_name" : "���Ź��"
]),
([        "action" : "$N��ϥ������һʽ"HIY"�����ޱߡ�"NOR"��������ȭ���⣬����Ĵֱָ����ңң����$nһ��",
        "lvl" : 60,
        "skill_name" : "���ޱ�"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) { return combo=="banruo-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��һָ��������֡�\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���򲻹����޷�ѧһָ����\n");

        if( query("max_neili", me)<300 )
                return notify_fail("�������̫�����޷���һָ����\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("yizhi-chan", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷����������һָ����\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<50 )
                return notify_fail("�������������һָ����\n");
        me->receive_damage("qi", 40);
        addn("neili", -25, me);
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
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -15;
        int f_e1 = 360;
        int f_e2 = 460;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yizhi-chan", 1);
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

void skill_improved(object me)
{
        int level = (int)me->query_skill("yizhi-chan", 1);

        if( level == 180 && !query("sl_gift/con", me) )
        {
                addn("con", 1, me);
                set("sl_gift/con", 1, me);
                tell_object(me, "���һָ���Ͱ�����ѧ�����ɣ��������ĸ��ǡ�\n");
        }
        /*
        if( query("family/family_name", me) == "������" )
        {
                if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) )
                {
                        me->improve_skill("hunyuan-yiqi", (level - 5), 1);
                        tell_object(me, "����һָ�������������������Ļ�Ԫһ������Ϊ��\n");
                }
        }
        */
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;

        if( damage_bonus < 50 ) return 0;

        if( random(damage_bonus/2) > victim->query_str()/10 )
        {
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "���������ݡ�һ�����죬һ�ɾ���ֱ͸$n��ǰ�أ�\n" NOR ]);
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yizhi-chan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"yizhi-chan/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\nһָ����"NOR"\n");
        write(@HELP

    һָ��Ϊ������ʮ������֮һ��
    ��������ƻ�����

        ѧϰҪ��
                ��Ԫһ����20��
                ����100
HELP
        );
        return 1;
}
