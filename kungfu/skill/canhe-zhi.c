// ����ָ��������ָ�����֡�
// �����书�ؼ�����Ľ�����ң�    ���÷�ָ������Ҷָ������ָ��
// ����������ס�֡������ߡ���  ����ָ
// �Ϻ�������Ϫ����              ����ָ
// �ض�������������              ������ָ
// ����ɽ���޶����ˡ���          �������ָ
// ���ϡ���ڤ���ˡ�              ��ڤָ
// ����Ϊ��
// canhe-zhi.c �κ�ָ��

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
//inherit F_SSERVER;
inherit SKILL;

string martialtype() { return "skill"; }

string *xue_name = ({
        "�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
        "����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
});

string *xue2_name = ({
        MAG "$NĬ����Ԫ�񹦣�������������ָ��ƽƽ�������޻��εص���$n������Ѩ" NOR,
        YEL "$N�������ϣ�����΢�飬������֮���ţ�����˫��ʳָ����һ��������ָ��ͬʱϮ��$n" NOR,
        WHT "$N��������ָ������ָ��ϳ�һ�ɽ�����ֱ��$n��ȥ"NOR,
        RED "$N�������֣���ָ���ǻ��ţ��ٻ���£ָ��ȭ����ʱ��������������Ľ�������" NOR,
        HIR "$Nָ��Ϭ������һ�����ν�������$n�������ڣ�$nֻ���ؿ�һʹ��ȫ��������к����" NOR
});
mapping *action = ({
([      "action": "$N˫ָ��£���������ϡ�"NOR + MAG "���÷�ָ" NOR "����"
                  "��" NOR + MAG "����ָ" NOR "��Ϊһʽ����ʱһ���ֱ��$n",
        "force" : 480,
        "attack": 110,
        "parry" :-90,
        "dodge" :-95,
        "damage": 160,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
]),
([      "action": "$N˫ָ���������ϡ�" HIG "����ָ" NOR "������" HIG "����Ҷ"
                  "ָ" NOR "��Ϊһʽ����ʱ����������$nȫ�����",
        "force" : 460,
        "attack": 100,
        "parry" :-90,
        "dodge" :-115,
        "damage": 180,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
]),
([
        "action": "ֻ��$Nʮָ���ţ�����ָָ��㣬����" HIY "�������ָ" NOR "����"
                  "��" HIY "������ָ" NOR "���ľ�����ʽͬʱʹ����\n��ʱ�����ݺᣬ��"
                  "ɰ���𣬱���$n��ȥ",
        "force" : 460,
        "attack": 100,
        "parry" :-135,
        "dodge" :-125,
        "damage": 180,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
]),
([
        "action": "ֻ��$N����Ծ�𣬳�Хһ������ն��£���" HIM "���ǽ���" NOR "������"
                  "��$nȫ�����",
        "force" : 460,
        "attack": 100,
        "parry" :-115,
        "dodge" :-145,
        "damage": 200,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
]),
([      "action": "$N�����ָ����ָ��������������������ָ��͸������" HIW "��ڤ����" NOR
                  "������$n�����Ѩ",
        "force" : 460,
        "attack": 120,
        "parry" :-130,
        "dodge" :-125,
        "damage": 200,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
]),
([      "action": "ң��$N���һָ�������$n��ָδ������" HIR "�κϽ���" NOR "���ѽ�$nѹ"
                  "��͸��������",
        "force" : 480,
        "attack": 120,
        "parry" :-150,
        "dodge" :-165,
        "damage": 240,
        "weapon" : HIR "�κ����彣��" NOR,
        "damage_type" : "����"
])
});

string main_skill() { return "canhe-zhi"; }

