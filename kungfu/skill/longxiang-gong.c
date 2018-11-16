#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("longxiang-gong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
        /*
        return force == "mizong-neigong" ||
               force == "xiaowuxiang" ||
               force == "yijinjing" ||
               force == "xixing-dafa";
        */
}

mapping *action = ({
([      "action" : "$N����һ�����˾������������������Х����$n��$l����ȥ",
        "dodge"  : 37,
        "force"  : 430,
        "attack" : 173,
        "parry"  : 41,
        "damage" : 133,
        "damage_type": "����"
]),
([      "action" : "$N��ȭ���ƣ�������������������ľ������͵�����$n��$l",
        "dodge"  : 35,
        "force"  : 440,
        "attack" : 177,
        "parry"  : 47,
        "damage" : 121,
        "damage_type": "����"
]),
([      "action" : "$N����������˫ȭͬʱ���������������������$n$l����ȥ",
        "dodge"  : 37,
        "force"  : 450,
        "attack" : 182,
        "parry"  : 46,
        "damage" : 123,
        "damage_type": "����"
]),
([      "action" : "$N���������������˫ȭƽ�ƣ���ʱһ���������ֱϮ$n",
        "dodge"  : 27,
        "force"  : 480,
        "attack" : 183,
        "parry"  : 35,
        "damage" : 145,
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("longxiang-gong", 1);

        if (lvl >= 150)
                return usage == "force" ||
                       usage == "parry" ||
                       usage == "unarmed";

        else if (lvl >= 30)
                return usage == "force";

        else
                return usage == "force";
}

int valid_learn(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if( query("str", me)<30 )
                return notify_fail("������������������޷����������������\n");

        if( query("con", me)<30 )
                return notify_fail("�����������������޷����������������\n");

        if( query("gender", me) == "����" && layer >= 1 )
                return notify_fail("���޸����ԣ������������޷����������������\n");

        if ((int)me->query_skill("lamaism", 1) < 100)
                return notify_fail("��������ķ���ⲻ����������������������\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ�����㣬������������������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬������������������\n");

        if (me->query_skill("force", 1) < lvl)
                return notify_fail("��Ļ����ڹ�ˮƽ�������������������������������\n");

        if( query("max_neili", me)<layer*500 )
                return notify_fail("���������Ϊ�������������������������������\n");

        if (me->query_skill("lamaism", 1) < layer * 25)
                return notify_fail("��������ķ���ⲻ�����������������������������\n");

        if (me->query_skill("unarmed", 1) < lvl && layer >= 5)
                return notify_fail("��Ļ���ȭ��ˮƽ�������������������������������\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if (layer > 13) layer = 13;

        if (damage_bonus < 130
           || layer < 6
            || query("neili", me)<500
            || query_temp("weapon", me )
            || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "longxiang-gong"
           || me->query_skill_mapped("unarmed") != "longxiang-gong"
           || me->query_skill_prepared("unarmed") != "longxiang-gong"
           || damage_bonus / 6 < victim->query_con() / 10
           //|| random(10) < 5
           )
                return 0;

        if (layer >= 10 && random(2) == 1)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 50) / 3, me);
                return HIY "$N" HIY "ȭ��֮�Ͼ��̲��š�" HIR "ʮ��ʮ��"
                       HIY "��֮��������壬�ݻ���$n" HIY "����Ԫ��\n" NOR;
        } else
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                return HIY "$N" HIY "˫ȭ���������������" + chinese_number(layer) +
                       "�㹦����$n" HIY "�����������һ����Ѫ��\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("���������ֻ����ѧ(learn)�����������ȡ�\n");
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("longxiang-gong", 1);
        layer = lvl / 30;

        if( lvl>400 && !query("can_perform/longxiang-gong/zhen", me) )
        {
                tell_object(me, HIR "��ͻȻ��Ϭһ����������������������ɵ��桤�������ؾ���\n" NOR);
                set("can_perform/longxiang-gong/zhen", 1, me);
        }

        if ((lvl % 30) == 0 && layer > 13)
        {
                tell_object(me, HIY "�������������ֽ���һ�㡣\n" NOR);
        } else
        if ((lvl % 30) == 0)
        {
                tell_object(me, HIY "�������˵�" + chinese_number(layer) +
                                "��������������\n" NOR);
        }
}

int difficult_level()
{
        object me;
        int lvl;

        if (me = this_player())
        {
                // ��С���๦������ѧϰ��
                if (lvl = me->query_skill("xiaowuxiang", 1))
                        return 3000;

                // �о����񹦣�����ѧϰ��
                if (lvl = me->query_skill("jiuyang-shengong", 1))
                        return 1000;
        }

        return 300;
}
string perform_action_file(string action)
{
        return __DIR__"longxiang-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"longxiang-gong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n�����������"NOR"\n");
        write(@HELP

    ��������������������������������ϵĻ����񹦡�Ϊѩɽ��
�����ڹ�����������������Ե�������ʮ�����ϣ�ÿ��һ�У�����
ʮ��ʮ��Ĵ������������������������

    �����������������ʮ���㣬��һ�㹦��ʮ��ǳ�ף���������
֮�ˣ�ֻҪ�õ����ڣ�һ�����м������ɡ��ڶ���ȵ�һ�����һ
������ʱ�����ꡣ�������ֱȵڶ������һ������ʱ�߰��ꡣ���
�ɱ�������Խ������Խ�ѽ�չ������������Ժ���������һ�㣬
����������ʮ�����Ͽ๦������һ�ţ���ɮ��ʿ��������������һ
ʮ���㡰�����������ȴ��δ��һ������ʮ�����ϡ��⹦��ѭ��
�����������޲�������֮�������˵���ǧ����䣬���ձ����ʮ
���㾳�磬ֻ���������ޣ������еĸ�ɮ��ʿ������������֮ǰ��
�����߲㡢�ڰ˲㣬��ǵ�������ɣ���һ�����������������ٲ�
��Ĵ�Σ����������䣬�ر�����һλ��ɮ�����˵ھŲ㣬������
�;�������������ʮ��ʱ����ħ�����޷����ƣ����ڿ���������
ҹ�����վ���������

        ѧϰҪ��
                �����ڹ�10��
                ��Ӧ������
                �ǳ������ﲻ��ѧ��30�����ϵ����������
                ̫�಻��ѧ��50�����ϵ����������
HELP
        );
        return 1;
}
