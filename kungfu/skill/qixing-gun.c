// quanzhen-jianfa ȫ�潣��

inherit SKILL;

mapping *action = ({
([      "action" : "$N����б�ɣ�һ�С�����б��������δ��أ�$w��ָ��$n�ĺ���",
        "force" : 120,
        "dodge" : 20,
        "damage" : 25,
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "$NС�����������ֽ���������$wʹһʽ���˼����ġ�ֱ��$n������",
        "force" : 140,
        "dodge" : 15,
        "damage" : 30,
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С���ǰ���¡���ģ����ֺ�գ�����̵�֮�⾰�����϶��²���",
        "force" : 170,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 9,
        "damage_type" : "����"
]),
([      "action" : "$N�������𣬽�����ָ��һ�С�����С�á�������������ɨ$n������",
        "force" : 190,
        "dodge" : 10,
        "damage" : 50,
        "lvl" : 19,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�������ٰ����$w�������ߣ���ͬ�����������ֱ��������$n��$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 60,
        "lvl" : 29,
        "damage_type" : "����"
]),
([      "action" : "$N$wֱ�ؽ�����������ң���ɨ���ߣ�һʽ������Į������Ѹ������$n�ļ�ͷ",
        "force" : 280,
        "dodge" : 5,
        "damage" : 70,
        "lvl" : 39,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��ٰ���ü���������󽣾���Ծ����أ�����$wб��$n������",
        "force" : 300,
        "dodge" : 5,
        "damage" : 80,
        "lvl" : 59,
        "damage_type" : "����"
]),
([      "action" : "$N����ǰ�ӣ������｣���棬һ�С��ƴ����¡�������ǰ���$n��$lɱ��",
        "force" : 330,
        "dodge" : -5,
        "damage" : 90,
        "lvl" : 79,
        "damage_type" : "����"
]),
([  "action" : "$Nһ�С��ֻ���������$w����ʵ���ң�����ʵ����ʵĪ�磬����$n�ĸ���",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "����"
]),
([  "action" : "$Nһ�С�������������Ӣ�˲�����$w������㺮�ģ���÷��ʢ��������$n��$l",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "club") || (usage == "parry"); } 



int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");
        return 1;
        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("����ڹ���򲻵���\n");
}

mapping query_action(object me, object weapon)
{
        int i, level;
            level   = (int) me->query_skill("quanzhen-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("jingli", me)<50 )
                return notify_fail("��ľ���������ȫ�潣����\n");
        addn("jingli", -30, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"quanzhen-jianfa/" + action;
}