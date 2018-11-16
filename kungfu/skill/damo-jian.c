// damo-jian.c ��Ħ��

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$Nʹһʽ"MAG"��������Ե����"NOR"������$w����΢�񣬻ó�һ���������$n��$l",
        "lvl" : 0,
        "skill_name" : "������Ե��"
]),
([        "action":"$N����ǰ��ʹ��"HIC"����ȥ�����С�"NOR"�������������ޣ�$w��������$n��$l��ȥ",
        "lvl" : 10,
        "skill_name" : "��ȥ������"
]),
([        "action":"$Nһʽ"YEL"��������ɣԶ��"NOR"������Ʈ�����ߣ��˷�����������$wңҡָ��$n��$l",
        "lvl" : 20,
        "skill_name" : "������ɣԶ"
]),
([        "action":"$N��������Ծ��һʽ"BLU"���ֻط����᡹"NOR"���������ּ�ת������ն��$n��$l",
        "lvl" : 30,
        "skill_name" : "�ֻط�����"
]),
([        "action":"$N����$w�й�ֱ����һʽ"HIW"��ˮ��ͨ���š�"NOR"��������Ϣ�ض�׼$n��$l�̳�һ��",
        "lvl" : 40,
        "skill_name" : "ˮ��ͨ����"
]),
([        "action":"$N����$wбָ���죬��â���£�һʽ"HIM"��������������"NOR"����׼$n��$lбб����",
        "lvl" : 50,
        "skill_name" : "����������"
]),
([        "action":"$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ"GRN "��ǧ��һέȥ��"NOR"����$n��$l",
        "lvl" : 60,
        "skill_name" : "ǧ��һέȥ"
]),
([        "action":"$N���Ƶ�����һʽ"HIG"�����Ķ�������"NOR"��$w�Ի���Ծ�����缲�������$n���ؿ�",
        "lvl" : 70,
        "skill_name" : "���Ķ�����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("damo-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ĵ�Ħ������\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<70 )
                return notify_fail("���������������Ħ����\n");

        if( query("neili", me)<70 )
                return notify_fail("���������������Ħ����\n");

        me->receive_damage("qi", 62);
        addn("neili", -69, me);
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
        int d_e1 = -30;
        int d_e2 = -50;
        int p_e1 = -20;
        int p_e2 = -40;
        int f_e1 = 200;
        int f_e2 = 350;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);
        int j, wt;
        object target;
        string *msg;

        wt=query_temp("sl_weituo", me);
        target = me->select_opponent();
        weapon=query_temp("weapon", me);

        msg = ({
                HIR"\n$N����Խ��Խ��������ͻ�죬���֮�䣬$n" +HIR"��ȫ�ǽ���������\n"NOR,
                HIY"\n$N���潣ת���ؽ����ӣ�һ������һ�������಻�����������������������ޱȡ�\n"NOR,
                HIC"\nԭ����Ħ���ߵľ��Ǹ���·�ӣ��˿�ȴ���������鶯֮�������Ƹ���������\n"NOR,
                HIW"\n��ʱ$N�Ľ���һ���Ƴ���Ȼ������Τ�ӷ�ħ�������ӵ������쾡�¡�\n"NOR,
        });

        if( wt>1 && wt<6 && !query_temp("weituo_attack", me)){

                message_combatd( msg[wt-2] , me, weapon);
                set_temp("weituo_attack", 1, me);
                for( j=0; j < wt-1; j++ )
                {
                        if (! me->is_fighting(target)) break;
                        addn("neili", -50, me);
                        COMBAT_D->do_attack(me, target, weapon);
                }
                delete_temp("weituo_attack", me);
                addn_temp("sl_weituo", 1, me);

        }
        lvl = (int) me->query_skill("damo-jian", 1);
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
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        int i;

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "damo-jian"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return 0;

        if( query_temp("damo-jian/lian", me) ||
            random(2) == 0 ||
            me->is_busy())
                return 0;

        message_combatd(HIY "\n$N" HIY "���潣ת���ؽ����ӣ�һ������һ�������಻����"
                        "�������������������ޱȡ�\n" NOR,
                        me, victim);

        addn("neili", -270, me);

        set_temp("damo-jian/lian", 1, me);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2) == 1)
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        delete_temp("damo-jian/lian", me);

}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point() { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"damo-jian/" + action;
}

int help(object me)
{
        write(HIC"\n��Ħ����"NOR"\n");
        write(@HELP

    ��Ħ��Ϊ������ʮ������֮һ��

        ѧϰҪ��
                ��Ԫһ����20��
                ����100
HELP
        );
        return 1;
}
