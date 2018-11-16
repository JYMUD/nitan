// This program is a part of NT MudLIB

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
BLU "$N����ƽƽ�̳�һ����ʵ���Ǻ����κα仯����ȴ�к��֮����$n"BLU"ֻ��\nһ�ɴ�����$w"BLU"ֱ������",
BLU "$N���Ծ�����潣�𣬽�������֮����������һ������$n"BLU"�������ڽ���֮��",
BLU "$N��̾һ�������ֺ���һ��������ָ��$n"BLU"��������˿���仯��ȴ���ý�\n�����裬����ƽ�����̺����б仯������ʤ����",
BLU "$NѸ������һ��������������磬�������磬�޿ɵ��棡�˽�֮�죬������\n˼��$n"BLU"�޷��ֱ����·ȥ��",
BLU "$N���׳�Х������Ʊ�ã������������һ��ƽָ������������$n"BLU"��\n�������$n"BLU"ֻ�������κ���֮�У������и���$N�������纣��һ�㣬һ��\nһ������ӿ�������Ӳ�����������ǿ",
BLU "$N����$w"BLU"��������ɽ���������ǰ���ͺ�һ�������ǽ�������ġ�����\nʽ�����������ǽ�Ӱ������ǧ��������ֻ��$n"BLU"����ζ�",
BLU "$N$w"BLU"����ʮ�ལ��һʱѸ�������ǻ��գ�һʱ���سٻ��������޼���Ѱ��\nƽ�������ַ�˼������˳�̣�������������������޲��ǽ��������ţ����淵��\n���棬ȴ�Ѳ��ٴ��κ�����",
});

mapping *action = ({
([      "action": "$N���е�$w����������󽭶�ȥ�������Ʋ��ɵ�",
        "force" : 250,
        "attack": 170,
        "dodge" :-30,
        "parry" :-70,
        "damage": 230,
        "lvl"   : 0,
        "damage_type": "����"
]),
([      "action": "$N̤��һ��������$w���һ����������$n��$l",
        "force" : 310,
        "attack": 280,
        "dodge" :-33,
        "parry" :-79,
        "damage": 224,
        "lvl"   : 40,
        "damage_type": "����"
]),
([      "action": "$N����$wһ����һ���̳�������$n��$l��û�а�㻨��",
        "force" : 330,
        "attack": 290,
        "dodge" :-41,
        "parry" :-85,
        "damage": 235,
        "lvl"   : 80,
        "damage_type": "����"
]),
([      "action": "$N����$w΢΢��������Ȼ�̳���һ����������$n��$l",
        "force" : 360,
        "attack": 295,
        "dodge" :-45,
        "parry" :-92,
        "damage": 239,
        "lvl"   : 120,
        "damage_type": "����"
]),
([      "action": "$N���$w����Ȼ��ɨ$n��������磬�����س�",
        "force" : 340,
        "attack": 297,
        "dodge" :-47,
        "parry" :-99,
        "damage": 248,
        "lvl"   : 160,
        "damage_type": "����"
]),
([      "action": "$N���е�$w�������̣��д���һ�������ӹ�$nȫ��",
        "force" : 380,
        "attack": 300,
        "dodge" :-50,
        "parry" :-100,
        "damage": 300,
        "lvl"   : 200,
        "damage_type": "����"
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        if( query("str", me)<26 )
                return notify_fail("������������������޷�ѧϰ����������\n");

        if( query("character", me) == "�ĺ�����" )
                return notify_fail("��һ����ɱ�����ˣ�û��������������ĵ��������塣\n");

        if( query("character", me) == "���ռ�թ" )
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û���������������\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ����������\n");

        if (me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("����ѧ�������㣬�޷���������������\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("�������̫��޷�ѧϰ����������\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷��������������������\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        object env;

        env = environment(me);
        if( !query("can_practice_xiantie-jian", env) &&
            me->query_skill("xuantie-jian", 1) < 180)
                return notify_fail("�����𽣻����˰��죬ֻ���ô˴����ʺ���ϰ����������\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("�����������������������\n");

        if( query("neili", me)<80 )
                return notify_fail("�����������������������\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        if( query("can_practice_xiantie-jian", env) )
        message_vision(HIW "\n$N" HIW"������Ϣ�����������е�"+ weapon->name() + HIW "������������࿹��\n\n", me);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon=query_temp("weapon", me);

        lvl = me->query_skill("xuantie-jian", 1);

        if (damage_bonus < 120
           || lvl < 160
           || ! objectp(weapon)
           || query("neili", me)<500
           || me->query_skill_mapped("sword") != "xuantie-jian" )
                      return damage_bonus / 4;

        //if (lvl / 2 + random(lvl) > victim->query_skill("parry", 1))
        {
                addn("neili", -120, me);
                victim->receive_wound("qi", damage_bonus * 4 / 5, me);

                return HIW "$N" HIW "����" + weapon->name() + HIW "����������������£�����"
                       "�ɵ�������$n" HIW "�����ƻֺ�֮����\n" NOR;
         }
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}
int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("xuantie-jian", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 90;
        if (lvl < 325) return 100;
        if (lvl < 350) return 110;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("id", weapon) != "ironsword" )
                return 0.8;
        else return 1.2;
}