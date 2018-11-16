#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiantian-gong", 1);
        return (lvl / 10) * (lvl / 20) * 15 * 22 / 100;
}

int valid_force(string force)
{
        return 1;
        return force == "quanzhen-xinfa" ||
               force == "xuanmen-neigong";
}

mapping *action = ({
([      "action" : "$N����һ�����˾����칦��������Х����$n��$l����ȥ",
        "dodge"  : -87,
        "force"  : 430,
        "attack" : 163,
        "parry"  : -81,
        "damage" : 83,
        "damage_type": "����"
]),
([      "action" : "$N����ƽ�죬�����������칦�ľ������͵�����$n��$l",
        "dodge"  : -85,
        "force"  : 440,
        "attack" : 147,
        "parry"  : -77,
        "damage" : 81,
        "damage_type": "����"
]),
([      "action" : "$N����һչ�����ƻ�ס�����������й�ֱ��������$n$l",
        "dodge"  : -75,
        "force"  : 450,
        "attack" : 182,
        "parry"  : -67,
        "damage" : 93,
        "damage_type": "����"
]),
([      "action" : "$N��ת����������˫�ƻ�Ȧ����ʱһ�����ȵ�����ֱϮ$n",
        "dodge"  : -87,
        "force"  : 480,
        "attack" : 183,
        "parry"  : -85,
        "damage" : 105,
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("xiantian-gong", 1);

        if (lvl >= 180)
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";

}

int valid_learn(object me)
{
        if( query("character", me) != "��������"
            && query("character", me) != "��ʿ��˫" )
                return notify_fail("��ֻ�����칦����ֺ룬���Լ��������ƺ���������\n");

        /*
        if( query("int", me)<28 )
                return notify_fail("����������Բ��㣬��������������칦��\n");
        */

        if( query("con", me)<32 )
                return notify_fail("�����������������޷�������������칦��\n");

        if( query("gender", me) == "����" && query("xiantian-gong", me)>29 )
                return notify_fail("���޸����ԣ�������������������������칦��\n");

        if ((int)me->query_skill("taoism", 1) < 200)
                return notify_fail("��Ե�ѧ�ķ�����ⲻ��������������칦��\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ�����㣬����������칦��\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż���㣬����������칦��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����������칦��\n");

        if (me->query_skill("taoism", 1) < 320
           && me->query_skill("taoism", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("��Ե�ѧ�ķ�����ⲻ�������Զ������������칦��\n");

        if (me->query_skill("force", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ������������칦��\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("xiantian-gong", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���������Զ������������칦��\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("xiantian-gong", 1);

        if (damage_bonus < 50
           || lvl < 180)
                return 0;

        if (damage_bonus > victim->query_con()/10)
        {
                addn("neili", -30, me);
                victim->receive_wound("qi", damage_bonus / 2, me);
                return HIR"����""$N""�Ĺ���,һ�����촿������˲�䱬���˳�����$n"  //return HIW "$N" HIW "���칦��Ǳ�������˳�����ͻȻ��$n"
                       HIR "ֻ�����ھ�٣�����ɳ���ޱȣ�������һ����Ѫ��\n" NOR;// HIW "ֻ�к���һ�����һ����Ѫ��\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("���칦ֻ����ѧ(learn)�����������ȡ�\n");
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
//        if ((int)this_player()->query("int") < 28)
//                return "����������Բ������޷�֪������������칦���С�\n";

        return __DIR__"xiantian-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"xiantian-gong/exert/" + action;
}

/*
void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("xiantian-gong", 1);

        if (lvl > 220
         && query("can_exert/xiantian-gong/shentong", me) <= 60 )
        {
                if( me->add("can_exert/xiantian-gong/shentong",random(i))<60 )
                {
                        tell_object(me, HIC "������칦��" HIW "������ͨ��"
                                        HIC "�������µ�����\n" NOR);
                } else
                {
                        tell_object(me, HIC "��ͨ�������칦��" HIW "������ͨ��"
                                        HIC "���İ��ء�\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }
}
*/

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        int ap, dp, cost;
        mapping result;

        if (me->query_skill("xiantian-gong", 1) < 200 ||
            me->query_skill_mapped("force") != "xiantian-gong" ||
            query("neili", me)<1000 ||
            ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap=ob->query_skill("force")*12+query("max_neili", ob)+ob->query_skill("count",1);
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "ֻ��$n" HIR "���커������Ȼ��"
                                            "Ȼ��������$N" HIR "���������������"
                                            "ȥ��\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "ֻ��$n" HIR "���커������Ȼ��"
                                            "Ȼ��������$N" HIR "�Ĺ�����Ϊ���Ρ�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "ֻ��$n" HIR "���커������Ȼ��"
                                            "Ȼ�������ֿ�$N" HIR "�Ĺ�����\n" NOR]);
                        break;
                }
                return result;
        }
}
