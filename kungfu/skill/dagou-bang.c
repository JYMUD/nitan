// dagou-bang.c �򹷰���

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$Nʹ��һ��"HIG"������˫Ȯ��"NOR"������$w���������������$n��$l",
        "lvl"        : 10,
        "skill_name" : "����˫Ȯ"
]),
([      "action": "$N����$w���һζ���һ��"HIG"������Ѱ�ߡ�"NOR"��$n��$l��ȥ",
        "lvl"        : 20,
        "skill_name" : "����Ѱ��"
]),
([      "action": "$N����$w���Ӹ�����ʹһ��"HIG"����ݾ��ߡ�"NOR"����$n��$l",
        "lvl"        : 30,
        "skill_name" : "��ݾ���"
]),
([      "action": "$Nʩ��"HIG"���������졹"NOR"��$w����������$n��ȥ",
        "lvl"        : 40,
        "skill_name" : "��������"
]),
([      "action":"$N�������һ����â�����������ʹ��"HIR"�������޹���"NOR"������ǵ�����",
        "lvl"        : 50,
        "skill_name" : "�����޹�"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("dex", me)<26 )
                return notify_fail("���������̫��޷�ѧϰ�򹷰�����\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬�޷�ѧϰ�򹷰�����\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("��Ļ����ȷ��������޷�ѧϰ�򹷰�����\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ĵ򹷰�����\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("��������������򹷰�����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������򹷰�����\n");

        me->receive_damage("qi", 75);
        addn("neili", -80, me);
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("dagou-bang", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "����",
        ]);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
            || !query_temp("feng_zijue", me )
            || !(weapon=query_temp("weapon", me) )
            || ! living(me)
            || query("skill_type", weapon) != "staff" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "�����ʩչ�򹷰���" HIY "��"
                                            HIG "���־�������" + weapon->name() + HIG
                                            "����ұգ�ʹ��$N" HIG "�Ĺ���ȫȻ��ա�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "��ת����" + weapon->name() +
                                            HIG "���򹷰���" HIY "��" HIG "���־�����"
                                            "�����쾡�£��ٽ�$N" HIG "����ʽ�������Ρ�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "���ʩչ���򹷰����⡹��"
                                 "��������$N" HIY "��Ҳ������������ֱ"
                                 "�룬��Ϯ$n" HIY "��\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "��ת����" + weapon->name() +
                                 HIY "������ұգ�Ȼ��$N" HIY "ȴ�Ǿ���"
                                 "������˿������$n" HIY "���Ի�\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage)
{
        string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if (random(fmsk) >= random(600))
                damage += fmsk / 2 + random(fmsk / 2);

        if( !objectp(weapon=query_temp("weapon", me)) )
                return 0;

        zhencost = sqrt(weapon->weight() / 10) + 10;
        if( query("neili", me)<zhencost || query("jing", me)<zhencost )
                return 0;

        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);



        if (random(ap+dp) > ap)
        {
                result=HIG"ͻȻ����������������������޷���"+query("name", weapon)+HIG"������$n��\n"NOR;
                damage=query("weapon_prop/damage", weapon)*3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap)
        {
                result = HIG "$N�͵صݳ�һ�У���һ��Ѹ�����ף�ֱȡ$nü�ģ�$p��������һ�������˳����ߣ�\n" NOR;
                damage=query("weapon_prop/damage", weapon)*2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "�϶�������֮�侹��ת��$n����ĵ�һ������$p���ϳ���һ�¡���\n" NOR;
                damage=query("weapon_prop/damage", weapon);
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point() { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "staff" )
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}

int help(object me)
{
        write(HIC"\n�򹷰�����"NOR"\n");
        write(@HELP

    ��ʮ��·�򹷰�����ؤ�￪����ʦү������������ǰ�ΰ�����
���ΰ��������������ڶ����ˡ�ؤ������ΰ������书��ʤ������
ʦ��������·�����и�������������仯������������ؤ��굽Σ
�ѹ�ͷ���������Գ�������������򹷰�������ɱ�У�����Ⱥа��
    �򹷰���������Ȼª�ף����仯��΢���������ʵ�ǹ�����
����ѧ�е�һ������Ĺ���׿Ȼ�Գ�һ�ң�������ɵĹ������
ǣ�档��ѧ���������ǲ����������������������������⡢ת��
���ֿھ�������һ�����á�ÿ��ھ�������ÿ���������䣬������
ٱ��Ϊؤ����������ഫ�����֮����

        ѧϰҪ��
                ��������50��
                ����200
HELP
        );
        return 1;
}
