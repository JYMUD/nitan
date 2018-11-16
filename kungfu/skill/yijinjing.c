// yijinjing.c ���� �׽��

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("yijinjing", 1);
        return (lvl / 20) * (lvl / 10) * 25 * 15 /100;
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( query("con", me)<20 )
                return notify_fail("���о���һ�����ֻ������ǰ������ð��̫��Ѩͻͻ������\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ�׽�񹦣�\n");

        /*
        if (me->query_skill("freezing-force", 1))
                return notify_fail("���Ѿ����׽�񹦺ͱ��Ϻ�����������һ�����ڹ��ˡ�\n");
        */

        if (me->query_skill("force", 1) < me->query_skill("yijinjing", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������������������׽�񹦣�\n");

        if( query("gender", me) != "����" )
                return notify_fail("�㲻�����ԣ��޷���ϰ�׽�񹦡�\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("�׽��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}
/*
void skill_improved(object me)
{
        int skill, lit;

        skill = me->query_skill("yijinjing", 1);
        lit = me->query_skill("literate", 1);

        if( skill == 200 && !query("sl/yijinjing", me) )
        {
                tell_object(me, HIW "\n��Ȼ����е�������Ϣ���ߣ�ԽתԽ�죬˲ʱ���Ѿ���ȫ������������һ���죬������ڵ���֮�У�\n" NOR);
                addn("max_neili", random(lit+skill), me);

                if( query("max_neili", me)>me->query_neili_limit() )
                        set("max_neili", me->query_neili_limit(), me);

                set("sl/yijinjing", 1, me);
        }
        if (skill == 400)
        {
                tell_object(me, HIW "\n��Ȼ����е�������Ϣ���ߣ�ԽתԽ�죬˲ʱ���Ѿ���ȫ������������ʮ���죬������ڵ���֮�У�\n" NOR);
                tell_object(me, HIW "�������ɰٶ��������ˡ�\n" NOR);
                set_temp("nopoison", 1, me);
        }
}
*/

string *fanzhen_msg = ({
        "ֻ���$N���ڸ��У���������һ�뷭ת��\n",
        "���ȷ��𣬽�$N��������ֽ��ȫ��Ѫɫ��\n",
        "���$N�ķ����ѣ�����������������\n",
        "�����Ѳ���ȫ����$N�����������ȥ��\n",
        "���$N������ת�������������߰˲���\n",
        "��$Nһײ��ֻ���$p�ؿ���Ѫ��ӿ��\n",
        "$N����ײ��һ���޻����棬����Ϊ��ĺ�ǽ��һ�㣬����������\n",
        "$N������$p��ͻȻ����һ�𣬵�ʱ���˳�ȥ��\n",
});
/*
mixed valid_damage(object me,object victim,int damage_bonus,int factor)

//factor= ���� damage_bonus=���� .
{
        int ap,dp;
//�ڹ����̫��(����2������),�����˺�ȫ������,�����ϲ�����
        ap=me->query_skill("force");
        dp=victim->query_skill("force");
        if( random(ap/2)>dp && query("neili", me)>2000 )
        {

                if (random(10)==1) tell_object(victim, "��ֻ������ͬ���ڽ����ϣ�ͷ��������һ����ͷ�������֣�\n");
                else tell_object(victim,HIY"��ֻ���þ�����ͬ���ڽ����֣������޷������ֺ���\n"NOR);
                tell_object(me, HIY"��ֻ���þ���Ϯ�壬��æ����������񹦣�һ����������ȫ��\n"NOR);
                addn("neili", -2*damage_bonus, me);
                return -damage_bonus;
        }
        else if( (random(ap*2)>dp) && query("neili", me)>1500 )
        {
                if (random(10)==1) tell_object(victim,HIY"��ֻ������ͬ���ڽ����ϣ�ͷ��������һ����ͷ���������֡���\n"NOR);
                else tell_object(victim,HIY"��ֻ���þ�����ͬ���ڽ����ϣ�����������ʹ��\n"NOR);
                tell_object(me, HIY"��ֻ���þ���Ϯ�壬������������֣�һ����������ȫ��\n"NOR);
                addn("neili", -damage_bonus, me);
                return -random(damage_bonus);
        }
        return 0;
}
*/
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;

        if( query("family/family_name", me) != "������" )
                return;

        if ((int) me->query_skill("yijinjing", 1) < 200 ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);

                        msg = random(2) ? HIR "$n��������һ�ɷ���֮����" : HIR "$n���Ͻ�ղ����������Ķ���";

                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;

                        ob->receive_damage("qi", damage / 10, me);
                        ob->receive_wound("qi", damage / 20, me);

                        result += ([ "msg" : msg ]);

                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                                result += ([ "msg" : HIR "������һ�����ε�ǽ��$n��ǰ�赲�ţ����"
                                                     "$N" HIR "һ���ӱ����������$N"
                                                     HIR "�ֱ۷��飡\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "���$n��������һ�ɷ���֮����$Nֻ������һ�ȣ�" +
                                                     weapon1->name() + HIR "��ʱ���ֶ������ɳ����⣡\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int skill;
        int i,j;

        if( query("family/family_name", me) != "������" )
                return;

        if (me->query_skill("yijinjing", 1) < 400 ||
            me->is_busy())
                return;

        skill = me->query_skill("force");

        i = damage_bonus * (skill + 1) / 1000;
        i = i/2+ random(i);
        if( query_temp("weapon", me) )
                i = i*3;
        if( query_temp("apply/damage", me) >= 1000 )
                i = i/3;

        j = me->query_skill("yijinjing", 1) / 2;
        i += j;
        message_combatd(HIR"$N"+HIR+"����һ����ţ������ھ�����������˫�ۣ�������֮�ƹ���$n��\n" NOR, me,victim);

        return i;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

string query_description()
{
        return
        "�׽��������ͷ�Ⱦ��������ڼ��⣬Ϊ���Ϸ�ħ�񹦡����ڹ�����������"
        "֮��������һ�����޷�ѧ�ɣ������׶ηֱ�Ϊ��0-200��200-400��>400����"
        "���׽��ǿ���壬�����Ϊ���м��ɽ�����ħ���ɽ��֮�壻�߼��ɿ�"
        "����ħ�����Σ����������ٶ����֡�";
}

int help(object me)
{
        write(HIC"\n�׽�񹦣�"NOR"\n");
        write(@HELP

    ���׽����ϴ�衷������Ϊ��������֮�����ഫΪ��Ħ��ʦ
���������в������ø�ɮ���٤��������������ϰ�����ѣ���ÿ�
�ơ����࣬���ࡱ�����в�����ϰ�书֮����������Ӻ�������
�ߡ�
    ��ϴ�衷�������������书�ľ�Ҫ�����׽����һ�ż����
����ڹ��ķ��鼮��

        ѧϰҪ��
                δ��ɫ���ͯ��֮��
                δ����
                ��Ԫһ����100��
                ��Ӧ����������ķ�
HELP
        );
        return 1;
}
