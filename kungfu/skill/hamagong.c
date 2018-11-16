// hamagong.c ��󡹦

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; } 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hamagong", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

/*
mapping *action = ({
([      "action" : "$N����������һ�ֳŵأ����Ӻ�ͦ��ֻ��һ����$n��$l�ĳ�",
        "lvl" : 0,
        "skill_name" : "��󡹦"
]),
([      "action" : "$N˫���ڵ���һ�ţ����Ӻ��ذ���һԾ���ߣ�����$n����ǰ��������$pֱ������",
        "lvl" : 10,
        "skill_name" : "��󡹦"
]),
([      "action" : "$NͻȻ�������Լ�������ץһ�ѣ��ַ������Լ����Ϻ���һ�ţ�һ�ƻ�������;����ر䣬ʵ��֪����δ�",
        "lvl" : 20,
        "skill_name" : "��󡹦"
]),
([      "action" : "ͻȻ֮�䣬$N������������ȫȻ���أ�΢΢��ͷ��һ����ĭ��$n$l��ȥ",
        "lvl" : 30,
        "skill_name" : "��󡹦"
]),
([      "action" : "$N˿��������ɫ��˫��΢��������ƽ�죬���ƻ��������󡹦�ľ���������һ������$n",
        "lvl" : 80,
        "skill_name" : "��󡹦"
]),
([      "action" : "$NĬ��ھ�����������ֻ����ת����˳�죬����һ������Ծ�𣬹���һ���к���˫�ƶ���$n�ĳ�",
        "lvl" : 110,
        "skill_name" : "��󡹦"
]),
([      "action" : "����$N˫��΢����˫�ƻ��գ�Ȼ����$nһ��һ�£�һ��һ�գ���Ȼ����",
        "lvl" : 140,
        "skill_name" : "��󡹦"
]),
([      "action" : "$N���۱�ס����������Ƭ�̣���Ծ�����۾�Ҳ����������˫�Ʊ���$n�ķ������˳�ȥ",
        "lvl" : 170,
        "skill_name" : "��󡹦"
]),
([      "action" : "$N�Ų�ҡҡ�ϻϵĿ���ȥ���Ͼͻ��������Ȼ˫��һ�䡢һ�ǣ����и��һ���кȣ�������$n��Ȼ�Ƴ�",
        "lvl" : 199,
        "skill_name" : "��󡹦"
]),
});
*/
mapping *action = ({
([      "action": "$N����һԾ��ʹ��һ��" + HIY"��ɳĮ���ۡ�"NOR + "�����ƺᣬ���ƴ�����$n�ƿ���",
        "force" : 200,
        "lvl"   : 0,
        "dodge" : -20,
        "damage": 240,
        "skill_name": "ɳĮ����",
        "damage_type": "����"
]),
([      "action":"ֻ��$Nٿ����ǰ���һ����һ��" + WHT"��������项"NOR + "��˫��һ��˳�ƹ���$n",
        "force" : 220,
        "lvl"   : 20,
        "dodge" : -20,
        "damage": 250,
        "skill_name": "�������",
        "damage_type": "����"
]),
([      "action":"$Nһ��" + HIW"����ɳ���̡�"NOR + "�����������޷�������΢�£�����$n����",
        "force" : 400,
        "lvl"   : 40,
        "dodge" : -30,
        "damage": 250,
        "skill_name": "��ɳ����",
        "damage_type": "����"
]),
([      "action":"$N��ü���������������ޣ�ǡǡ��$n����һһ��ס������������֮�⣬����һ��" + HIR"������Ūѩ��"NOR + "��",
        "force" : 225,
        "dodge" : -30,
        "lvl"   : 70,
        "damage": 270,
        "skill_name": "����Ūѩ",
        "damage_type": "����"
]),
([      "action":"$Nһ��" + HIB"����޿�;��"NOR + "�������Ჽ�����˷�����˫��ƽ�ƣ������������ֱ����$n��",
        "force" : 530,
        "dodge" :-20,
        "lvl"   : 100,
        "damage": 300,
        "skill_name": "��޿�;",
        "damage_type": "����"
]),
});

