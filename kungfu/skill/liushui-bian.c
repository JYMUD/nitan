//liushui-bian.c ��ˮ�޷�
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"ֻ��$N���μ�ת�������ᶶ��һʽ�����˫�ɡ���$w�����ϻ��������ɺ硣",
        "force" :180,
        "dodge" :10,
        "attack":30,
        "damage":50,
        "lvl"   :0,
        "skill_name" :"���˫��",
        "damage_type":"����"
]),
([      "action":"$Nһʽ������ƽ����������$w���²������·�һ�����̱���Ʈ��$n��ͷ���������롣",
        "force" :190,
        "dodge" :50,
        "attack":45,
        "damage":80,
        "lvl"   :10,
        "skill_name" :"����ƽ��",
        "damage_type":"����"
]),
([      "action":"$N����$w��һ�С�«��Ʈ�㡹����ӰƮ�������ص���$n��$l��",
        "force" :210,
        "dodge" :80,
        "attack":60,
        "damage":110,
        "lvl"   :80,
        "skill_name" :"«��Ʈ��",
        "damage_type":"����"
]),
([      "action":"$N�����趯$w��ȴ��һ�С������ƻá���ֻ���ж�������������ת��һ��δ������������������档",
        "force" :230,
        "dodge" :110,
        "attack":85,
        "damage":130,
        "lvl"   :110,
        "skill_name" :"�����ƻ�",
        "damage_type":"����"
]),
([      "action":"$Nһʽ��ǧɽĺѩ����$w�������磬��ʱ���ѩ�׷ף����������������滨�����ܹ�ס$nȫ��",
        "force" :250,
        "dodge" :140,
        "attack":120,
        "damage":150,
        "lvl"   :150,
        "skill_name" :"ǧɽĺѩ",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("���������һ�����Ӳ������޷���\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 150)
         return notify_fail("����ڹ��ķ����̫ǳ������ѧ��ˮ�޷���\n");

     if ((int)me->query_skill("whip", 1) < 150)
         return notify_fail("��Ļ����޷���򲻹���\n");

     if( query("max_neili", me)<500 )
         return notify_fail("�������̫�ͣ��޷�ѧ��ˮ�޷���\n");

     if ((int)me->query_skill("whip", 1) < (int)me->query_skill("liushui-bian", 1))
         return notify_fail("��Ļ����޷�ˮƽ���ޣ��޷������������ˮ�޷���\n");

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
     level = (int) me->query_skill("liushui-bian", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("���������һ�����Ӳ������޷���\n");

     if( query("qi", me)<110 )
            return notify_fail("���������������ˮ�޷���\n");

     if( query("neili", me)<115 )
            return notify_fail("���������������ˮ�޷���\n");

     me->receive_damage("qi", 92);
     addn("neili", -98, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"liushui-bian/" + action;
}
