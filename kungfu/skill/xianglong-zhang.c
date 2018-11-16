// xianglong-zhang.c ����ʮ����
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N˫��ƽƽ�ᵽ��ǰ����ɫ���صĻ���ʩ��"+(order[random(13)])+"�������лڡ�"NOR"����$n��$l",
]),
([        "action" : "$NͻȻ���η���˫�ƾӸ�����һ��"+(order[random(13)])+"���������졹"NOR"����$n��$l",
]),
([        "action" : "$N����һ��"+(order[random(13)])+"���������"NOR"��Ѹ���ޱȵ�����$n��$l",
]),
([        "action" : "$N˫��ʩ��һ��"+(order[random(13)])+"���轥��½��"NOR"���������ŷ�������$n��$l",
]),
([        "action" : "$N���ƾ۳�ȭ״������һ��"+(order[random(13)])+"��Ǳ�����á�"NOR"��������$n��$l",
]),
([        "action" : "$Nʩ��һ��"+(order[random(13)])+"������󴨡�"NOR"�����Ʋ�������������$n��$l",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"��ͻ��������"NOR"�����ƴӲ����ܵĽǶ���$n��$l�Ƴ�",
]),
([        "action" : "$N���һ����˫��ʹ��"+(order[random(13)])+"���𾪰��"NOR"������һ�а����$n",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"����Ծ��Ԩ��"NOR"����$n��$l��������",
]),
([        "action" : "$N���λ�����˫��ʹһ��"+(order[random(13)])+"��˫��ȡˮ��"NOR"һǰһ����$n��$l",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"����Ծ��Ԩ��"NOR"�����η���˫�Ʋ���һ����$n��$l����",
]),
([        "action" : "$N˫������ʹ��"+(order[random(13)])+"��ʱ��������"NOR"��$n��������",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"�����Ʋ��꡹"NOR"�����Ʒ�ס$n����·������бб������$l",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"���������ڡ�"NOR"��˫�������������$n��$l",
]),
([        "action" : "$N����һת��ͻȻ�۵�$n��ǰ��һ��"+(order[random(13)])+"����ս��Ұ��"NOR"����$n��$l",
]),
([        "action" : "$N�Ż��󿪣�һ��"+(order[random(13)])+"����˪������"NOR"��$n��$l��ȥ",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"������ެ��"NOR"��˫���������ϻ���$n��$l",
]),
([        "action" : "$N���ƻ��أ�����ʹһ��"+(order[random(13)])+"��������β��"NOR"���»ζ��Ż���$n��$l",
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

string main_skill() { return "xianglong-zhang"; }

mapping sub_skills = ([
        "kanglong-youhui"  : 150,        // 1
        "feilong-zaitian"  : 150,        // 2
        "jianlong-zaitian" : 150,        // 3
        "hongjian-yulu"    : 150,        // 4
        "qianlong-wuyong"  : 150,        // 5
        "lishe-dachuan"    : 150,        // 6
        "turu-qilai"       : 150,        // 7
        "zhenjing-baili"   : 150,        // 8
        "huoyue-zaiyuan"   : 150,        // 9
        "shuanglong-qushui": 150,        // 10
        "yuyue-yuyuan"     : 150,        // 11
        "shicheng-liulong" : 150,        // 12
        "miyun-buyu"       : 150,        // 13
        "sunze-youfu"      : 150,        // 14
        "longzhan-yuye"    : 150,        // 15
        "lvshuang-bingzhi" : 150,        // 16
        "diyang-chufan"    : 150,        // 17
        "shenlong-baiwei"  : 150,        // 18
]);
int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        if( query("character", me) == "���ռ�թ" )
        {
                tell_object(me, "��������ϣ����ִ����Ʒ��ƺ����Լ����Ը�"
                                "���ϣ�����������\n");
                return 0;
        }

        if( query("gender", me) == "����" )
        {
                tell_object(me, "��������ϣ�ֻ���������������������˹�֮"
                                "�¼������ʡ�\n");
                return 0;
        }

        if( query("str", me)<36 )
        {
                tell_object(me, "��������ϣ�ֻ���ֱ���������ʹ�ü���̧"
                                "��������\n");
                return 0;
        }

        if( query("con", me)<32 )
        {
                tell_object(me, "��������ϣ��;�����ǰ������ð��̫��Ѩͻ"
                                "ͻ������\n");
                return 0;
        }

        if ((int)me->query_skill("force") < 300)
        {
                tell_object(me, "��������ϣ��������ѣ����������ڹ�ˮƽ��"
                                "�д���ߡ�\n");
                return 0;
        }

        if( query("max_neili", me)<3000 )
        {
                tell_object(me, "��������ϣ������᲻��������������Ӧ��"
                                "��������������\n");
                return 0;
        }

        if (random(30) <= 28)
        {
                tell_object(me, "���ʮ���Ƶİ����������򣬻�������������"
                                "�����ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIY "��һ���ǳɣ���ʮ���ƴ�ͷ��β������һ�䣬����"
                        "����ͨ\n���˽���ʮ���Ƶİ���裬�ڻ��ͨ����"
                        "���ľ�΢֮����\n��Ҳ�ǲ�ʹ����ô��ô�򵥡�\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
int valid_learn(object me)
{
        if( query("character", me) == "���ռ�թ" )
                return notify_fail("�����а��룺���书�����ý���ѧ��������\n");

        if( query("str", me)<36 )
                return notify_fail("�����������������������������ʮ���ơ�\n");

        if( query("con", me)<32 )
                return notify_fail("����������������������������ʮ���ơ�\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹���������������ʮ���ơ�\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("���������Ϊ���㣬������������ʮ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("��Ļ����Ʒ���򲻹���������������ʮ���ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xianglong-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ�������������Ľ���ʮ���ơ�\n");

        return 1;
}
int practice_skill(object me)
{
        if (!valid_learn(me)) return 0;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<40 )
                return notify_fail("�����������������ʮ���ơ�\n");
        me->receive_damage("qi", 100);
        addn("neili", -40, me);
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
        int d_e2 = -40;
        int p_e1 = -20;
        int p_e2 = 10;
        int f_e1 = 520;
        int f_e2 = 640;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xianglong-zhang", 1);
        seq = random(ttl);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("xianglong-zhang", 1);

        if (damage_bonus < 100 || lvl < 150) return 0;

        if (damage_bonus > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);

                return random(2) ? HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                                   "�߹Ƕ��۵�������\n" NOR:

                                   HIR "$n" HIR "һ���ҽУ���ǰ���������꡹������"
                                   "�죬������Ѫ���硣\n" NOR;
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("huntian-qigong",1) >= 10)        return 0.8;
        else return 1.0;
}

string perform_action_file(string action)
{
        return __DIR__"xianglong-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n����ʮ���ƣ�"NOR"\n");
        write(@HELP

    ����ʮ������ؤ�����֮��������������͵��书��

        ѧϰҪ��
                ������������ʮ��·�Ʒ��϶�Ϊһ
                ����3000
                �������25
                �������20
                �����Ʒ�180
                �����Ʒ������ڽ�����
HELP
        );
        return 1;
}
