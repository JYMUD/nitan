//jiuyin-baiguzhao.c �����׹�צ

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N��צ��Σ���צ������һ�С�������ǡ�ֱ����$n��$l",
        "force" : 250,
        "attack": 45,
        "dodge" : 10,
        "parry" : 18,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "�������" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N˫��������צ��צצ����$n������������������$n��$lץ��",
        "force" : 270,
        "attack": 50,
        "dodge" : 20,
        "parry" : 26,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "��������" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N˫��ʹ����ʮָ���ġ������в���$n��$l",
        "force" : 300,
        "attack": 60,
        "dodge" : 20,
        "parry" : 32,
        "damage": 45,
        "lvl"   : 70,
        "skill_name"  : "��������" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N����Χ$nһת��ʹ�������޵�������$n��$l����ȫ������צӰ��",
        "force" : 340,
        "attack": 85,
        "dodge" : 30,
        "parry" : 55,
        "damage": 55,
        "lvl"   : 100,
        "skill_name" : "���޵���" ,
        "damage_type" : "ץ��"
]),
([      "action": "$Nʹһ�С������ơ���˫צ�ó�����צӰץ��$nȫ��",
        "force" : 370,
        "attack": 110,
        "dodge" : 40,
        "parry" : 68,
        "damage": 70,
        "lvl"   : 130,
        "skill_name" : "������" ,
        "damage_type" : "ץ��"
]),
([      "action": "$N����������һ�С�Ψ�Ҷ���˫צ������$n�������",
        "force" : 420,
        "attack": 140,
        "dodge" : 50,
        "parry" : 85,
        "damage": 90,
        "lvl"   : 160,
        "skill_name" : "Ψ�Ҷ���" ,
        "damage_type" : "ץ��"
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="cuixin-zhang"; }
int valid_learn(object me)
{
        if( query("character", me) != "�ĺ�����" && query("character", me) != "��ʿ��˫" )
                return notify_fail("�����Բ���������������޷��������׹�צ����ּ��\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�������׹�צ������֡�\n");

        if( query("max_neili", me)<800 )
                return notify_fail("�������̫�����޷��������׹�צ��\n");

        if ((int)me->query_str() < 30)
                return notify_fail("�������������������޷��������׹�צ��\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("����ڹ�̫��޷��������׹�צ��\n");

        if ((int)me->query_skill("claw", 1) < 60)
                return notify_fail("��Ļ���צ��̫��޷��������׹�צ��\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("jiuyin-baiguzhao", 1))
                return notify_fail("��Ļ���צ����򲻹����޷���������ľ����׹�צ��\n");

        return 1;
}
int practice_skill(object me)
{
        object obj;
        object *obs;
        int i, skill, damage;

        skill = me->query_skill("jiuyin-baiguzhao", 1);
        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<500 )
                return notify_fail("������������������׹�צ��\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��������\n");

        if( query("sleep_room", environment(me)) )
                return notify_fail("������������ű�����Ϣ��\n");

        if (skill < 200)
        {
                obs = filter_array(all_inventory(environment(me)),
                                   (: (base_name($1) == CORPSE_OB &&
                                       !query("been_cut/head", $1) ||
                                       base_name($1) == "/clone/misc/head") &&
                                       query_temp("clawed_by_jiuyin", $1)<10:));
                if (sizeof(obs) < 1)
                        return notify_fail("�������׹�ץ����ʬ�������õ�ͷ�ǹǡ�\n");

                addn("neili", -450, me);
        }

        me->receive_damage("qi", 80);
        addn("neili", -40, me);
        if (skill < 200)
        {
                message_vision(HIB "ֻ��$N" HIB "������Ȧ�¹���������ת��������"
                               "�߰˰㻨�������������һ�죬�۵�һ�죬�����ֱָ"
                               "����\nͷ�ǵ����š���������ָ" HIR "Ѫ����"
                               HIB "���Ὣ������\n" NOR, me);

                if (base_name(obs[0]) == "/clone/misc/head")
                        obs[0]->set("long",query("long", obs[0])+
                                    "�����Ȼ�����С��������һ̽���պÿ��Բ��롣\n");

                addn_temp("clawed_by_jiuyin", 1, obs[0]);
                me->improve_skill("jiuyin-baiguzhao", 100 + skill * 5 + random(500));
        }

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
        int d_e1 = 20;
        int d_e2 = 5;
        int p_e1 = -20;
        int p_e2 = -60;
        int f_e1 = 300;
        int f_e2 = 600;
        int i, lvl, seq, ttl = sizeof(action);

        seq = random(ttl);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "ץ��" : "����",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if( query("shen", me) <= -100000)return 1;
        else if( query("shen", me)<0)return 0.8;
        else return 0.6;
}

void skill_improved(object me)
{
        tell_object(me, HIR"���Ȼ���ĵ�����һ�ɶ��ɱ��ɱ��ɱ����Ҫɱ�������ˣ�\n" NOR );
        addn("shen", -200, me);
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;
        mixed result;

        lvl  = me->query_skill("jiuyin-baiguzhao", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (damage_bonus / 2 > victim->query_str())
        {
            victim->affect_by("jy_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ]));
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "��������������һ�����죬�����ǹ����������\n" NOR ]);

                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("jiuyin-baiguzhao", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"jiuyin-baiguzhao/" + action;
}

int help(object me)
{
        write(HIC"\n�����׹�צ��"NOR"\n");
        write(@HELP

    ���ڻʵ���������䣬���������µ���֮�飬���ӡ�У�һ��
����ǧ�İٰ�ʮһ����Ϊ�����ٵ��ء����ʵ�ί�ɿ���֮�ˣ���
�����ѡ��������ⲿ����ؿ̴����֣��ʵ۷���֮����Ҫɱ����
ͷ�������һ��һ���ϸ��У��������Ȼ����˾�ͨ��ѧ�������
��������书�еĸ����������ʦ��ͨ����ϰ�ڹ��⹦������Ϊ
һλ�书����֡�������漰������ɱ������ɽ�֡���֪��������
������ʮ���꣬���ڶ�ÿһ��������ʹ����������������ͨ���ƽ�
�ķ��ӶԸ������ǳ���ɽ����ȥ����ѩ�ޡ�������Щ����ȫ���Ѳ�
�������ˡ��������룺��ԭ����Ҳ���ˣ���Ҳû����û���������
�����⼸ʮ����Ѫ������˰��������¸��Ҹ��ɹ������ѧ������
���꣬�ⷬ��Ѫ���Ǿʹ���û�������������뵽�ķ���д������
�������飬�Ǿ��ǡ������澭���������׹�צ�������������ɵİ�
������

        ѧϰҪ��
                ����200
HELP
        );
        return 1;
}
