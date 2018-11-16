// yunv-xinfa.c ��Ů�ķ�
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yunv-xinfa", 1);
        return lvl * lvl * 15 * 12 / 100 / 200;
}

int valid_force(string force)
{
        // return (force == "minggu-xinfa");
        return 1;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( (!me->query_family() ||
            me->query_family() != "��Ĺ��") && (!query("reborn/times", me) || member_array("��Ĺ��", query("reborn/fams", me)) == -1) )
                return notify_fail("�㲻�ǹ�Ĺ�����ˣ��޷���ϰ��\n");

        if( query("gender", me) == "����" )
                return notify_fail("���޸����ԣ������ѵ���������ϰ��Ů�ķ���\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("��Ļ����ڹ���򻹲�����������ϰ��Ů�ķ���\n");

        if ((int)me->query_int() < 42)
                return notify_fail("��ĺ������Բ��㣬�޷�������Ů�ķ���\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬���������Ů�ķ���\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��Ů�ķ�ֻ����ѧ(learn)�����������ȡ�\n");
}
mixed hit_ob(object me, object victim)
{
        int lvl;
        int damage_bonus;
        string wn;
        object weapon;

        lvl = me->query_skill("yunv-xinfa", 1);

        if (lvl < 150
             || query("neili", me)<300
             || !objectp(weapon=query_temp("weapon", me) )
            || random(me->query_skill("force") / 6) < victim->query_con()
            || random(3) > 1
             || !query("can_learn/yunv-xinfa/wall", me) )
                return 0;

        wn = weapon->name();

        if( query("skill_type", weapon) == "sword"
            && me->query_skill_mapped("sword") == "suxin-jian")
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 5 + random(lvl / 5);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "����" + wn + HIW "����һ�񣬽���"
                       "Ů�ľ��������ڽ��ˣ������ޱߺ��⡣\n" NOR;
        } else
        if( query("skill_type", weapon) == "whip"
            && me->query_skill_mapped("whip") == "yinsuo-jinling")
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 4 + random(lvl / 4);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "һ�����ȣ�����Ů�ķ���������" + wn +
                       HIW "֮�ϣ�����������������Ȼ�𾴡�\n" NOR;
        }
}
int difficult_level()
{
        return 400;
}

string exert_function_file(string func)
{
        return __DIR__"yunv-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n��Ů�ķ���"NOR"\n");
        write(@HELP

    ��Ĺ�ڹ�����һ���������֣�Ψ��ƽ�ľ�������������֮�Ų�
����ϰ�ϳ��书����Ů�ľ������ѶȺܴ�ѧϰ��Ҫ�������꣬ѭ
�򽥽����гɹ�֮��������Ѱ�ٱ����ؼ�����Ů�ľ������²��ж���

        ѧϰҪ��
                �����ڹ�10��
                ������̫��
HELP
        );
        return 1;
}
