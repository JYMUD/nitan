#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ���������¡�������$w�������Һ�ɨ����$n��$l",
        "force" : 126,
        "parry" : 3,
        "dodge" : 5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
([      "action":"$N̤��һ����������ʽ��������$w���������һ���������$n��$l",
        "force" : 149,
        "parry" : 13,
        "dodge" : 10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "����ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һ�С��콵ʽ����бб�����ó�������$n��$l",
        "force" : 167,
        "parry" : 12,
        "dodge" : 15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "�콵ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$w����������Ȧ��һʽ��������졹��һ�������$n��$l",
        "force" : 187,
        "parry" : 23,
        "dodge" : 19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬һʽ�����ʽ������׼$n��$lбб����",
        "force" : 197,
        "parry" : 31,
        "dodge" : 27,
        "damage": 56,
        "lvl"   : 90,
        "skill_name" : "���ʽ",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ��������ʡ���$w��ն�������缲�������$n���ؿ�",
        "force" : 218,
        "parry" : 49,
        "dodge" : 35,
        "damage": 63,
        "lvl"   : 110,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һʽ���ƹ�ʽ����������Ϣ�ػ���$n��$l",
        "force" : 239,
        "parry" : 52,
        "dodge" : 45,
        "damage": 72,
        "lvl"   : 130,
        "skill_name" : "�ƹ�ʽ",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬��â���£�һʽ���������ʽ������׼$n��$lбб����",
        "force" : 257,
        "parry" : 55,
        "dodge" : 51,
        "damage": 88,
        "lvl"   : 150,
        "skill_name" : "�������ʽ",
        "damage_type":  "����"
]),
([      "action":"$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ�������ݺ᡹����$n���ʺ�",
        "force" : 282,
        "parry" : 63,
        "dodge" : 55,
        "damage": 105,
        "lvl"   : 170,
        "skill_name" : "�����ݺ�",
        "damage_type":  "����"
]),
([      "action":"$N���Ƶ�����һʽ�������޼�����$w�Ի���Ծ�����缲�������$n���ؿ�",
        "force" : 335,
        "parry" : 76,
        "dodge" : 55,
        "damage": 122,
        "lvl"   : 190,
        "skill_name" : "�����޼�",
        "damage_type":  "����"
])
});

int valid_enable(string usage)
{ 
       return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;
        int lv = me->query_skill("poyang-jian", 1);

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ѧϰ������⽣��\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("���������Ϊ����������ѧϰ������⽣��\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻹�������ѧϰ������⽣��\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������������⽣��\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������������⽣��\n");

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
        int i, level;
        level = (int) me->query_skill("poyang-jian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<100 )
                return notify_fail("�������������������⽣��\n");

        if( query("neili", me)<130 )
                return notify_fail("�������������������⽣��\n");

        me->receive_damage("qi", 80);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyang-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("poyang-jian", 1);

        if( lvl > 120 &&
            !query("can_perform/poyang-jian/xian", me) ) 
        {
                tell_object(me, WHT "��ͨ����������⽣��" HIY "�������" WHT "���İ��ء�\n" NOR);    
                set("can_perform/poyang-jian/xian", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }
        
        if( lvl > 180 &&
            !query("can_perform/poyang-jian/long", me) ) 
        {
                tell_object(me, WHT "��ͨ����������⽣��" HIC "��������" WHT "���İ��ء�\n" NOR);    
                set("can_perform/poyang-jian/long", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}