mapping *reverse_action = ({
([      "action": "����$N���������������������������һ������ݺݵĳ�$n�˽�����",
        "dodge": -15,
        "parry": -20,
        "force": 300,
        "damage": 60,
        "damage_type": "����"
]),
([      "action":"����$N���Ƹ������������°�ĭ����ͷ��$n��ײ",
        "parry": -15,
        "force": 360,
        "damage": 70,
        "damage_type": "����"
]),
([      "action":"$N����ſڣ�����һ��������$n$lҧ�䣬�ֿ���׼",
        "dodge": -5,
        "force": 420,
        "damage": 80,
        "weapon": "����",
        "damage_type": "ҧ��"
]),
([      "action":"$Nһ����ĭ���£���Ю���磬����̵����ĭҲ�����˹�������",
        "dodge": -45,
        "force": 480,
        "damage": 90,
        "weapon":"��ĭ",
        "damage_type": "����"
]),
([      "action":"$N��Ȼ���죬һ����ĭ��$n������ȥ�����ƻ���$n���ܵķ�λ��ͬʱ����һ��Ũ̵�½�����",
        "dodge": -30,
        "force": 540,
        "damage": 100,
        "weapon" : "Ũ̵",
        "damage_type": "����"
]),
([      "action":"��ʱ$N��ʹ����������ϣ��Ź֣�������ף�����ʱ��������ʱ��ֱ������Ȼһ�ֳŵأ����Ӻ�ͦ��һ�ֳ��ƴ���$n$l",
        "dodge": -10,
        "force": 600,
        "damage": 110,
        "damage_type": "����"
]),
});

int valid_combine(string combo) { return combo=="shexing-diaoshou"; }

