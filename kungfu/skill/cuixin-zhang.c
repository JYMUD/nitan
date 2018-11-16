// cuixin-strike.c ������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N����΢�Σ�һ��"CYN"����߱�����"NOR"����Ю��磬����$n���ķ�",
        "lvl"   : 0,
        "skill_name" : "��߱���",
]),
([        "action" : "$N������磬˫��΢΢������һ��"BLU"����Ӱ���ġ�"NOR"����$n���ظ�",
        "lvl"   : 20,
        "skill_name" : "��Ӱ����",
]),
([        "action" : "$N˫�ƺ������֣�һ��"HIW"������ѩ�衹"NOR"�����Ȱ��ɨ��$n�ļ�ͷ",
        "lvl"   : 40,
        "skill_name" : "����ѩ��",
]),
([        "action" : "$N���Ƶ��ػ��������Ƽ�����һ��"GRN"����ӫ��Ӱ��"NOR"���͵�����$n�Ķ�ͷ",
        "lvl"   : 60,
        "skill_name" : "��ӫ��Ӱ",
]),
([        "action" : "$Nʹһ��"HIC"�������꾡��"NOR"��˫���������������ľ��磬ײ��$n",
        "lvl"   : 80,
        "skill_name" : "�����꾡",
]),
([        "action" : "$N���ޱ��飬˫�ۺ�����ҵؼ��ӣ�ʹ��"HIM"��ѩԭ���衹"NOR"��ʮ���������������Ѹ���ޱȵ�Ϯ��$nȫ�������Ѩ",
        "lvl"   : 100,
        "skill_name" : "ѩԭ����",
]),
([        "action" : "$Nʹ��"RED"��������ա�"NOR"����Ȼ������ϣ�����$n��ת��Ȧ��$n���ۻ����Ҽ䣬$N����Ȼͣ��$n������ֻ���һ����Ȧ���������ֳ����Ȧ����$n�ĺ�",
        "lvl"   : 120,
        "skill_name" : "�������",
]),
([        "action" : "$NͻȻ˫��ƽ�٣�$nһ�������ڲ²�䣬���$Nವ�һ�½�˫���ջ���ǰ������һ��"HIG"������������"NOR"��˫����磬ֱ����$n������",
        "lvl"   : 140,
        "skill_name" : "��������",
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo=="jiuyin-baiguzhao" || combo=="dafumo-quan"; }

int valid_learn(object me)
{

        /*
        if ((int)me->query_skill("jiuyin-shengong", 1))
                return notify_fail("���ѽ������澭�ϵ��书ȫ���ڻ��ͨ�������ٷֿ�ѧϰ�ˡ�\n");
        */

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("�������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 100)
            return notify_fail("����ڹ�̫��޷���ϰ�����ơ�\n");

        if( query("max_neili", me)<1200 )
            return notify_fail("���������Ϊ̫ǳ���޷���ϰ�����ơ�\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("��Ļ����Ʒ����ޣ��޷��������Ƶ�Ҫ�衣\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("cuixin-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ĵ����ơ�\n");

        return 1;
}

int practice_skill(object me)
{
        /*
        if ((int)me->query_skill("jiuyin-shengong", 1))
                return notify_fail("���ѽ������澭�ϵ��书ȫ���ڻ��ͨ�������ٷֿ���ϰ�ˡ�\n");
        */

        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<350 )
                return notify_fail("�������������\n");

        me->receive_damage("qi", 80);
        addn("neili", -300, me);
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
        int d_e1 = -45;
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 200;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("cuixin-zhang", 1);
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

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("cuixin-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("cuixin_zhang",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIR "ֻ��$n" HIR "�ƺ���һ�����������ܵ��˴������ƾ��ĸ��ţ�\n" NOR;
        }
}

void skill_improved(object me)   
{  
             int lvl; 
             lvl = me->query_skill("cuixin-zhang", 1);  
               if( lvl >= 80 &&  
                   !query("can_perform/cuixin-zhang/gu", me) )   
               {  
                       tell_object(me, HIC "��ͨ���˴����ơ�" HIR "��עһ��" HIC "���İ��ء�\n" NOR);     
                        set("can_perform/cuixin-zhang/gu", 1, me);  
                       me->improve_skill("martial-cognize", 1500000); 
                       me->improve_skill("martial-cognize", 1500000); 
                       me->improve_skill("martial-cognize", 1500000); 
               }  
             if( lvl >= 150 &&  
                 !query("can_perform/cuixin-zhang/cui", me) )   
             {  
                     tell_object(me, HIC "��ͨ���˴����ơ�" HIR "��������" HIC "���İ��ء�\n" NOR);     
                      set("can_perform/cuixin-zhang/cui", 1, me);  
                     me->improve_skill("martial-cognize", 1500000);    
                     me->improve_skill("martial-cognize", 1500000);    
                     me->improve_skill("martial-cognize", 1500000);    
             }  
     }  
int help(object me)
{
        write(HIC"\n�����ƣ�"NOR"\n");
        write(@HELP

    ������Ϊ����ɴ����Ʒ����ݻٵз����ࡣ
    ������Ӱ�Ȼ�����

        ѧϰҪ��
                ��ڤ����15��
                �����ڹ�20��
                ����300
HELP
        );
        return 1;
}
