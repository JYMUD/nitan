// dragon-strike.c ����ʮ����

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string main_skill() { return "yinyang-shiertian"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N˫��ƽƽ�ᵽ��ǰ����ɫ���صĻ���ʩ��"+(order[random(13)])+"�������лڡ�"NOR"����$n��$l",
          "lvl"        : 10,
          "skill_name" : "�����л�",
]),
([        "action" : "$NͻȻ���η���˫�ƾӸ�����һ��"+(order[random(13)])+"���������졹"NOR"����$n��$l",
          "lvl"        : 20,
          "skill_name" : "��������",
]),
([        "action" : "$N����һ��"+(order[random(13)])+"���������"NOR"��Ѹ���ޱȵ�����$n��$l",
          "lvl"        : 30,
          "skill_name" : "��������",
]),
([        "action" : "$N˫��ʩ��һ��"+(order[random(13)])+"���轥��½��"NOR"���������ŷ�������$n��$l",
          "lvl"        : 40,
          "skill_name" : "�轥��½",
]),
([        "action" : "$N���ƾ۳�ȭ״������һ��"+(order[random(13)])+"��Ǳ�����á�"NOR"��������$n��$l",
          "lvl"        : 50,
          "skill_name" : "Ǳ������",
]),
([        "action" : "$Nʩ��һ��"+(order[random(13)])+"������󴨡�"NOR"�����Ʋ�������������$n��$l",
          "lvl"        : 60,
          "skill_name" : "�����",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"��ͻ��������"NOR"�����ƴӲ����ܵĽǶ���$n��$l�Ƴ�",
          "lvl"        : 70,
          "skill_name" : "ͻ������",
]),
([        "action" : "$N���һ����˫��ʹ��"+(order[random(13)])+"���𾪰��"NOR"������һ�а����$n",
          "lvl"        : 80,
          "skill_name" : "�𾪰���",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"����Ծ��Ԩ��"NOR"����$n��$l��������",
          "lvl"        : 90,
          "skill_name" : "��Ծ��Ԩ",
]),
([        "action" : "$N���λ�����˫��ʹһ��"+(order[random(13)])+"��˫��ȡˮ��"NOR"һǰһ����$n��$l",
          "lvl"        : 100,
          "skill_name" : "˫��ȡˮ",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"����Ծ��Ԩ��"NOR"�����η���˫�Ʋ���һ����$n��$l����",
          "lvl"        : 110,
          "skill_name" : "��Ծ��Ԩ",
]),
([        "action" : "$N˫������ʹ��"+(order[random(13)])+"��ʱ��������"NOR"��$n��������",
          "lvl"        : 120,
          "skill_name" : "ʱ������",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"�����Ʋ��꡹"NOR"�����Ʒ�ס$n����·������бб������$l",
          "lvl"        : 130,
          "skill_name" : "���Ʋ���",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"���������ڡ�"NOR"��˫�������������$n��$l",
          "lvl"        : 140,
          "skill_name" : "��������",
]),
([        "action" : "$N����һת��ͻȻ�۵�$n��ǰ��һ��"+(order[random(13)])+"����ս��Ұ��"NOR"����$n��$l",
          "lvl"        : 150,
          "skill_name" : "��ս��Ұ",
]),
([        "action" : "$N�Ż��󿪣�һ��"+(order[random(13)])+"����˪������"NOR"��$n��$l��ȥ",
          "lvl"        : 160,
          "skill_name" : "��˪����",
]),
([        "action" : "$Nʹ��"+(order[random(13)])+"������ެ��"NOR"��˫���������ϻ���$n��$l",
          "lvl"        : 170,
          "skill_name" : "����ެ",
]),
([        "action" : "$N���ƻ��أ�����ʹһ��"+(order[random(13)])+"��������β��"NOR"���»ζ��Ż���$n��$l",
          "lvl"        : 180,
          "skill_name" : "������β",
]),
});

// string main_skill() { return "dragon-strike"; }

