// riyue-lun.c �����ַ�

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$Nʹһ��"GRN"�������ơ�"NOR"���������е�$w��$n��$l��ȥ",
        "skill_name" : "������",
        "lvl" : 0
]),
([      "action" : "$Nʹһ��"BLU"����ɽ���ơ�"NOR"��˫��һ�����趯����$w��$n��$l��ɨ",
        "skill_name" : "��ɽ����",
        "lvl" : 8
]),
([      "action" : "$Nʹһ��"MAG"����΢�ơ�"NOR"���͵�һ�����������¶�������$n��$l",
        "skill_name" : "��΢��",
        "lvl" : 16
]),
([      "action" : "$Nʹһ��"RED"�������ơ�"NOR"���������֮��$wɨ��$n��$l",
        "skill_name" : "������",
        "lvl" : 24
]),
([      "action" : "$Nʹһ��"YEL"��Բ���ơ�"NOR"��$w������֮����ֱ��$n��$l",
        "skill_name" : "Բ����",
        "lvl" : 32
]),
([      "action" : "$NԾ���գ�ʹһ��"HIC"�����ػ��ơ�"NOR"���߾�$w����$n��$l",
        "skill_name" : "���ػ���",
        "lvl" : 40
]),
([      "action" : "$Nʹһ��"HIW"��׽���ơ�"NOR"��б������$w����$n��$l",
        "skill_name" : "׽����",
        "lvl" : 48
]),
([      "action" : "$N��һ��������ʹ��"HIR"���Լ��项"NOR"��$wɨ��$n��ͷ��",
        "skill_name" : "�Լ���",
        "lvl" : 56
]),
});
string  *msg = ({
        CYN"��������ֻ$w"CYN"�Ի����������������Ʋ���������$n"CYN"һ��֮�ʣ�$w"CYN"�����˳�ȥ��"NOR,
        MAG"���������У�$w"MAG"��ת������ײ��$n"MAG"����$p"MAG"��Ҫ����ʱ��ȴ�ƹ�$n"MAG"�ɵ�������"NOR,
        MAG"$w"MAG"���������������ɻأ�����$n"MAG"����Ȧ�ӣ����ߺ��ͣ�������б����������Ҳ���������죬�Թ����˾����ŵ��ۻ����ң����񲻶�"NOR,
        YEL"һ����С���ˣ�������Ȼ��$w"YEL"�����һ��������$n"YEL"ײȥ��������ţ���������ɵ�"NOR,
        HIB"ֻ��$w"HIB"����$n"HIB"�����·��ɣ�$w"HIB"��Ծ�鶯�����������������Ƶ����������絶���Ҫ��$n"HIB"��������"NOR,
        HIR"ͻȻ��������𣬼�������$w"HIR"������ײ�����ֹ�һ���ϲ�����$n��ȥ"NOR,
        HIG"������$n"HIG"��ǰ���ģ��͵���$p"HIG"ӭͷ���£������ַ���һ�֣�һ��һ�ͣ��������죬����$n"HIG"$l"NOR,
        HIW"������Х���У�����ֻ$w"HIW"��ֱ�ɡ���б�ɡ������������׹������������ʱ��$n"HIW"��ȫ����·�ѱ�����"NOR,
        HIC"�͵���$w"HIC"��$n"HIC"$l�����£���$p"HIC"����ж��֮ʱ��$w"HIC"��ͻȻ�Ϸɻ���������$p"HIC"��$l"NOR,
        HIM"��$w"HIM"�����ҵ���$n"HIM"ȴ������ͷ�����������һһ��������$w"HIM"���糤�����۾�һ�㣬��Ȼ�����ɵ���$n"HIM"$l"NOR,
        HIG"����ɭɭ���˵�����$w"HIG"����������ζ��������������죬�ڲ���գ�۵�˲Ϣ�䣬ҫĿ�ĵ���������������������⣬Ѹ����ƥ�Ļ�$n��"NOR,
        MAG"�����ٴκ�Χ���ϵ羫âΧ��$n"MAG"�������������䣬ǧ����Ӱ��ӳ��һ��������ѣĿ��ͼ������ͼ�������ˣ�����һƬ����ε���ɫѩ����"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }
int valid_learn(object me)
{
        /*
        if( query("str", me)<32 )
                return notify_fail("�������������㣬�������������ַ���\n");
        */

        if( query("max_neili", me)<1000 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("hammer", 1) < 100)
                return notify_fail("��Ļ��������������������������ַ���\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("riyue-lun", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������������ַ���\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "hammer" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("���������������,�����������ַ���\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object my_w, victim_w;
        object piece;
        victim_w=query_temp("weapon", victim);
        my_w=query_temp("weapon", victim);

//      if( me->query("dex") < 20 || me->query("str") < 20 )

        if( query_temp("weapon", victim) || query_temp("secondary_weapon", victim) )
        {
                if( (int)(me->query_skill("riyue-lun", 1)) < 20 )
                        return HIW"һ�������ײ���������󣬶Է�������Ȼ�������\n"NOR;
                if( random(query_temp("apply/damage", victim))<random(me->query_skill("riyue-lun",1)/3) )
                {
                        if( objectp(my_w=query_temp("weapon", me)) &&
                                (query("id", my_w) == "falun"
                                   || query("id", my_w) == "yinlun"
                                    || query("id", my_w) == "jinlun" )
                                    && query("ownmake", my_w) != 1 )
                        {
                                seteuid(getuid());
                                piece = new("/clone/misc/piece");
                                piece->set_name(query("name", victim_w)+"����Ƭ",({query("id", victim_w),"piece"}));
                                piece->move(environment(victim));
                                set("long", "һ���������£������Ǳ�����Ƭ��\n", piece);
                                destruct(victim_w);
                                return HIB "��������������һ�����������������������Ƭ����һ�أ�\n" NOR;
                        }
                        else return HIR"��ϧ��û�÷��֣�û������Է�������\n"NOR;
                }
        }
}
*/
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon1;  object master;
        weapon=query_temp("weapon", me);
        weapon1=query_temp("weapon", victim);

        if (weapon && weapon1
        &&  me->query_skill("riyue-lun",1)>150 && query("jiali", me )
        &&  query("neili", me)>1000
        // &&  random(10) >= 5
        &&  query("skill_type", weapon) == "hammer"
        &&  me->query_skill_mapped("parry") == "riyue-lun")
        {
                message_combatd(HIW"$N�ֱ۱�����ʩչ�������־���"+weapon->name()+
                                HIW"̽�������һ����ס��$n"+weapon1->name()+HIW"��\n"NOR,
                                me, victim);

                if (random(me->query_str()) > victim->query_str())
                {
                        addn("neili", -100, me);
                        message_combatd(HIG+query("name", me)+"�˾�������$n�۹ǿ���һ������Щ�ͱ����ϣ���ʹ֮����һ�ɣ�"+
                                        weapon1->name()+HIG"�����˹�ȥ��\n"NOR, me, victim);
                        weapon1->unequip();
                        weapon1->move(me);
                } else
                if (random(me->query_str()) > victim->query_str() / 2)
                {
                        addn("neili", -50, me);
                        message_combatd(HIG+query("name", me)+"�˾�������$N���������ļ������������ھ�ʹ��"+
                                        weapon1->name()+HIG"���ַɳ���\n"NOR, victim);
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                } else
                if( query_temp("shield", victim) )
                {
                        addn("neili", -50, me);
                        message_combatd(HIY"$N����ǰ�壬"+weapon1->name()+HIY"ֱ�̹�ȥ������"+
                                        query("name", victim)+"�����������û��˿�ȥ��\n"NOR,victim);
                }

                else message_combatd(HIY"$N����ǰ�壬"+weapon->name()+HIY"ֱ��"+query("name", victim)+"��"+
                                        query("name", victim)+"������죬"+weapon->name()+HIY"һ�����ѣ��������˿�ȥ��\n"NOR,
                                        victim);
        }
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
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);
        string str, message;
        if (weapon)
        {
                if( query("id", weapon) == "jin lun" )
                        str = "����";
                else if( query("id", weapon) == "yin lun" )
                        str = "����";
                else if( query("id", weapon) == "fa lun" )
                        str = "����";
                else str = weapon->name();
                message = msg[random(sizeof(msg))];
                message = replace_string(message, "$w", str);
                switch(str)
                {
                case "����" :
                        message = HIY+message+NOR; break;
                case "����" :
                        message = HIW+message+NOR; break;
                case "����" :
                        message = HIC+message+NOR; break;
                default : break;
                }
                return ([
                        "action" : message,
                        "damage" : 300,
                        "damage_type" : random(2)?"����":"����",
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                ]);
        }
        lvl = (int) me->query_skill("riyue-lun", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"riyue-lun/" + action;
}

int help(object me)
{
        write(HIC"\n�����ַ���"NOR"\n");
        write(@HELP

    �����ַ�Ϊ���ַ������书����ѩɽ�¼�Ϊ�Ե��Ĺ���

        ѧϰҪ��
                ���������20��
                ����100
HELP
        );
        return 1;
}
