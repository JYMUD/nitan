// Cuff��  ��ȭ������ȭ��̫�泤ȭ������ȭ�����ֳ�ȭ���˼�ȭ
// Claw��  �������֡�С�����֡�ӥצ������צ��
// Strike�������ơ��䵱���ơ����������

#include <ansi.h>
inherit SKILL;

string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N������̧��һ�в�ȭ�ġ������ڡ�����׼$n��$l�ͻ���ȥ",
        "force" : 420,
        "attack": 130,
        "dodge" : 45,
        "parry" : 45,
        "damage": 80,
        "damage_type":  "����"
]),
([      "action": "$Nһ������ȭ�ġ��׺����᡹������������ת�ɹ��������������ɹ��֣���\n"
                  "��һ�����죬����$n$l",
        "force" : 512,
        "attack": 145,
        "dodge" : 10,
        "parry" : 75,
        "damage": 85,
        "damage_type":  "����"
]),
([      "action": "$N����һ�ݣ�ʩչС�����ֵ��ַ���˫�ֶ���$n$l���Ĺؽ�ֱֱץȥ",
        "force" : 410,
        "attack": 170,
        "dodge" : 35,
        "parry" : 35,
        "damage": 178,
        "damage_type":  "ץ��"
]),
([      "action": "$N��ȭ��������ȭת�ۻ��ţ�һ�����ֵ����ֳ�ȭͻȻ���������������������$n",
        "force" : 460,
        "attack": 150,
        "dodge" : 62,
        "parry" : 60,
        "damage": 90,
        "lvl"   : 30,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N����������ʹ���˼�ȭ�еġ��˼�����ʽ����˫�ƶ���$n��$lƽƽ��ȥ",
        "force" : 480,
        "attack": 160,
        "dodge" : 40,
        "parry" : 40,
        "damage": 85,
        "damage_type":  "����"
]),
([      "action": "$N���һ����������$n���һ����������$n���ֻ�ȥ�����ǰ����Ƶ���ʽ",
        "force" : 510,
        "attack": 155,
        "dodge" : 30,
        "parry" : 30,
        "damage": 95,
        "damage_type":  "����"
]),
([      "action": "$N�������ߣ����ֻ��أ�����һ����������Ƶġ��ο�̽צ����Ѹ������$n$l",
        "force" : 510,
        "attack": 150,
        "dodge" : 45,
        "parry" : 45,
        "damage": 110,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N������ʽ��˫�ֽ��䵱�ɵ�����ʹ���ܲ�͸�磬���в���$n��$l",
        "force" : 460,
        "attack": 155,
        "dodge" : 160,
        "parry" : 160,
        "damage": 105,
        "damage_type":  "����"
]),
([      "action": "$NͻȻ����һԾ����˫������צ״������$n��$l��Ȼץȥ����Ȼ��ӥצ������ʽ",
        "force" : 470,
        "attack": 185,
        "dodge" : 60,
        "parry" : 60,
        "damage": 155,
        "damage_type":  "ץ��"
]),
([      "action": "ֻ��$N����һ����˫�ַ������ϱ�ΪȦ��һ��̫��ȭ�����֡�ֱ��$n��$l",
        "force" : 350,
        "attack": 90,
        "dodge" : 210,
        "parry" : 230,
        "damage": 65,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N��ǰһ��������һ�Ǵ������ֻ�ס���̣�����˳��һ����ʩһ��ˤ���ֻ���$n",
        "force" : 520,
        "attack": 155,
        "dodge" : 41,
        "parry" : 37,
        "damage": 103,
        "damage_type":  "����"
]),
([      "action": "$Nһ��ת����$n���������ֽ�$n���α�ס�͵ĳ�����ˤȥ����Ȼ���ɹŵ�ˤ����ʽ",
        "force" : 560,
        "attack": 185,
        "dodge" : 75,
        "parry" : 60,
        "damage": 125,
        "damage_type":  "ˤ��"
]),
});

string main_skill() { return "baihua-cuoquan"; }