mapping sub_skills = ([
       "kanglong-youhui"  : 80,        // 1
       "feilong-zaitian"  : 80,        // 2
       "jianlong-zaitian" : 80,        // 3
       "hongjian-yulu"    : 80,        // 4
       "qianlong-wuyong"  : 80,        // 5
       "lishe-dachuan"    : 80,        // 6
       "turu-qilai"       : 80,        // 7
       "zhenjing-baili"   : 80,        // 8
       "huoyue-zaiyuan"   : 80,        // 9
       "shuanglong-qushui": 80,        // 10
       "yuyue-yuyuan"     : 80,        // 11
       "shicheng-liulong" : 80,        // 12
       "miyun-buyu"       : 80,        // 13
       "sunze-youfu"      : 80,        // 14
       "longzhan-yuye"    : 80,        // 15
       "lvshuang-bingzhi" : 80,        // 16
       "diyang-chufan"    : 80,        // 17
       "shenlong-baiwei"  : 80,        // 18
]);

int get_ready(object me)
{
       return 1;
}

int get_finish(object me)
{
       if( query("str", me)<31 || me->query_str()<45 )
       {
               tell_object(me, "��������ϣ��ֱ�������������̧��������\n");
               return 0;
       }

       if( query("con", me)<24 || me->query_con()<37 )
       {
               tell_object(me, "��������ϣ��;�����ǰ������ð��̫��Ѩͻͻ������\n");
               return 0;
       }

       if ((int)me->query_skill("force") < 150)
       {
               tell_object(me, "��������ϣ��������ѣ��Լ����ڹ�ˮƽ�������д���ߡ�\n");
               return 0;
       }

       if( query("max_neili", me)<1500 )
       {
               tell_object(me, "��������ϣ������᲻��������������Ӧ�ü�������������\n");
               return 0;
       }

       if (random(10) < 5)
       {
               tell_object(me, "���ʮ���Ƶİ����������򣬻���������һ�ξ��ܹ��ڻ��ͨ��\n");
               return 0;
       }

       tell_object(me, HIY "��һ���ǳɣ���ʮ���ƴ�ͷ��β������һ�䣬���ж���ͨ\n"
                           "���˽���ʮ���Ƶİ���裬�ڻ��ͨ���Ʒ��ľ�΢֮����\n"
                           "��Ҳ�ǲ�ʹ����ô��ô�򵥡�\n" NOR);
       return 1;
}

mapping query_sub_skills()
{
       return sub_skills;
}

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
       if( query("str", me)<31 )
               return notify_fail("���������ӹǻ�������ʮ���ƣ�С��Ū���˸첲��\n");

       if( query("con", me)<24 )
               return notify_fail("���˰ɣ���������ǲ��ã���ǿѧ�ˡ�\n");

       if ((int)me->query_skill("force") < 150)
               return notify_fail("����ڹ���򲻹����޷�ѧϰ����ʮ���ơ�\n");

       if( query("max_neili", me)<1500 )
               return notify_fail("���������ô������ڻ��ͨ����ʮ���ƣ�\n");

       if ((int)me->query_skill("strike", 1) < 30)
               return notify_fail("��Ļ����Ʒ���򲻹����޷�ѧϰ����ʮ���ơ�\n");

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1))
               return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n");

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
        mapping a_action;
        int level, tmp;
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -20;
        int p_e2 = 10;
        int f_e1 = 520;
        int f_e2 = 640;
        int i, seq, ttl = sizeof(action);

        level = (int)me->query_skill("dragon-strike", 1);
        if( query_temp("xlz/hanglong", me) )
        {
                tmp = 4 + random(15);
                delete_temp("xlz/hanglong", me);
                return ([
                        "action": HIY "\n$N�е��������У�������΢�������ƻ��˸�ԲȦ��ƽ�Ƴ�ȥ�����ǽ���ʮ�����еġ������лڡ���\n" +
                                  "���Ƴ�ȥ�������赭д����һ��������ɲʱ֮������" + chinese_number(tmp) + "���ᾢ��һ��ǿ��һ����\n" +
                                  "���ص�����ֱ���޼᲻�ݣ���ǿ���ƣ�" NOR,
                        "dodge" : -140,
                        "parry" : -140,
                        "attack": 200,
                        "force" : 500 + 40 * tmp,
                        "damage": 100 + 20 * tmp,
                        "damage_type": random(2)?"����":"����"
                ]);
        }

        seq = random(ttl);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

