// yuenv-jian.c ԽŮ����
// Modify by Rcwiz for hero.cd

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N����$w�������$n��$l��Ѹ���ޱ�",
        "force"  : 100,
        "attack" : 130,
        "dodge"  : 120,
        "parry"  : 12,
        "damage" : 70,
        "lvl"    : 0,
        "damage_type" : "����"
]),
([      "action" : "$N��Ծ�������е�$w����һ����������Ȼ����$n",
        "force"  : 120,
        "attack" : 140,
        "dodge"  : 125,
        "parry"  : 15,
        "damage" : 84,
        "lvl"    : 20,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ������ಽ�����е�$wб��$n��$l",
        "force"  : 140,
        "attack" : 140,
        "dodge"  : 130,
        "parry"  : 10,
        "damage" : 100,
        "lvl"    : 50,
        "damage_type" : "����"
]),
([      "action" : "$Nȴ���Ჽ�����е�$w�Ƶ��ɵ����ƽ��ǽ�������ֱ��$n",
        "force"  : 160,
        "attack" : 160,
        "dodge"  : 138,
        "parry"  : 10,
        "damage" : 110,
        "lvl"    : 75,
        "damage_type" : "����"
]),
([      "action" : "$N����$w�����ļ��죬ֻ�ϵ�$n�ۻ����ң��벻֪�Ӻι���",
        "force"  : 180,
        "attack" : 180,
        "dodge"  : 145,
        "parry"  : 12,
        "damage" : 125,
        "lvl"    : 100,
        "damage_type" : "����"
]),
([      "action" : "$N�������𣬽�����ָ�����������ƣ�ֱ��$n��$l",
        "force"  : 200,
        "attack" : 185,
        "dodge"  : 150,
        "parry"  : 18,
        "damage" : 130,
        "lvl"    : 130,
        "damage_type" : "����"
]),
([      "action" : "$N����$w��������һ�̣�û���κλ��ɣ�Ȼ�����ǿ�ò���˼��",
        "force"  : 220,
        "attack" : 210,
        "dodge"  : 155,
        "parry"  : 15,
        "damage" : 140,
        "lvl"    : 160,
        "damage_type" : "����"
]),
([      "action" : "$N��̾һ�������е�$w����һ����������$n",
        "force"  : 240,
        "attack" : 230,
        "dodge"  : 170,
        "parry"  : 22,
        "damage" : 150,
        "lvl"    : 200,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�����е�$w���������������������$n",
        "force"  : 260,
        "attack" : 250,
        "dodge"  : 185,
        "parry"  : 25,
        "damage" : 155,
        "lvl"    : 225,
        "damage_type" : "����"
]),
([  "action" : "$Nһ����Ц������$w�û��������ǵ㣬��֪����$n�ĺδ�",
        "force"  : 320,
        "attack" : 280,
        "dodge"  : 220,
        "parry"  : 30,
        "damage" : 180,
        "lvl"    : 250,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{

        if( query("gender", me) != "Ů��" )
                return notify_fail("��������ȥ����������������ʺ�Ů����ϰ��\n");

        if( query("dex", me)<13 )
                return notify_fail("�����������㣬�޷�����ԽŮ������\n");

        if ((int)me->query_skill("dodge", 1) < 200)
                return notify_fail("����Ṧ��򲻵����޷�����ԽŮ������\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ľ������ײ��У��������ԽŮ������\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("�������̫��޷�ѧϰԽŮ������\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuenv-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ԽŮ������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yuenv-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("�������������ԽŮ������\n");

        if( query("neili", me)<70 )
                return notify_fail("���������������ԽŮ������\n");

        me->receive_damage("qi", 64);
        addn("neili", -65, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;
        int ap, dp;

        weapon=query_temp("weapon", me);

        attack_time = (int)(me->query_skill("yuenv-jian", 1) / 40);

        if (attack_time > 7)
                attack_time = 7;

        ap = me->query_skill("sword"); 
        dp = victim->query_skill("dodge");

        if (me->is_busy()
           || ! living(victim)
            || query("neili", me)<200
           || ap * 3 / 5 + random(ap) < dp
            || query_temp("is_attacking", me )
           || me->query_skill_mapped("sword") != "yuenv-jian"
           || me->query_skill("yuenv-jian", 1) < 120)
                return 0;
        
        message_vision(HIW "\n���Ǽ䣬ֻ��$N" HIW "����" + weapon->name() + HIW "��ӯ�鶯"
                       "����������������һ˿����֮����ȴ��$n" HIW "������Ͼ������\n"
                       NOR, me, victim);

        set_temp("is_attacking", 1, me);
        me->start_busy(1 + random(attack_time / 2));
        addn("neili", -attack_time*20, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        delete_temp("is_attacking", me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuenv-jian/" + action;
}
