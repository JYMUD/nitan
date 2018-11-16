// duanyun-bian.c ���Ʊ޷�

#include <ansi.h>

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action":"$Nһ��"HIR" �ۻ� "NOR",�����������$w��$n����Χס������һ�£���Ȧ������С��",
        "force":query("max_neili", this_player())/4,
        "dodge":        -10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "�ۻ�",
        "damage_type":  "����"
]),
([      "action":"$N������ã�����$wһ��"HIC" ��� "NOR",����$w����һ������Ѹ�ٻ���$n��",
        "force":query("max_neili", this_player())/4,
        "dodge":        5,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "���",
        "damage_type":  "����"
]),
([      "action":"$N�ڿն�������$w���Բ����һ��"HIB" ���� "NOR"ѹ��$n,��$n�޴��ɶ㡣",
        "force":query("max_neili", this_player())/4,
        "dodge":        10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "����",
        "damage_type":  "����"
]),
([      "action":"$N������ң�һ��"HIR" ���� "NOR"������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force":query("max_neili", this_player())/4,
        "dodge":        -5,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "����",
        "damage_type":  "����"
]),
([      "action":"$N��ǰһ��, ����$N����һת��һ��"HIC" �Ƶ� "NOR"������$w�����һ�㣬��֪������Ϯ��$n��$l��",
        "force":query("max_neili", this_player())/4,
        "dodge":        -10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "�Ƶ�",
        "damage_type":  "����"
]),
([      "action":"$N�ֳ�$w,������ԣ�һ��"HIR" ���� "NOR"����$w����ʺ�����$n,�ѽ�$n�����ڱ��¡�",
        "force":query("max_neili", this_player())/4,
        "dodge":        -20,
        "damage":query("shen", this_player())/2500,
        "skill_name":  "����",
        "damage_type":  "����"
]),
([      "action":"$N������Σ��ҽ�ͻȻ��ǰ������һ��"CYN" ֹ�� "NOR"������$w��ͬ����һ��������Ϣ�Ĵ���$n!",
        "force":query("max_neili", this_player())/4,
        "dodge":        0,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "ֹ��",
        "damage_type":  "����"
]),
([      "action":"$N��ǰ�ݳ�������ɹ�$nͷ����һ��"HIW" ���� "NOR"����$w����$n��$l",
        "force":query("max_neili", this_player())/4,
        "dodge":        100,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "����",
        "damage_type":  "����"
]),
([      "action":"$N����$w�γ������Ӱ��һ��"HIB" ���� "NOR"����ʵʵ�ı�Ӱ������ǵصĻ���$n",
        "force":query("max_neili", this_player())/4,
        "dodge":        50,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "����",
        "damage_type":  "����"
]),
([      "action":"$Nһ��"YEL" ���� "NOR"����$w�����������Ʒɻ�,�ܲ�͸�������$n��",
        "force":query("max_neili", this_player())/4,
        "dodge":        40,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "����",
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;
        int lvl = (int)me->query_skill("qingyun-bian", 1);
        int t = 1, j;
        if( query("max_neili", me)<500 )
                return notify_fail("����������㣬û�а취�����Ʊ޷�, ����Щ���������ɡ�\n");

        if ((int)me->query_skill("shaolin-xinfa", 1) < 80)
                return notify_fail("��������ķ����̫ǳ��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("���������һ�����Ӳ������޷���\n");
        if(lvl<=100)
        {
                if( lvl>10 && query("shen", me)<t*100 )
                        return notify_fail("�������̫���ˡ�\n");
        }
        else
        {
                if( query("shen", me)<(11100+(lvl-100)*1000) )
                        return notify_fail("�������̫���ˡ�\n");
        }
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
        level   = (int) me->query_skill("qingyun-bian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<50 )
                return notify_fail("����������������Ʊ޷���\n");
        me->receive_damage("qi", 5);
        return 1;
}

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qingyun-bian", 1) >= 50 )
                return __DIR__"qingyun-bian/" + action;
}