// int double_attack() { return 1; }

int practice_skill(object me)
{
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ʮ���Ʊ�����֡�\n");

        if( query("qi", me)<110 )
                return notify_fail("�������̫���ˡ�\n");

        // cost = me->query_skill("dragon-strike", 1) / 5 + 90;
        if( query("neili", me)<110 )
                return notify_fail("�����������������ʮ���ơ�\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        string msg;
        int lvl;

        lvl = me->query_skill("dragon-strike", 1);

        if (damage < 50 || lvl < 150) return;

        if (random(10) < 2)
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIY "$N" HIY "һ�Ƽȳ���������ǰ������һ�С������лڡ���"
                                     "������ǰ�ƣ�˫����������һ����ɽ������ѹ��������\n"
                                     HIR "$n" HIR "�������������Ե�����������ʱ�����ش����۵�һ�����³�һ����Ѫ��\n"
                                     NOR ]);
        }
        else
        {
                victim->receive_wound("qi", damage, me);
                msg = random(2) ? HIR "$n" HIR "һ���ҽУ���ǰ���������꡹������"
                                  "�죬������Ѫ���硣\n" NOR :
                                  HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                                  "�߹Ƕ��۵�������\n" NOR;
                result = ([ "msg" : msg ]);
        }

        return result;
}

string perform_action_file(string action)
{
/*
        object me = this_player();

        if( me->query_family() != "ؤ��" && query("reborn/family_name", me) != "ؤ��" )
                return 0;
*/

        return __DIR__"dragon-strike/" + action;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
               me->delete_skill(sub_skillnames);
}

/*
// Let parry skill take its special effort.
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("dragon-strike", 1)) < 100 ||
            !living(query_temp("weapon", me) || objectp(me)) )
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) * 2 / 3 +
             me->query_skill("dragon-strike", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "��������һ�С�������β�������ֻ���һ�ơ�\n"
                                    "$N" HIC "�����������׺ݣ�����Ӳ�ӣ�����ܿ���\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "ֻ��$n" HIC "����Բ��������ֱ�ƣ�ʹ�С����������������ǰ��\n"
                                    "��һ�д��Ƿ�����ȴ����˫��֮�䲼��һ����ڡ�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "���²��ҵ�����˫�Ʒ��裬���Լ�ȫ������������֮�¡�\n"
                                    "��һ�ص���������Ԩͣ���ţ�ֱ�ް��������\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("dragon-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("huntian-qigong",1) >= 10)        return 0.8;
        else return 1.0;
}

// ���ܵ�ʽ���
string query_description()
{
        return
        "����ʮ��������ֱǰ�������������������������񽣣���Ȼ"
        "�ۺ������������������о��롣���ڽ���ʮ���Ƶ�"
        "��λ�����������飬�����������������µĹ���λ�ġ�"
        "��Ȼѧϰ����Ҫ�Һ��߹�������ʮ��������ؤ��ר���书��"
        "�������ɵ����ﲻ��ѧϰ��ؤ��ѧϰ��������������ӻ�"
        "Ů���ܹ��õó������Ľл��������߹��ԣ����������Ϳ���"
        "�������ˡ��м����ط�����ѧϰ���ա����������û�� 31"
        " ������������� 24 ���������ǣ���ʡʡ���ɲ��������ˡ�"
        "����ʮ����Ҫ�Ƚ�ʮ����ѧ�뵽 80 ����Ȼ��ͨ��������"
        "�ɽ���ʮ���ơ�";
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
