// meiren-sanzhao.c ��������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }


mapping *action = ({
([      "action" : "$N����΢����������Ť�����㷴�ߣ���$n��С����ȥ��$n������ܣ�\n$N˳�Ʒ�������������§ס$nͷ���������ս���׼$n���ģ�һ����ȥ",
        "lvl" : 0,
        "skill_name" : "��������",
]),
([      "action" : "$N�����Ե���$n�������̤ס$N�ĺ�����$N���Դ��������Լ����ؿ����䣬\n˳���ڵ���һ�������$n�Ŀ�������������ս�����$n�ĺ���",
        "lvl" : 10,
        "skill_name" : "С�����",
]),
([      "action" : "$N������ǰ���ߣ�˳��һ�������ϵĽ�����$n���ʺ��ȥ",
        "lvl" : 20,
        "skill_name" : "�������",
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if( query("gender", me) != "Ů��" )
                return notify_fail("�㲻��Ů�ӣ�����ô��ѧ�����������أ�\n");
        if (me->query_int() < 25)
                return notify_fail("������Բ������޷�ѧ�������С�\n");
        if( query("max_neili", me)<100 )
                return notify_fail("�������̫�����޷�ѧ�������С�\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        int level;

        if( query("jingli", me)<30 || query("jing", me)<30 )
                return notify_fail("��ľ���̫�ã��޷�������ϰ��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������������С�\n");


        level = (int)me->query_skill("meiren-sanzhao", 1);
        if( level < 30 )
                return notify_fail("����������е����ջ�������\n");

        if( level > (int)me->query_skill("strike", 1))
                return notify_fail("�������������Ҳ������ȥ�ˡ�\n");

        addn("jingli", -30, me);
        me->receive_damage("jing", 30);
        addn("neili", -30, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -15;
        int d_e2 = 5;
        int p_e1 = -45;
        int p_e2 = 25;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 180;
        int m_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("meiren-sanzhao",1);
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

mixed hit_ob(object me, object victim, int damage_bonus)
{
             int lvl;
             lvl = me->query_skill("meiren-sanzhao", 1);
        if( damage_bonus < 100
               || me->is_busy()
               || ! living(victim)
               || lvl < 150
                || query("neili", me)<500
               || me->query_skill_mapped("strike") != "meiren-sanzhao" )
                          return 0;

        if((damage_bonus/2) > victim->query_str()/10&&
               !query_temp("boduo", victim)){
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                addn_temp("boduo", 1, victim);
                 return HIW "ֻ����һ������������"BLINK"��һ�а��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 1){
                victim->receive_wound("qi", (damage_bonus - 90) / 2, me);
                addn_temp("boduo", 1, victim);
                return HIG"ֻ����һ������������"BLINK"�ڶ��а��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 2){
                victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                addn_temp("boduo", 1, victim);
                return HIB "ֻ����һ������������"BLINK"�����а��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 3){
                victim->receive_wound("qi",(damage_bonus - 70) / 2, me);
                addn_temp("boduo", 1, victim);
                return HIY"ֻ����һ������������"BLINK"���ĸа��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 4){
                victim->receive_wound("qi", (damage_bonus - 60) / 2, me);
                addn_temp("boduo", 1, victim);
                return HIC"ֻ����һ������������"BLINK"����а��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 5){
                victim->receive_wound("qi", (damage_bonus - 50) / 2, me);
                addn_temp("boduo", 1, victim);
                return HIR "ֻ����һ������������"BLINK"�����а��ᣡ\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()/10&&
                query_temp("boduo", victim) == 6){
                delete_temp("boduo", victim);
                return WHT"ֻ����һ������������"BLINK"�ٴΰ��Ὺʼ��\n" NOR;
        }

}

string perform_action_file(string action)
{
        return __DIR__"meiren-sanzhao/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n��������"NOR"\n");
        write(@HELP

    ����������������������ȡ��������������

        ѧϰҪ��
                ������60��
                ������Ϊ100
                ��������35
HELP
        );
        return 1;
}

