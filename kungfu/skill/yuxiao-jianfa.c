// This program is a part of NITAN MudLIB
// yuxiao-jianfa.c ��������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
        "�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
        "����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
});

string *parry_msg = ({
        "ȴ��$n����΢ת�����赭д����$w���ᵲ�����ڴ�δ����ߣ�������δ��Ƭ��ͣ�͡�\n",
});

string query_parry_msg(object weapon, object me)
{
        if( !me ) me = this_player();

        if (! objectp(weapon)
         || !query_temp("exercise/playing", me) )
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return parry_msg[random(sizeof(parry_msg))];
}

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action" : "$N����������һ��"+(order[random(13)])+"��Ӣ�������Ҷ��С�"NOR"��ƮȻ����$n��ǰ���漴����$w΢�𣬽��⼲����$n��$l",
        "lvl" : 0,
        "skill_name": "Ӣ�������Ҷ���"
]),
([        "action" : "$Nб��һ����ʹ��һʽ"+(order[random(13)])+"����Ů�鳤ֻ�޶̡�"NOR"���ӽ��������һ��һ�̵Ĺ�Ӱֱ��$n��$l",
        "lvl" : 10,
        "skill_name" : "��Ů�鳤ֻ�޶�"
]),
([        "action" : "$Nһ��"+(order[random(13)])+"����Ȼ��ȥ��˼�项"NOR"��$w��Ȼ���������̻ص������У��漴ת����Ȼ��ȥ��$n��ʱ�Ÿо�����һ�ɾ��������Լ���$l",
        "lvl" : 20,
        "skill_name": "��Ȼ��ȥ��˼��"
]),
([        "action" : "$N˫�־ٽ����죬һ��"+(order[random(13)])+"������Ⱥ�������塹"NOR"��$w���������ף����϶�����$n��ͷ­��ȥ",
        "lvl" : 30,
        "skill_name": "����Ⱥ��������"
]),
([        "action" : "$Nʩչ��"+(order[random(13)])+"�����һЦ������"NOR"������$w���΢΢һЦ��$nֻ����һ����ȴ��һ����Ӱ�������ΰ�Ϯ���Լ���$l�����Լ�ȴû����$N��ʱ������",
        "lvl" : 40,
        "skill_name" : "���һЦ������"
]),
([        "action" : "$N���̤ʵ���ҽ���㣬һ��"+(order[random(13)])+"��һ����ϳ�᡹"NOR"��$w����һ�Ž�����Ʈ�������ر���$n��$l",
        "lvl" : 50,
        "skill_name": "һ����ϳ��"
]),
([        "action" : "$Nһ��"+(order[random(13)])+"������Ū������项"NOR"�������ḧ$w���漴�͵�һ����������ǰһ�ݣ�ֻ��һ����˸�����Ľ�ӰѸ�ٴ���$n��$l",
        "lvl" : 60,
        "skill_name" : "����Ū�������"
]),
([        "action" : "$N������ף���ɫ��Ȼ��һ��"+(order[random(13)])+"��������Թ���˳���"NOR"��$w�������Ʋ����ش���$n��$l",
        "lvl" : 70,
        "skill_name" : "������Թ���˳�"
]),
([        "action" : "$N�������棬һ��"+(order[random(13)])+"���˽�������������"NOR"������$wб���»�����$n΢����֣������ɼ䣬ȴ��$N���е�$w�ѷ������ϣ�ֱ���Լ����ʺ�",
        "lvl" : 80,
        "skill_name": "�˽�����������"
]),
([        "action" : "$N��Ȼ��¶΢Ц��һ��"+(order[random(13)])+"����������Ц���ա�"NOR"������$wһ����������Ž�������$n����������·",
        "lvl" : 90,
        "skill_name" : "��������Ц����"
]),
([        "action" : "$N����ʳָ����$w��һ��"+(order[random(13)])+"���������������项"NOR"��$w����һ���������������ƣ�$nֻ������ǰһ�ƣ�һ����͵ľ��������Լ�",
        "lvl" : 100,
        "skill_name" : "��������������"
]),
([        "action" : "$N����΢��һ��"+(order[random(13)])+"��������������ϡ�"NOR"������$w����������һ����������ĺ�����ɲ�Ǽ��ɳ��ʯ��$n����һ�Ž���������£�������֧����",
        "lvl" : 110,
        "skill_name" : "�������������"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ�������޷�ѧϰ����������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�ѧϰ����������\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ���������򲻹����޷�ѧϰ����������\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuxiao-jianfa", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

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
        int d_e1 = -40;
        int d_e2 = -30;
        int p_e1 = -50;
        int p_e2 = -30;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 190;
        int m_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yuxiao-jianfa", 1);
        if (random(lvl) > 200 &&
            me->query_skill("force", 1) > 100 &&
            query("neili", me)>200 )
        {
                return ([
                        "action": HIC "$w" NOR + HIC "�ϵĽ�â�����Ƴ��߰���������......\n\n"
                                  HIG"$N����������һ�����������ӵ�����Ĵ��˰��Ȧ�ӣ�����$w"NOR+HIG"һͦ����ؽ�âͻʢ����â����$n$l��"NOR,
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                        "force" : 400,
                        "damage": 400,
                        "damage_type":  "����"
                ]);
        }
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

int practice_skill(object me)
{
        object weapon;

        if( !(weapon=query_temp("weapon", me)) )
                return notify_fail("����ʱ�޷������｣����\n");
        if( query("skill_type", weapon) != "sword" && query("skill_type", weapon) != "xsword" )
                return notify_fail("��ʹ�õ��������ԣ��޷������｣����\n");
        if( query("qi", me)<80 )
                return notify_fail("����������������｣����\n");

        if( query("neili", me)<80 )
                return notify_fail("����������������｣����\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"yuxiao-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        string name;
        object weapon;
        name = xue_name[random(sizeof(xue_name))];

        if( damage < 50 ) return 0;

        /*
        if( !objectp(weapon=query_temp("weapon", me) )
         || (query("id", weapon) != "yu xiao" &&
            query("id", weapon) != "xiao") )
                return;
        */
        result = ([ "damage" : damage ]);

        if (random(2) != 1)
                result += ([ "msg" : HIR "$n�������ߴ���һ������������ʱѪ��������һ���������Ķ�����\n" NOR]);
        else
                result += ([ "msg" : HIB "$n��$N����������һ����������������" RED + name + NOR +
                                     HIB "����ʱ������ת��ʹ����֣�\n" NOR]);
        return result;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yuxiao-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n���｣����"NOR"\n");
        write(@HELP

    ���｣���Ƕ����һ�������ҩʦ�Ĳ���֮�ܡ�
    ���һ��������ڡ�����ͤ�����ԣ�����һ�����������һ�Ӱ��
���񽣣��̺��������������Ȼ��ҩʦ��ƽ��������书����Ӣ
��֮��������｣���ˡ�

        ѧϰҪ��
                �̲���100��
                ����500
                ��Ե
HELP
        );
        return 1;
}
