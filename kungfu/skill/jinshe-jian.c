// jinshe-jian.c ���߽���
// Last Modified by sega on Mar. 10 2000
// �����ý��߽�ʱ����damage����,

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "skill_name" : "�����Ӱ",
        "action"     : "$Nʹһ��"HIY"�������Ӱ��"NOR"�����е�$w��һ��ָ������$n��$l��������",
        "lvl"        : 0
]),
([      "skill_name" : "��Ӱ���",
        "action"     : "$Nʹһ��"HIY"����Ӱ�����"NOR"������$w�����������$n��$l��������",
        "lvl"        : 10
]),
([      "skill_name" : "ѩ�ط���",
        "action"     : "$N����һת����������Ծ������$w�鶯زԾ��һ��"HIY"��ѩ�ط��ߡ�"NOR"����$n��$l",
        "lvl"        : 20
]),
([      "skill_name" : "��������",
        "action"     : "$N����һת��һ��"HIY"���������š�"NOR"�����е�$w����������$n��$l���˹�ȥ",
        "lvl"        : 30
]),
([      "skill_name" : "���߿���",
        "action"     : "$N����һ����һ��"HIY"�����߿��衹"NOR"��$wЮ���������⣬����޷�����$n��$l",
        "lvl"        : 40
]),
([      "skill_name" : "���ߵ���",
        "action"     : "$N������������񴦣�һ��"HIY"�����ߵ�����"NOR"��$w���޷����ݵ��ٶ�ֱ��$n��$l",
        "lvl"        : 50
]),
([      "skill_name" : "�������",
        "action"     : "$N����һ����һ��"HIY"��������ǡ�"NOR"�����е�$w�������ϴ���$n��$l",
        "lvl" : 60
]),
([      "skill_name" : "���߻���",
        "action"     : "$N����$w���Ⱪ����һ��"HIY"�����߻�����"NOR"����ǧ����Ы��$n$lҧȥ",
        "lvl"        : 70
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{

        if( query("dex", me)<28 )
                return notify_fail("���о��˰��죬ֻ��������Щ�ʼ���޷�������е����С�\n");

        if( query("str", me)<28 )
                return notify_fail("���о��˰��죬�о�������Щ�ͣ�ʼ���޷�����ʩչ��\n");

        if( query("max_neili", me)<500 )
                return notify_fail("���������Ϊ������û�а취�����߽�����\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹���û�а취�����߽�����\n");

        if ((int)me->query_skill("dodge", 1) < 140)
                return notify_fail("��Ļ����Ṧ��򲻹���û�а취�����߽�����\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("��Ļ���������򲻹���û�а취�����߽�����\n");

        if ((int)me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("�����ѧ�������㣬û�а취������߽�����\n");

        if( query("character", me) == "�ĺ�����" )
                return notify_fail("��һ����ɱ�����ˣ�û�������߽�����\n");

        if( query("character", me) == "���ռ�թ" )
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û�������߽�����\n");

        if( query("character", me) == "��������" )
                return notify_fail("�����а�����ʲô���߽��������߰���ģ�û�а�����ơ�\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshe-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ��߽�����\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me)) || 
            query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

        if( query("qi", me)<80 )
                return notify_fail("�����������û�а취��ϰ���߽�����\n");

        if( query("neili", me)<80 )
                return notify_fail("�������������û�а취��ϰ���߽�����\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinshe-jian", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int effective_level() { return 25;}

string *parry_msg = ({
        "$n���е�$W����ǧ�ٰѣ���ס��ȫ��\n",
        "$n���е�$W�������£�������$N��$w�������Ρ�\n",
        "$nʹ��$W������ǰ������һ��ͭǽ���ڣ���ס��$N�Ĺ��ơ�\n",
        "$n��$W������һ�̣�$W�����������պ�ֱ��$N��˫�ۡ�\n",
        "$n�ٽ�������һ�������ӽ���͸�����ƿ���$N��\n",
        "$nһ�����е�$W����ס��ȫ��\n",
});

string *unarmed_parry_msg = ({
        "$n�������أ���ס��$N��$w��\n",
        "$n���˷������������죬�ݺݿĿ���$N��$w��\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"jinshe-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i, ap, dp;

        lvl = me->query_skill("jinshe-jian", 1);

        if( query("neili", me)<300
           || me->query_skill_mapped("sword") != "jinshe-jian"
            || !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                     return 0;

        ap = me->query_skill("sword");
        dp = victim->query_skill("dodge");

        addn("neili", -80, me);

        switch(random(5))
        {
           case 1:
             break;

           case 2:
             break;

          case 3:
             break;

          case 4:
             if (ap / 2 + random(ap) > dp &&
                 ! me->is_busy() &&
                 ! victim->is_busy())
             {
                 message_sort(HIW "\n$N" HIW "����һת������" + weapon->name() + HIW
                              "�������߰���趯�ţ�����$n" HIW "������ơ�\n" NOR);
                 me->start_busy(1);
                 victim->start_busy(1 + random(lvl / 20));
             }
             break;

          default :
             if (ap * 3 / 5 + random(ap) > dp &&
                 ! me->is_busy() &&
                 !query_temp("jinshe-jian/lian", me) )
             {
                weapon=query_temp("weapon", me);
                message_sort(HIY "\n$N" HIY "һ������������" + weapon->name() + HIY
                             "��ʱ����һ�����ߣ�Ѹ���ޱȵ�Ϯ��$n" HIY "��\n" NOR,
                             me, victim);

                addn("neili", -180, me);

                set_temp("jinshe-jian/lian", 1, me);
                for (i = 0; i < 9; i++)
                {
                    if (! me->is_fighting(victim))
                            break;

                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                }
                delete_temp("jinshe-jian/lian", me);

             }
             break;
       }
}
int help(object me)
{
        write(HIC"\n���߽�����"NOR"\n");
        write(@HELP

    ���߽������ڡ��������š����˽����ɾ���ѩ�˵Ķ����书��
��ѩ����ʱȫ�Ҳ��ұ��¼����Ͻ������ţ���־���𡣺����置��
ʶ�嶾�̽���֮�úκ�ҩ��������������嶾�̵ġ�������������
�߽�������׶���ر�ͼ��������ɾ����书��
    ��ѩ������Ź֣�Ϊ�����ݣ��书���������˰�����Ѳ⡣��
����������������Ϊ֮ɫ�䣬���ǳ������Ѳ������ѩ�����µ�
���������š�������һ���书�������߽���������׶���ͽ�������
�ơ�

        ѧϰҪ��
                ����500
HELP
        );
        return 1;
}