int valid_enable(string usage)
{
        if (usage == "force" || usage == "parry" ) return 1;
        if (usage == "strike") {
                if (this_player()->query_skill("hamagong",1) < 200) {
                        /*
                        message_vision("$N�������������й������Ľ��˼�����Ҫ����󡹦�ھ�����ȭ��֮�ϣ����������ʹ�ò��ϡ�\n", this_player() );
                        write("��ĸ�󡹦����㣬�޷����������Ʒ��С�\n");
                        */
                        return 0;
                }
                return 1;
        }
        return 0;
}
int valid_learn(object me)
{
        mapping skl;
        string *sname;
        int v, i, k=0;

        if( query("character", me) == "��������"
            || query("character", me) == "������" )
                return notify_fail("�����а��������󡹦�����쳣�����ƻ��˼���"
                                   "�����Ǳ���Ϊ�\n");

        /*
        if( query("con", me)<32 )
                return notify_fail("����������������޷�������󡹦��\n");

        if( query("dex", me)<32 )
                return notify_fail("��������̫��޷�������󡹦��\n");
        */

        if( query("gender", me) == "����" && query("hamagong", me)>49 )
                return notify_fail("���޸����ԣ���������������������ĸ�󡹦��\n");

        /*
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("��Ļ�����������㣬��������󡹦��\n");
        */

        i = (int)me->query_skill("hamagong", 1);

        if ((int)me->query_skill("force", 1) < 30
         || (int)me->query_skill("force", 1)/2 < i/3 )
                return notify_fail("��Ļ����ڹ�����㣬����ѧ��󡹦��\n");

        if( query("tianmo_jieti/times", this_player()) )
                return ::valid_learn(me);

        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );

        if(me->query_skill("hamagong", 1) > 99){

                for(v=0; v<sizeof(skl); v++) {
                        if (SKILL_D(sname[v])->check() == "force")
                        k++;
                }
                if ( k >=3 )
                return notify_fail("�����ڲ�ͬ���������ײ����������������ڹ���\n");
        }

        if( query("class", me) == "bonze" && !query("reborn/times", me))
        {
                if( query("gender", me) == "Ů��" )
                        return notify_fail("С�������󡹦�����±��˽���ͺͷ�����\n");
                if( query("gender", me) == "����" )
                        return notify_fail("��ʦ������󡹦�����±��˽���ͺͷ�����\n");
        }

        if( query("family/family_name", me) == "ؤ��" && !query("reborn/times", me) )
                return notify_fail("�Ͻл���ͽ��ѧ���˸�󡹦��\n");

        if( query("family/family_name", me) == "�䵱��"  && !query("reborn/times", me))
                return notify_fail("�ϵ�����󡹦�����±��˽���ţ���Ӹ����\n");

        return ::valid_learn(me);
}
int practice_skill(object me)
{
        if( query("family/master_id", me) != "ouyang feng"
         && me->query_skill("hamagong", 1) > 200)
                return notify_fail("��󡹦�����ָ����ܼ�����ߡ�\n");

        if( query_temp("weapon", me) )
                 return notify_fail("���Ӳ��ֱֳ��У���������󡹦Ҳ������֡�\n");

        if( query("jing", me)<50 )
                return notify_fail("��ľ�����������󡹦��\n");

        if( query("neili", me)<100 )
                return notify_fail("���������������󡹦��\n");
        addn("neili", -30, me);
        me->receive_damage("jing", 10);
        if (me->query_skill("hamagong", 1) > 100){
                addn("neili", -40, me);
                me->receive_damage("jing", 20);
        }
        if (me->query_skill("hamagong", 1) > 150){
                addn("neili", -20, me);
                me->receive_damage("jing", 10);
        }
        if (me->query_skill("hamagong", 1) > 200){
                addn("neili", -10, me);
                me->receive_damage("jing", 10);
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
        int d_e1 = -40;
        int d_e2 = -20;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 190;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        string *power_msg =
        ({
                HIR"$N���������������󡹦��˫��ƽ�ƣ�������ü�����������к���������֮�����з缲��Ѹ���;���ʵ�Ƿ�ͬС��"NOR,
                WHT"$N�������ŭ�𣬶�������������˫�����������δ�����Ʒ��ѽ����³�������һ�ɾ���ֱ��$n���ţ��Ƶ���ǿ�ޱ�"NOR,
                HIR"$N��ɫ���������������鼡��΢΢ǣ�����������������һ����У�˫��ͦ����һ�ɾ������ֱײ�ĳ�$n�ƽ�����"NOR,
                WHT"$N�׵����ӣ����й������Ľ���������˫���Ƴ����Ը�󡹦��$n�͹���$n������$P��������֮�£�ֻ���û�����������������"NOR,
        });
        string *reverse_msg =
        ({
                HIM"����$N�������أ��������ף������������Լ�������ץһ�ѣ������������Լ����Ϻ���һ�ţ�ÿһ�ƴ򽫳�������;����ر䣬ʵ��֪�򽫺δ�"NOR,
                HIM"$N��Ȼ���������������Լ��������⣬��һ����˫�־ݵأ�����$n�����ط���һ������Ȼ�����Ծ��˫����$n��������"NOR,
                HIM"ͻȻ֮�䣬$N������������ȫȻ���أ����й����ޱȣ�����󡹦��ת���ã�������֮��������֮����������׽��"NOR,
                HIM"$Nȫ������˳���棬����������Ȼ���˴�������Ǵ��д��ţ����ֵֹ�������$n����ѽ�"NOR,
        });

        lvl = (int) me->query_skill("hamagong", 1);
        if (me->query_skill_mapped("force") == "hamagong" ) {
                if( !query_temp("hmg_dzjm", me) && query_temp("powerup", me) && random(me->query_skill("force",1))>250 && query("neili", me)>1000 && query("jiali", me)>100 )
                        return ([
                        "action": power_msg[random(sizeof(power_msg))],
                        "dodge": -120,
                        "parry": -120,
                        "force": 650+random(100),
                        "damage": 120,
                        "damage_type": random(2)?"����":"����"
                        ]);
                else if( query_temp("reverse", me) && random(me->query_skill("force",1))>400 && random(me->query_skill("strike",1))>300 && query("neili", me)>1000 )
                        return ([
                        "action": reverse_msg[random(sizeof(reverse_msg))],
                        "dodge": -200,
                        "parry": -200,
                        "force": 630+random(100),
                        "damage": 300+random(20),
                        "damage_type": "����",
                        ]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        if( query_temp("hmg_dzjm", me) )
                return ([
                        "action"      : reverse_action[random(6)]["action"],
                        "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                        "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                        "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                        "damage_type" : random(2) ? "����" : "����",
                ]);
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

        lvl = me->query_skill("hamagong", 1);

        if (damage_bonus < 150
           || lvl < 180
           || query("neili", me)<300
        // || query_temp("weapon", me )
           || me->query_skill_mapped("force") != "hamagong"
           || me->query_skill_mapped("strike") != "hamagong"
           || me->query_skill_prepared("strike") != "hamagong")
                return 0;

        if (damage_bonus / 2 > victim->query_con() / 10)
        {
                addn("neili", -30, me);
                victim->receive_wound("qi", damage_bonus/2, me);
                return WHT "$n" WHT "Ӳ����$N" WHT "һ�ƣ���ʱȫ"
                       "��һ���������������һ����Ѫ��\n" NOR;
        }
}

string exert_function_file(string func)
{
        return __DIR__"hamagong/exert/" + func;
}

string perform_action_file(string action)
{
        return __DIR__"hamagong/perform/" + action;
}

int help(object me)
{
        write(HIC"\n��󡹦��"NOR"\n");
        write(@HELP

    ŷ���洴���˹���Ϊ����ɽ�ɱ����ڹ����˹�Ҳ����Ϊ�Ʒ�ʹ
�ã����������ε��ֻ�����
    ���󡹦��ϵ�Ծ��ƶ�����ȫ�������ƣ��������£�ֻҪ��
��һʩ��������ʱ���������ޱȵľ�������������������ƥ��

        ѧϰҪ��
                �����ڹ�10��
                ̫���޷�����50�����ϵĸ�󡹦
                ��Ӧ������
HELP
        );
        return 1;
}