mapping sub_skills = ([
        "lianhua-zhi"    : 120,
        "tianlong-zhi"   : 120,
        "qilian-zhi"     : 120,
        "tianzhu-fuzhi"  : 120,
        "qixing-zhi"     : 120,
        "youming-zhi"    : 120,
        "xiuluo-zhi"     : 120,
        "duoluoye-zhi"   : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("int", me)<30 )
        {
                tell_object(me, "��ֻ�����Լ������ԣ��޷��ϳɲκ�ָ�񹦡�\n");
                return 0;
        }

        if( query("dex", me)<30 )
        {
                tell_object(me, "��ֻ�����Լ������鶯�ԣ������޷��ϳɲκ�ָ�񹦡�\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "����òκ�ָ�񹦼�����£��������о�һ��ѧ�ʿ��ܸ��а�"
                                "����\n");
                return 0;
        }

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
        {
                tell_object(me, "��������ϣ��������ͨ������ѧӦ�ø�����������\n");
                return 0;
        }
        */

        if (me->query_skill("martial-cognize", 1) < 200)
        {
                tell_object(me, "�㷢���Լ�����ѧ�����д���ߣ������޷������ɹ���\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 240)
        {
                tell_object(me, "�㷢���Լ����ڹ����������������޷������ɹ���\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "������Լ��������̣��޷��ϳɲκ�ָ�񹦡�\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIY "\n���Ǽ䣬��ֻ������������������ָ���������Ժ��н����\n"
                            "�֣��������ٴ��麣�������ڻ��ͨ����Ϊ���Ҿ�ѧ�κ�\n"
                            "ָ�񹦡�������ͨ���˲κ�ָ�ľ��ϡ�\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

int double_attack()
{
        return 1;
}

int valid_combine(string combo)
{
        /*
         object me = this_player();
         mappingmyfam=query("family", me);
         if (myfam["master_name"] == "Ľ�ݲ�")
        */
        return combo == "xingyi-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���κ�ָ������֡�\n");

        if( query("int", me)<30 )
                return notify_fail("�����������̫�ͣ��޷����κ�ָ��\n");

        if( query("dex", me)<30 )
                return notify_fail("����������������޷������κ�ָ��\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("����ڹ���򲻹����޷�������ָ��\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("�������̫�����޷������κ�ָ��\n");

        if ((int)me->query_skill("finger", 1) < 160)
                return notify_fail("��Ļ���ָ����򲻹����޷������κ�ָ��\n");

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("�㷢���������кܶ���������ľ��繹���йأ�������⡣\n");
        */

        if (me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("�����ѧ�����д���ߣ������޷������κ�ָ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("canhe-zhi", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ĳκ�ָ��\n");

        return 1;
}

int practice_skill(object me)
{
        int cost;

        if (me->query_skill("canhe-zhi", 1) > 120
            && me->query_skill("zihui-xinfa", 1) < 120)
                return notify_fail("���ϻ��ķ���Ϊ������������ȥ���»��߻���ħ��\n");

        if( query("qi", me)<130 )
                return notify_fail("�������̫���ˡ�\n");

        cost = me->query_skill("canhe-zhi", 1) / 2 + 60;

        if( query("neili", me)<cost )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("qi", 100);
        addn("neili", -cost, me);
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{

        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 280;
        int f_e2 = 380;
        int i, lvl, seq, ttl = sizeof(action);

        // if (! undefinedp(me->query_temp("canhe-action")))
        //        return action[me->query_temp("canhe-action")];

        if( random(10) == 1 && query("neili", me)>1000 )
        {
                addn("neili", -300, me);
                return ([       "action": HIC "$N" HIC "���������˫ָ���������ָ����"
                                          "�����ƿն����ġ��κϽ������Ѿ�����$n",
                                "dodge" :-140,
                                "parry" :-140,
                                "damage": 320,
                                "force" : 560,
                                "weapon" : HIR "�κ����彣��" NOR,
                                "damage_type": "����"
                        ]);
        }

        lvl = (int) me->query_skill("canhe-finger", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.0; }

string query_parry_msg(object victim_weapon)
{
        switch (random(3))
        {
        case 0:
                return NOR + WHT "$n" NOR + WHT"���˷���������ʳָ��ֱָ��$N" NOR + WHT
                       "��ǰ��Ѩ��$Nһ������æ�����Ծȡ�\n" NOR;
        case 1:
                return NOR + WHT "$n" NOR + WHT"˫ָ���������Ѹ���������������־��Ĳ�"
                       "�Ͻ�������������$N" NOR + WHT"�޴����֡�\n" NOR;
        default:
                return NOR + WHT "$n" NOR + WHT"��Хһ������������������$N" NOR + WHT
                       "˫ָ������������$P��Χ������һ����һ�㣬����������\n";
        }
}

/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, slv, p;
        object target;
        string msg;

        if (! target) target = offensive_target(me);
        if (! target) {return "";}
        lvl = me->query_skill("canhe-zhi", 1);

        // �������񽣾������Խ��κϽ����ۻ�
        if (slv = target->query_skill("six-finger", 1) > 200
            && target->query_skill_prepared("finger") == "six-finger"
            && slv >= me->query_skill("canhe-zhi", 1) - 60
            && random(10) == 0)
        {
                msg = action[random(sizeof(action))]["action"];
                msg += HIY "\n����$n" HIY "ббһָ�����ָ����磬�����ݺᣬ��Ȼ"
                       "���죬����$N" HIY "�Ľ���ȫ���ۻأ������Լ���ȥ��\n" NOR;

                me->receive_wound("qi", slv / 4 + random(slv / 6), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";
                return msg;
        }

        if (damage_bonus < 120 || lvl < 140) return 0;

        if (random(damage_bonus) > victim->query_dex()/10
            && query("neili", me)>200)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                        return HIR "��ֻ���������͡��ƿ������죬���Ͼ�����һЩѪ�Σ�\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"canhe-zhi/" + action;
}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy() || damage_bonus < 100) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>200) && random(me->query_skill("canhe-zhi",1))>60 )
                {
                        victim->start_busy(2);
                        addn("neili", -30, me);
                        if( query("neili", victim) <= (damage_bonus/2+30) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/2+30, victim);

                        return HIW "$NĬ����Ԫ�񹦣�ָ����ƮƮ�ص���$n��һ���ھ�������Ϣ������$n�����Ѩ��\n"
                               HIW "$nֻ��ȫ��һ�飬�ѱ�һ�е��С�" HIR + name + HIW "����\n" NOR;
                }
        }
}
*/

int help(object me)
{
        write(HIC"\n�κ�ָ��"NOR"\n");
        write(@HELP

    �κ�ָΪ����Ľ�ݼ�ָ��������Ľ���ϼ�ѧԨԴ���κ�ָ����
�಻ѷ�������ɴ������ָ��
    ���������ƻ�����

        ѧϰҪ��
                ��Ԫ��15��
                ����100
HELP
        );
        return 1;
}
