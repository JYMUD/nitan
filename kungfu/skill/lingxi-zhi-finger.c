// This is player's own skill (Write by Lonely@nt2)
//CreatebyС��(Sata)atTue May 10 13:11:08 2011
// ��Ϭһָָ(lingxi-zhi-finger.c)

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N˫��΢������ȭ���գ�һʽ�����է�֡���˫��ʳָ�͵ĵ���$n��",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 100,
	"damage_type" : "����",
	"skill_name" : "���է��"
 ]),
// ZHAOSHI : 1
([      "action" : "$N���۽��죬�Ƚż��أ�һʽ��һָ���졹��˫�ֽ�ָ���ն�׼$n��$l�þ�ȫ������������ȥ��",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 110,
	"damage_type" : "����",
	"skill_name" : "һָ����"
 ]),
// ZHAOSHI : 2
([      "action" : "$N���۽��죬�Ƚż��أ�һʽ��һָ��������������ֱָ��ָ��$n��$l",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 120,
	"damage_type" : "����",
	"skill_name" : "һָ����"
 ]),
// ZHAOSHI : 3
([      "action" : "$N���۽��죬һʽ������ɽ�������ִ�Ĵֱָָ$n��$l��ȥ",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 130,
	"damage_type" : "����",
	"skill_name" : "����ɽ"
 ]),
// ZHAOSHI : 4
([      "action" : "$N˫��ʮָ���룬һʽ��ǧ���ơ����������������ס$n��",
	"attack" : 260,
	"damage" : 260,
	"force" : 260,
	"dodge" : 260,
	"parry" : 260,
	"lvl" : 140,
	"damage_type" : "����",
	"skill_name" : "ǧ����"
 ]),
// ZHAOSHI : 5
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��"+"��Ϭһָָ"+"������֡�\n");
        if( query("max_neili", me)<50 )
                return notify_fail("�������̫�����޷���"+"��Ϭһָָ"+"��\n");
        return 1;
}

int valid_enable(string usage) { 
        return usage == "finger" || 
               usage == "parry"; 
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
        level = (int)me->query_skill("lingxi-zhi-finger",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("lingxi-zhi-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        if( query("qi", me)<25 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        if( query("neili", me)<3 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        me->receive_damage("qi", 25);
        addn("neili", -3, me);
        return 1;
} 

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (random(damage) > victim->query_str()) 
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "�����������꡹һ�����죬�ѱ�$N����ɱ�����ˣ�$n��ʱѪð���ɣ�����\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__ + "lingxi-zhi-finger" + "/" + action; 
}