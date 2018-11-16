// xixing-dafa.c ���Ǵ�

#include <ansi.h>;
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if( query("character", me) == "��������" )
                return notify_fail("�����а��������ֺ��˵��书����ѧ��������\n");

        if( !query("family/family_name", me) || query("family/family_name", me) != "�������" )
                return notify_fail("�㲻��������̵��ˣ������������Ǵ󷨡�\n");

        if( query("con", me)<20 )
                return notify_fail("�����Ű��շ�����ת��һ����Ϣ����Ȼ�����Ļ���"
                                   "�٣�����ȴ��һ�������\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���Ϊ���㣬�����������Ǵ󷨡�\n");

        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me )
           && lvl < 200
           && lvl >= 10)
                return notify_fail("��û�а������Ǵ󷨵ľ��Ͻ�����ɢȥ�����ڻ���"
                                   "�����Լ������д󷨡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("���Ǵ�ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int)me->query_skill("xixing-dafa", 1) < 80
           || ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1
            || ob->query_skill_mapped("force") == "taixuan-gong")
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("force");
        if (ap / 2 + random(ap) < dp)
        {
                if( query("neili", me)<query("max_neili", me)*15/10 )
                        addn("neili", jiali, me);

                result = ([ "damage" : -damage ]);

                switch (random(4))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "ֻ��������ԴԴ��к"
                                             "�����ɵô��һ����\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
                                             "��ʯ���󺣣���֪���١�\n" NOR ]);
                        break;
                case 2:
                        result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
                                             "��Ӱ���٣���Ȼ��֪���䡣\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : HIM "$N" HIM "��ס�߶�����������"
                                             "ֻ����$n���ƺ���������\n" NOR ]);
                        break;
                }
                return result;
        }
}
void check_count(object me)
{
        if( !query("can_learn/xixing-dafa/ren", me )
            && query("max_neili", me) >= 3000
            && query("exception/xixing-count", me)>1000 )
        {
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        query("exception/xixing-count", me)/10);
                delete("exception/xixing-count", me);
        }
}

void skill_improved(object me)
{
        addn("exception/xixing-count", me->query_skill("xixing-dafa",1)+1, me);
        check_count(me);
}
string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}

int help(object me)
{
        write(HIC"\n���Ǵ󷨣�"NOR"\n");
        write(@HELP

    ������̺�ľ�µ�һ���ڹ���

    ���Ǵ󷨴��Ա���������ң�ɣ���Ϊ��ڤ�񹦺ͻ�������
·�������Ӵ�����Ϻ������ɷֱ��䣬�϶�Ϊһ����Ϊ���Ǵ󷨡�
��Ҫ�Ǽ̳��˻�����һ·����ϰ�ߵ���ﳣ����䣬������ȣ�
����������ȿ���ˮ��������Ϣ��ɢ֮��������Ѩ��
    ���Ǵ�ֻ�ܰ�������Ϊʦѧϰ�������൱��Ե����ѧ����

        ѧϰҪ��
                �����ķ�
                �����ڹ�10��
                �����ٵ�����
                ����ѧϰ�����ķ�
                ɢ��
HELP
        );
        return 1;
}
