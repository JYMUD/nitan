#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N��Ѹ�ݣ�������������Ϯ$n���ź�$w������һ�С���ճ�����",
        "force"  : 70,
        "dodge"  : 20,
        "parry"  : 25,
        "attack" : 10,
        "damage" : 35,
        "lvl"    : 0,
        "damage_type" : "����",
        "skill_name"  : "��ճ���"
]),
([      "action" : "$N�Խ�������ǰ�ſ����һʽ����ɨ��Ҷ�����ὣ����$n$l��",
        "force"  : 110,
        "dodge"  : 40,
        "parry"  : 40,
        "attack" : 20,
        "damage" : 45,
        "lvl"    : 25,
        "damage_type" : "����",
        "skill_name"  : "��ɨ��Ҷ"
]),
([     
        "action" : "$N����$wб������ֱָ��$n$l������һ�С�����������",
        "force"  : 160,
        "dodge"  : 30,
        "parry"  : 45,
        "attack" : 30,
        "damage" : 55,
        "lvl"    : 50,
        "damage_type" : "����",
        "skill_name"  : "��������"
]),
([      
        "action" : "$N����$w����ת����һʽ��������������˳�ƴ���$n$l",
        "force"  : 180, 
        "dodge"  : 45,
        "parry"  : 50,
        "attack" : 35,
        "damage" : 60,
        "lvl"    : 75,
        "damage_type" : "����",
        "skill_name"  : "��������"
]),
([      
        "action" : "$N��Хһ�������ŵ�أ�����Ծ��ͦ������$n$l������һ�С����ף�ڡ�",
        "force"  : 240,
        "dodge"  : 80,
        "parry"  : 60,
        "attack" : 45,
        "damage" : 80,
        "lvl"    : 100,
        "damage_type" : "����",
        "skill_name"  : "���ף��"
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
  
            if( query("max_neili", me)<800 )
                return notify_fail("�������������û�а취��ף�ڽ�����\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("��Ļ�������̫�û�а취��ף�ڽ�����\n");

            if (me->query_skill("sword", 1) < me->query_skill("zhurong-jian", 1))
                return notify_fail("��Ļ�������������ޣ��޷����������ף�ڽ�����\n");

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

        level = (int) me->query_skill("zhurong-jian", 1);
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

               if( query("neili", me)<65 )
                       return notify_fail("����������㣬û�а취��ϰף�ڽ�����\n");

        if( query("qi", me)<65 )
                return notify_fail("�������������ף�ڽ�����\n");

            me->receive_damage("qi", 55);
            addn("neili", -60, me);
            return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhurong-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("zhurong-jian", 1);
   

        if( lvl > 160 &&
            !query("can_perform/zhurong-jian/wan", me) ) 
        {
                tell_object(me, WHT "��ͨ����ף�ڽ�����" HIC "�򽣷���" WHT "���İ��ء�\n" NOR);    
                set("can_perform/zhurong-jian/wan", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}