mapping sub_skills = ([
                "cha-quan"      : 100,          // ��ȭ
                "baji-quan"     : 100,          // �˼�ȭ
                "changquan"     : 100,          // ̫�泤ȭ
                "liuhe-quan"    : 100,          // ����ȭ��
                "yanqing-quan"  : 100,          // ����ȭ
                "shaolin-quan"  : 100,          // ���ֳ�ȭ
                "bagua-zhang"   : 100,          // ������
                "bazhen-zhang"  : 100,          // ���������
                "wudang-zhang"  : 100,          // �䵱����
                "huzhao-shou"   : 100,          // ��צ��
                "yingzhao-shou" : 100,          // ӥצ��
                "xiao-qinna"    : 100,          // С������
                "da-qinna"      : 100,          // ��������
        ]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("int", me)<28 )
        {
                tell_object(me, "��������ϣ����ø���ȭ������ǣ���������������"
                                "�ԣ��޷���ͨ�ٻ���ȭ��\n");
                return 0;
        }

        if( query("dex", me)<23 )
        {
                tell_object(me, "��������ϣ�ֻ���Լ������鶯��̫��޷���ͨ"
                                "�ٻ���ȭ��\n");
                return 0;
        }

        if ((int)me->query_skill("unarmed", 1) < 150)
        {
                tell_object(me, "������Լ���ȭ�Ź����д���ߣ������޷���ͨ��"
                                "����ȭ��\n");
                return 0;
        }

        if (me->query_skill("force") < 250)
        {
                tell_object(me, "������Լ��ڹ������ǳ���޷���ͨ�ٻ���ȭ��\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 80)
        {
                tell_object(me, "������Լ���ѧ����̫�ͣ��޷���ͨ�ٻ���ȭ��\n");
                return 0;
        }

        if( query("max_neili", me)<3000 )
        {
                tell_object(me, "������Լ��������̣��޷���ͨ�ٻ���ȭ��\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIY "��һ���ǳɣ������Ҹ��ɵ���ʮ��ȭ������ʩչ������һ"
                            "Ƭ��ͻȻ�����ж���ͨ���˰ٻ���ȭ�İ�\n��裬��"
                            "���ͨ����ȭ���еľ�΢֮������ټ�֮�����������װ�"
                            "����ȭ��\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("���ٻ���ȭ������֡�\n");

        if( query("int", me)<28 )
                return notify_fail("�����������̫��޷�ѧϰ�ٻ���ȭ��\n");

        if( query("dex", me)<23 )
                return notify_fail("����������������޷�ѧϰ�ٻ���ȭ��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������ΪԶԶ���㣬������ϰ�ٻ���ȭ��\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ������ǳ���޷�ѧϰ�ٻ���ȭ��\n");

        if ((int)me->query_skill("unarmed", 1) < 150)
                return notify_fail("���ȭ�Ÿ������ޣ��޷����ٻ���ȭҪ�衣\n");

        if ((int)me->query_skill("cuff", 1) < 100)
                return notify_fail("���ȭ���������ޣ��޷����ٻ���ȭҪ�衣\n");

        if ((int)me->query_skill("claw", 1) < 100)
                return notify_fail("���צ���������ޣ��޷����ٻ���ȭҪ�衣\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("����Ʒ��������ޣ��޷����ٻ���ȭҪ�衣\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("baihua-cuoquan", 1))
                return notify_fail("���ȭ�Ÿ�������㣬�޷���������İٻ���ȭ��\n");

        return 1;
}

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="benlei-shou"; }

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
        int d_e1 = 25;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -15;
        int f_e1 = 130;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("baihua-cuoquan", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.0; }

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("����������������Ϣһ�������ɡ�\n");

        if( query("neili", me)<150 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("qi", 80);
        addn("neili", -120, me);

        return 1;
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
        int lvl;
        mixed result;

        lvl = me->query_skill("baihua-cuoquan", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                                     "�߹Ƕ��۵�������\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"baihua-cuoquan/" + action;
}

int help(object me)
{
        write(HIM"\n�ٻ���ȭ��"NOR"\n");
        write(@HELP

    �ٻ���ȭ����ع���Ԭʿ��������Ԭʿ��ʹ�ڵ����������Ե��
������������������ȭ����ȭȡ�ڼ�֮�����������Ƕ��ǣ��յ�
��찣��ʳƴ�ȭ��
    �컨���ܶ����¼���ΪԬʿ�����ҵ��ӣ��ô���ȭ��

        ѧϰҪ��
                �컨��20��
                ������Ϊ100
HELP
        );
        return 1;
}