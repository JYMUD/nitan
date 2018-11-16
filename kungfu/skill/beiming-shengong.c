// beimin-shengong.c ��ڤ��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int valid_enable(string usage) { return usage=="force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int valid_force(string force) { return 1; }

// beiming ����Ӧ�ø�10��
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("beiming-shengong", 1);
        return lvl /10 * lvl /10 * 28 * 15 / 10 / 10;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("beiming-shengong", 1);

        if( query("gender", me) == "����" && lvl>49 )
                return notify_fail("���޸����ԣ���������������������ı�ڤ�񹦡�\n");

        if( query("con", me)<24 )
                return notify_fail("���˰ɣ���������ǲ��ã���ǿѧ�ˡ�\n");

        if( query("int", me)<30 )
                return notify_fail("���˰ɣ����������Բ��ã���ǿѧ�ˡ�\n");

        if (me->query_skill("force", 1) <= lvl)
                return notify_fail("��Ļ����ڹ�������������ѧ��ȥ���߻���ħ�ġ�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��ڤ��ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int) me->query_skill("beiming-shengong", 1) < 80 ||
            ob->query_skill_mapped("force") == "taixuan-gong" ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap = ob->query_skill("force") + ob->query_skill("dodge");
        dp = me->query_skill("force") + me->query_skill("dodge");
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "ֻ��������ԴԴ��к"
                                             "�����ɵô��һ����\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
                                             "��ʯ���󺣣���֪���١�\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : HIM "$N" HIM "��ס�߶�����������"
                                             "ֻ����$n���ƺ���������\n" NOR ]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int percent,force1,force2,dodge1,dodge2,lv1,lv2;

        force1 = victim->query_skill("force");
        force2 = me->query_skill("force");
        dodge1 = victim->query_skill("dodge");
        dodge2 = me->query_skill("dodge");

        lv1= force1*dodge1;
        lv2= force2*dodge2;

        lv2 = lv2*3/2;
        if ((int)me->query_skill("beiming-shengong",1)>100
         && !query_temp("weapon", victim )
         && query("max_neili", victim)>500
        && lv1/2 + random(lv2) > lv1 )
        {
                addn("max_neili", -1*(5+(me->query_skill("beiming-shengong",1)/100)), victim);
                if( query("max_neili", me)<me->query_current_neili_limit() )
                addn("max_neili", 1*(5+(me->query_skill("beiming-shengong",1)/100)), me);
                return ([ "msg": HIR "$nֻ��Ϣ��һ����һ��������$N���˹�ȥ��\n" NOR ]);
        }

        return damage_bonus;
}

int difficult_level()
{
        return 200;
}

string exert_function_file(string func)
{
        return __DIR__"beiming-shengong/" + func;
}
int help(object me)
{
        write(HIC"\n��ڤ�񹦣�"NOR"\n");
        write(@HELP

    ��ڤ��Ϊ��ң�������ڹ���
    ׯ�ӡ���ң�Ρ����ƣ����֮����ڤ���ߣ����Ҳ�������ɣ�
�����ǧ�δ��֪����Ҳ�������ƣ����ҷ�ˮ֮��Ҳ��������
������Ҳ����������ˮ������֮�ϣ����Ϊ֮�ۣ��ñ����򽺣�ˮ
ǳ���۴�Ҳ�����ǹ���ң���书���Ի�������Ϊ��һҪ�塣������
�������书�޲�Ϊ�����ã���֮��ڤ������С���޲��أ�����С
���޲��ݡ��ǹ�����Ϊ��������Ϊĩ����ڤ��ϵ������֮������
Ϊ���С���ڤ��ˮ���������������ƣ��ٴ��㺣����֮ˮ���ݰ�
�����á�����޽������ڻ��ۡ�
    �����������������Ŷ������̣�����ң�����������֮����
���̶������ţ�Ĵָ������ӣ���֮�������������������ŵ���
Ѩ��Ȼ��֮������ʤ���ң���ˮ������뽭�ӣ�����Ī������ң
����֧��δ��Ҫ����Ω��������������������Ϊ���ã�����ȡǧ��
������֮�ڵأ�������������Ҳ��

        ѧϰҪ��
                �����ڹ�10��
                ̫���޷�ѧ��50�����ϵı�ڤ��
HELP
        );
        return 1;
}
