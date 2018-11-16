// hanbing-zhenqi.c ��������
// Last Modified by winder on Jul. 20 2001

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_force(string force)
{
        return force == "songshan-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hanbing-zhenqi", 1);
          return lvl * lvl * 15 * 18 / 100 / 200;
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("character", me) == "��������" )
                return notify_fail("�����а��룺�����¹������䣬ѧ��������"
                                   "�书������\n");

        if( query("gender", me) == "����"
           && (int)me->query_skill("hanbing-zhenqi", 1) > 19)
                return notify_fail("���޸����ԣ��������������Զ�������������\n");

        if( query("con", me)<34 )
                return notify_fail("��������ǲ������޷���������������\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹������Զ�������������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("��Ŀǰ��������Ϊ���������Զ�������������\n");

        if (me->query_skill("force", 1) < me->query_skill("hanbing-zhenqi", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ��������ĺ���������\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        int lvl  = me->query_skill("hanbing-zhenqi", 1);
        int flvl=query("jiali", me);

        result = ::hit_ob(me, victim, damage_bonus, factor);

        if (intp(result) && result > 0)
        {
                if( query("neili", me)<500
                   || lvl < 220
                   || flvl < 100
                   || random(3) != 1)
                        return;

                if( query_temp("weapon", me )
                    || query_temp("secondary_weapon", me )
                    || !query_temp("freezing", me) )
                        return;

                if (flvl * 2 + random(lvl) > victim->query_skill("force"))
                {
                        victim->affect_by("freezing",
                               ([ "level"    : flvl * 3,
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));

                        addn("neili", -80, me);

                        return random(2) ? ([ "damage" : result,
                                              "msg"    : HIW "$n" HIW "����$N" HIW "һ�У���"
                                                         "ʱֻ�е�����Ϯ�壬˵�����Ķ�������"
                                                         "��\n" NOR ]):

                                           ([ "damage" : result,
                                              "msg"    : HIW "ֻ��$n" HIW "ȫ��һ������Ƥ��"
                                                         "�ϣ���������$N" HIW "�����ھ��ĸ�"
                                                         "�š�\n" NOR ]);
                }
        }
        return result;
}

string exert_function_file(string func)
{
        return __DIR__"hanbing-zhenqi/" + func;
}
int help(object me)
{
        write(HIM"\n����������"NOR"\n");
        write(@HELP

    ��ɽ�ɱ����ڹ���

        ѧϰҪ��
                �����ڹ�10��
                ��Ӧ������
HELP
        );
        return 1;
}
