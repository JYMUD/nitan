#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N����Ҵڣ�����$wͻȻ����$n$l������һ�С����·ת��",
        "force"  :  45,
        "dodge"  :  20,
        "parry"  :  20,
        "attack" :  10,
        "damage" :  20,
        "lvl"    :  0,
        "damage_type" :  "����",
        "skill_name"  :  "���·ת",
]),
([      "action" :  "$NԽ��Խ�ͣ�ͻȻ������$w���Ⱪ�ǣ�һ�С�����̺졹��Ȼʹ��\n"
                    "$nֻ����ǰ����ҫ�ۣ����ɵ�����һ��",
        "force"  :  90,
        "dodge"  :  26,
        "parry"  :  40,
        "attack" :  24,
        "damage" :  35,
        "lvl"    :  25,
        "damage_type" :  "����",
        "skill_name"  :  "����̺�",
]),
([     
        "action" :  "$N�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����$wˢ��һ�������ѵ�ˮ������$n$l��ȥ",
        "force"  :  110,
        "dodge"  :  35,
        "parry"  :  40,
        "attack" :  30,
        "damage" :  40,
        "lvl"    :  50,
        "damage_type":  "����",
        "skill_name":   "���ѵ�ˮ",
]),
([      
        "action" :  "$N��Хһ����$w��ֱ��$n$w����һ�������κ���ʽ������$Nȴʹ�ò�\n"
                    "�������������ʹ�������ǧɽĺѩ����һ�з��ӵ��˼���",
        "force"  :  120, 
        "dodge"  :  48,
        "parry"  :  45,
        "attack" :  35,
        "damage" :  48,
        "lvl"    :  75,
        "damage_type" :  "����",
        "skill_name"  :  "ǧɽĺѩ",
]),
([      
        "action" : "$N��$wһ�ӣ���Хһ�����ڿն���ʹ��һʽ�������ϸǡ�����һ��������\n"
                   "����׼��$wֱָ$n$l,",
        "force"  :  160,
        "dodge"  :  82,
        "parry"  :  66,
        "attack" :  55,
        "damage" :  60,
        "lvl"    :  100,
        "damage_type" :  "����",
        "skill_name"  :  "�����ϸ�",
]),
});

string main_skill()
{
        return "wushen-jian";
}

int valid_learn(object me)
{
            object ob; 

        if (me->query_skill("wushen-jian", 1) > 0)
                return notify_fail("���������ϳ��˺�ɽ���񽣣������ٵ���ѧϰ��\n");

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

            if( query("max_neili", me)<300 )
                return notify_fail("�������������û�а취���ϸǽ�����\n");

            if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ��\n");

            if ((int)me->query_skill("sword", 1) < 60)
                   return notify_fail("��Ļ���������򲻹����޷�ѧϰ�ϸǽ�����\n");

            if (me->query_skill("sword", 1) < me->query_skill("zigai-jian", 1))
                return notify_fail("��Ļ�������������ޣ��޷�����������ϸǽ�����\n");

        return 1;
}

int valid_enable(string usage)
{
            return usage == "sword" || usage == "parry";
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
        int i, level;

        level = (int) me->query_skill("zigai-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
       object weapon;

       if( !objectp(weapon=query_temp("weapon", me) )
           || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

       if( query("neili", me)<60 )
                   return notify_fail("����������㣬û�а취��ϰ�ϸǽ�����\n");

       if( query("qi", me)<65 )
                   return notify_fail("��������������ϸǽ�����\n");

       me->receive_damage("qi", 40);
       addn("neili", -50, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zigai-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("zigai-jian", 1);
   

        if( lvl > 120 &&
            !query("can_perform/zigai-jian/hui", me) ) 
        {
                tell_object(me, WHT "��ͨ�����ϸǽ�����" HIC "�ϸǻ���" WHT "���İ��ء�\n" NOR);    
                set("can_perform/zigai-jian/hui", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}
