//kuangfeng-blade ��絶��
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����$w��ӣ�һ��"+HIW"����ƽ�˾���"NOR+"������ƽ��ʵ��Ѹ�ٵ���$n��$l��ȥ",
        "lvl" : 0,
        "skill_name" : "��ƽ�˾�",
]),
([        "action" : "$Nһ��"+HIW"��������ӿ��"NOR+"���ҽ�һ�㣬$w��������������ӿ$n��$l",
        "lvl" : 10,
        "skill_name" : "������ӿ",
]),
([        "action" : "$Nһ��"+HIY"�������ơ�"NOR+"���ֱ�һ�գ�����һ�����϶���ն��$n",
        "lvl" : 20,
        "skill_name" : "������",
]),
([        "action" : "$Nһ��"+HIC"��������ɢ��"NOR+"��������ˣ�$wȴ����ǰ����һ��Բ��������$n��$l",
        "lvl" : 32,
        "skill_name" : "������ɢ",
]),
([        "action" : "$N���������ϣ�һ��"+HIW"��������ড�"NOR+"������$n��ǰ��$w�Ϳ�$n��$l",
        "lvl" : 45,
        "skill_name" : "�������",
]),
([        "action" : "$N���ٻ���$w��ʹ��һ��"+RED"�����в���"NOR+"������һƬ��������$n��$l",
        "lvl" : 58,
        "skill_name" : "���в���",
]),
([        "action" : "$Nһ��"+HIC"���絶˪����"NOR+"��ֻ�����쵶����˸�����ص�Ӱ��$n��ȫ��ӿȥ",
        "lvl" : 71,
        "skill_name" : "�絶˪��",
]),
([        "action" : "$Nʹһ��"+HIW"����۵糸��"NOR+"��$w��������Ӱ��$n��$lӿȥ",
        "lvl" : 86,
        "skill_name" : "��۵糸",
]),
([        "action" : "$Nһ��"+HIB"������Ʈҡ��"NOR+"��$w������˸�������ƻ�����ر�$n��$l",
        "lvl" : 101,
        "skill_name" : "����Ʈҡ",
]),
([        "action" : "$NŲ��С�ˣ�һ��"+HIC"���绨ѩ�¡�"NOR+"������$w���赭д�ػӳ�һ�����漴�֡��ৡ�������������������������$n��$l",
        "lvl" : 120,
        "skill_name" : "�绨ѩ��",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("�������������\n");
        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("����ڹ��ķ����̫ǳ��\n");
        if ((int)me->query_skill("dodge", 1) < 60)
                return notify_fail("����Ṧ���̫ǳ��\n");
        if ((int)me->query_dex() < 25)
                return notify_fail("�������������\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<30 )
                return notify_fail("���������������絶����\n");
        me->receive_damage("qi", 25);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
                return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 60;
        int d_e2 = 35;
        int p_e1 = 5;
        int p_e2 = -10;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 140;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("kuangfeng-blade", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1; }
mixed hit_ob(object me, object victim, int damage)
{
        if (damage < 100) return 0;

        if (random(damage / 2) > victim->query_str())
        {
                victim->receive_wound("qi", (damage - 100) / 2 );
                return HIW "�����������꡹һ�����죬�ѱ�$N�ĵ������ˣ�$n��ʱѪð����!!!\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("kuangfeng-blade", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("kuangfeng-blade", 1); 

        if( lvl >= 150 && 
            !query("can_perform/kuangfeng-blade/kuang", me) )  
        { 
                tell_object(me, HIC "��ͨ���˿�絶����" HIR "����ʮһʽ" HIC "���İ��ء�\n" NOR);     
                set("can_perform/kuangfeng-blade/kuang", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
} 


string perform_action_file(string action)
{
        return __DIR__"kuangfeng-blade/" + action;
}
int help(object me)
{
        write(HIC"\n��絶����"NOR"\n");
        write(@HELP

    �ﲮ��Ŀ쵶��

        ѧϰҪ��
                �����ڹ�60��
                �����Ṧ60��
                ������25����
                ����300
HELP
        );
        return 1;
}
