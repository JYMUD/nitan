// huoyan-dao.c ���浶

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$Nʹ��һ��"RED"����ľȡ��"NOR"������ת��˫����ǰƽƽ����$n",
        "skill_name" : "��ľȡ��",
        "lvl" : 0
]),
([        "action" : "$Nʹ��һ��"HIR"��ף�ڻ��桹"NOR"�������絶��бб����$n��$l",
        "skill_name" : "ף�ڻ���",
        "lvl" : 10
]),
([        "action" : "$Nʹ��һ��"HIR"������ޱߡ�"NOR"��˫��һ�ģ�һ�����������й���$n��$l",
        "skill_name" : "����ޱ�",
        "lvl" : 20
]),
([        "action" : "$Nʹ��һ��"RED"�������ֻء�"NOR"��˫�ֺ�ʮ����ͷ����$n",
        "skill_name" : "�����ֻ�",
        "lvl" : 30
]),
([        "action" : "$Nʹ��һ��"HIR"��˫�����桹"NOR"��˫��һ�������������湥��$n��$l",
        "skill_name" : "˫������",
        "lvl" : 40
]),
([        "action" : "$Nʹ��һ��"HIB"����ɽ�𺣡�"NOR"��˫������б�ģ���ʱ��ǧ������������˷�����$n",
        "skill_name" : "��ɽ��",
        "lvl" : 60
]),
([        "action" : "$Nʹ��һ��"RED"���׷��ȡ�"NOR"����ۻ��գ�����������ֱ��$n��$l",
        "skill_name" : "�׷���",
        "lvl" : 80
]),
([        "action" : "$Nʹ��һ��"RED"������������"NOR"��˫��΢��������ǰ�죬һ���ھ�����ɽ�����㹥��$n",
        "skill_name" : "��������",
        "lvl" : 100
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }
int valid_combine(string combo)
{
        return combo == "dashou-yin" ||
               combo == "yujiamu-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�����浶������֡�\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��\n");

        if (me->query_skill("strike", 1) < me->query_skill("huoyan-dao", 1))
                return notify_fail("��Ļ����Ʒ�������ޣ��޷���������Ļ��浶����\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�����浶������֡�\n");
        if( query("qi", me)<60 )
                return notify_fail("������������������˻��浶��\n");
        if( query("neili", me)<40 )
                return notify_fail("������������������˻��浶��\n");
        me->receive_damage("qi", 55);
        addn("neili", -35, me);
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
        int d_e1 = -55;
        int d_e2 = -35;
        int p_e1 = -15;
        int p_e2 = 15;
        int f_e1 = 310;
        int f_e2 = 460;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huoyan-dao", 1);
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
                "damage_type" : "����",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
void skill_improved(object me)
{
        int skill = me->query_skill("huoyan-dao", 1);
        if( skill == 200 && !query("sl_gift/huoyandao", me) )
        {
                tell_object(me, HIW"\n��Ȼ����е�������ϢԽתԽ�죬˲ʱ�书���Ѿ���������һ���µľ��磡\n"
                                "������������ˣ�\n��ĸ��������ˣ�\n" NOR);
                addn("max_neili", skill+random(skill), me);
                addn("con", 1, me);
                set("sl_gift/huoyandao", 1, me);
         }
}

string perform_action_file(string action)
{
        return __DIR__"huoyan-dao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        string msg;

        if (damage_bonus < 100) return 0;

        if (random(damage_bonus / 2) > victim->query_str()/10
         && query("neili", me)>query("neili", victim)*2/3 )
        {
                result = ([ "damage" : damage_bonus]);

                switch(random(3))
                {
                case 0:
                        msg = HIR"$n�ľ�����һ˿˿����Ļ𾢸����룬ȫ��ʹ���ޱȣ�\n"NOR;
                case 1:
                        msg = HIR"ֻ������������һ����$n���ϵĻ𾢱����ˣ�\n"NOR;
                case 2:
                        msg = HIR"$nֻ�ŵ�һ�����ս���ζ������ȫ��֪���Լ��Ѿ����յ���������ˣ�\n"NOR;
                }
                result += ([ "msg" : msg ]);
                return result;
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("huoyan-dao", 1) < 100 ||
            !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("huoyan-dao", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage / 2 ]);
                result += ([ "msg" : HIR "$nչ�����浶������ס��һЩ$N�Ĺ�����\n" NOR ]);
                return result;
       }
}

int help(object me)
{
        write(HIR"\n���浶��"NOR"\n");
        write(@HELP

    ���浶Ϊѩɽ������ס���Ħ�ǵĶ��ž�����
    ԭΪ������ʮ������֮һ�����Ħ�ǵ�Ľ�ݲ��������ÿ�����
���գ�������С���๦�������С�

        ѧϰҪ��
                С���๦60��
                ����800
HELP
        );
        return 1;
}
