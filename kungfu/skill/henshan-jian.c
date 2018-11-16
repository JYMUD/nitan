#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N����$w����ָ����ͻȻ���ڿ���һ�����������죬���Ⱪ������$n��ȥ",
        "force"  :  110,
        "dodge"  :  28,
        "damage" :  30,
        "lvl"    :  0,
        "damage_type":  "����"
]),
([      "action" :  "$N����$w������ȣ������Ƶ�$n����$n��æת������ֻ������������",
        "force"  :  120,
        "dodge"  :  24,
        "damage" :  25,
        "lvl"    :  20,
        "damage_type":  "����"
]),
([     
        "action" :  "$N����$w���ⶸ�������е�$w���͵ط��̣�ֱָ$n�ؿڡ���һ�³��п�\n"
                    "��������������ã����ǡ��ٱ�ǧ�ú�ɽ����ʮ��ʽ���еľ���",
        "force"  :  120,
        "dodge"  :  24,
        "damage" :  28,
        "lvl"    :  35,
        "damage_type":  "����",
        "skill_name":   "�ٱ�ǧ��",
]),
([      
        "action" :  "$N���Ų�æ�������ƴ���������$wˢ��һ������������������$n$l��ȥ",
        "force"  :  130, 
        "dodge"  :  30,
        "damage" :  35,
        "lvl"    :  50,
        "damage_type":  "����",
        "skill_name":   "��������",
]),
([      
        "action" : "$N����Ծ��һʽ��������ԡ���$w����һ����Х�Ӱ��������$n��$l",
        "force"  :  160,
        "dodge"  :  38,
        "damage" :  45,
        "lvl"    :  75,
        "damage_type":  "����",
        "skill_name":   "�������",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

            if( query("max_neili", me)<80 )
                return notify_fail("��Ŀǰ��������Ϊ������û�а취����ɽ������\n");

            if (me->query_skill("sword", 1) < 10)
                return notify_fail("��Ļ����������̫ǳ��û�а취����ɽ������\n");

            if (me->query_skill("sword", 1) < me->query_skill("henshan-jian", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������ĺ�ɽ������\n");

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

        level = (int) me->query_skill("henshan-jian", 1);
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

        if( query("neili", me)<40 )
                       return notify_fail("����������㣬û�а취��ϰ��ɽ������\n");

        if( query("qi", me)<50 )
                return notify_fail("���������������ɽ������\n");

        me->receive_damage("qi", 45);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"henshan-jian/" + action;
}
