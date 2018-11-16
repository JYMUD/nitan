// linji-zhuang.c �ټ�ʮ��ׯ

#include <ansi.h>
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        if( query("sex", me) )
                return 0;

        lvl = (int)me->query_skill("linji-zhuang", 1);
        return lvl / 100 * lvl * 24 * 15 / 200;
}

string *skill_name = ({
        "����ׯ",
        "����ׯ",
        "֮��ׯ",
        "����ׯ",
        "����ׯ",
        "����ׯ",
        "����ׯ",
        "Ʈ��ׯ",
        "����ׯ",
        "С��ׯ",
        "����ׯ",
        "ڤ��ׯ",
        "�ټ�ʮ��ׯ",
});

string *combo_name = ({
        "���",
        "֮��",
        "����",
        "����",
        "��С",
        "��ڤ",
});
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i, np, nf, nh, ns, ts;
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);
        np = (int)me->query_skill("mahayana", 1);

        if( query("gender", me) != "Ů��" )
                return notify_fail("���Ů�ӣ�������ϰ�ټ�ʮ��ׯ��\n");

        if (np <= nh && np < 200)
                return notify_fail("��Ĵ�����͹���Ϊ�������޷�����������ټ�ʮ��ׯ��\n");

        if (nf < 40)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����ټ�ʮ��ׯ��\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�ټ�ʮ��ׯֻ����ѧ(learn)�������������ȡ�\n");
}

void skill_improved(object me)
{
        int level = me->query_skill("linji-zhuang",1);
        int o_lvl=query("linji_lvl", me);
        int i;

        if ( level > 180 ) return;

        if ( level/15*15 == level ) {
                tell_object(me, HIG "��ԡ�" + skill_name[level/15-1] + "���ѻ�Ȼ��ͨ��\n"NOR);
                if (o_lvl < level) {
                        tell_object(me, HIG"��ʱ��Ի����ڹ�������Ҳ�����ߡ�\n"NOR);
                        for (i=0; i< level; i++)
                        me->improve_skill("force", level);
                }
        }

        if ( level/30*30 == level )
        if (o_lvl < level) {
                tell_object(me, HIY"��ʱ��" + combo_name[level/30-1] +
                        "��ׯ�ڻ��ͨ��һ����͵���������ȫ��������Ϊ��������һ�㡣\n"NOR);
                addn("max_neili", level, me);
        }


        if( o_lvl<level)set("linji_lvl", level, me);

}
/*
void skill_improved(object me)
{
        switch (me->query_skill("linji-zhuang",1))
        {
                case 30:
                        tell_object(me, HIG "�����ׯ������! \n" NOR );
                        break;
                case 60:
                        tell_object(me, HIG "��֮��ׯ������! \n" NOR );
                        break;
                case 90:
                        tell_object(me, HIG "������ׯ������! \n" NOR );
                        break;
                case 120:
                        tell_object(me, HIG "�����ׯ������! \n" NOR );
                        break;
                case 150:
                        tell_object(me, HIG "���Сׯ������! \n" NOR );
                        break;
                case 180:
                        tell_object(me, HIG "����ڤׯ������! \n" NOR );
                        break;
        }
        return;
}
*/
string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

int help(object me)
{
        write(HIC"\n�ټ�ʮ��ׯ��"NOR"\n");
        write(@HELP

    �ټ�ʮ��ׯ����������������������˳���ǣ����֮�ġ�����
���ơ���С��ڤ������������;����ʼ�ڵ��Ҷ����ڷ�ҵ�������
�����硣ʮ��ׯ�ֱ���ʮ�����ֱ������ֿɷֱ��Ϊ����ׯ������
ׯ��֮��ׯ������ׯ������ׯ������ׯ������ׯ��Ʈ��ׯ������ׯ��
С��ׯ������ׯ��ڤ��ׯ��ÿ����һׯ���ж�������Ī��ô�����
���ǵ���ʮ��ׯ��Ϊ�����ڻ��ͨʱ����ָ��ء�֮�ġ���С����
�ס����ơ���ڤ������������Ϊ�������棬�������ӿ���ʹ�õ���
�����칦�ܡ����ܹ�ͨ��ڤ��ׯ���������������ɵ���������ʿ��
��������������ᡢˮ��ȼõľ��硢����ͨ�����鵤֮���
    �ټ�ʮ��ׯ������Ϊ�������ˣ���Ч�̶ȱ������ڹ��ߣ�����
���������ơ�

        ѧϰҪ��
                ��Ů����֮��
                �����˲�����ϰ30�����ϵ��ټ�ʮ��ׯ
                ��Ӧ����Ĵ�����͹�
                �����ڹ�10��
                ������
HELP
        );
        return 1;
}
