// taixuan-gong.c ���͵�̫����
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) { return 1; }
string *dodge_msg = ({
        "$n����̫�������ŷ�������$n�����ĳ������絽������$N��һ�ߡ�\n",
        "$n�ֱۻ�ת��ץס$N����һ�ƣ���$NԶԶ������\n",
        "$nĬ��̫���ھ���������ţ���Ծ��������������ʮ�����⡣\n",
        "$Nֻ����ǰһ����ֻ����$n����һ�ϣ��Լ���������ȻĪ�����������ˡ�\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taixuan-gong", 1);
        return lvl * lvl * 15 / 100 / 10;
}
mapping *actionf = ({
([      "action":"$N˫��һ�٣�һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
        "force" : 540,
        "attack": 220,
        "dodge" : 120,
        "parry" : 120,
        "damage": 155,
        "damage_type":  "����"
]),
([      "action":"$N�����������ʱһ�������������Ϯ��$n",
        "force" : 560,
        "attack": 240,
        "dodge" : 60,
        "parry" : 90,
        "damage": 230,
        "damage_type":  "����"
]),
([      "action":"$N���һ��������һ������ʱһ��������$n����ӿȥ",
        "force" : 570,
        "attack": 235,
        "dodge" : 155,
        "parry" : 135,
        "damage": 260,
        "damage_type":  "����"
]),
([      "action":"$N�����ϣ�ȫ������������˫���͵�����$n",
        "force" : 580,
        "attack": 250,
        "dodge" : 120,
        "parry" : 75,
        "damage": 295,
        "damage_type":  "����"
]),
([      "action":"$N�����죬������֣�ͻȻ��$N˫�������ĳ�������̫���ھ�������$n",
        "force" : 580,
        "attack": 265,
        "dodge" : 140,
        "parry" : 125,
        "damage": 260,
        "damage_type":  "����"
]),
([      "action":"$NͻȻ������һ�࣬��ס$n��·������������ӿ����",
        "force" : 580,
        "attack": 280,
        "dodge" : 125,
        "parry" : 145,
        "damage": 380,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action" : "$N������磬���ƷǷ���$w�������֣�׽��������$n������ȥ",
        "force" : 510,
        "attack": 180,
        "dodge" : 115,
        "parry" : 125,
        "damage": 325,
        "damage_type": "����"
]),
([      "action":"$N���е�$w�������������糤��������������$n����",
        "force" : 510,
        "attack": 188,
        "dodge" : 112,
        "parry" : 115,
        "damage": 310,
        "damage_type": "����"
]),
([      "action":"$N�������е�$w�����緭������ֱ����$n��ȥ",
        "force" : 532,
        "attack": 225,
        "dodge" : 120,
        "parry" : 102,
        "damage": 365,
        "damage_type": "����"
]),
([      "action":"$N����$w�ó�һ�����⻷����ʱ��$n���Ű�Χ",
        "force" : 565,
        "attack": 210,
        "dodge" : 115,
        "parry" : 105,
        "damage": 390,
        "damage_type": "����"
]),
([      "action":"$N�����������$w����������ؾ���$n",
        "force" : 550,
        "attack": 248,
        "dodge" : 110,
        "parry" : 120,
        "damage": 420,
        "damage_type": "����"
]),
});

mapping *actionbad = ({
([      "action" : "$N����ʩ�У�ȴ��ͻȻ���ú�����������ʽ��ֻ�ú���ʹ����",
        "force" : 10,
        "attack": 10,
        "dodge" : -10,
        "parry" : -10,
        "damage": 10,
        "damage_type": "����"
]),
});
mapping *action = ({
([      "action":"$N˫��һ�٣�һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
        "lvl": 0
]),
([      "action":"$N�����������$n�۰���Ѹ���ޱȵ�һ����$nһ�ӵ��˳�ȥ",
        "lvl": 10
]),
([      "action":"$N���һ�����ſ�һ��������$n������ȥ",
        "lvl": 20
]),
([      "action":"$N�����ϣ�˫���͵�����$n",
        "lvl": 30
]),
([      "action":"$N����΢�࣬ͻȻ����һ�ţ�����$n����·���ŵ���;���͵�һ̧������$n����",
        "lvl": 40
]),
([      "action":"$NͻȻ������һ�࣬��ס$n��·������������ӿ����",
        "lvl": 50
]),
});

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = 10;
        int f_e1 = 440;
        int f_e2 = 600;
        int i, lvl, seq, ttl;

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return actionbad[0];

        if( random(me->query_skill("taixuan-gong",1))>220 && query("neili", me)>100 )
        {
                addn("neili", -50, me);
                return ([
        "action": HIR "$N������ͻȻһƬãȻ��ֻ���þ�������������������ڴ�����ȥ���ѹ��ǳ���
���²������룬˳����������һ��ȭ����ߣ����ܶ�ʱ������쩣��ò����֣�"NOR,
        "damage": 1000,
        "parry" : -180,
        "dodge" : -140,
        "force" : 1000,
        "damage_type": "����"]);
        }
        lvl = (int) me->query_skill("taixuan-gong", 1);

        if( weapon )
                ttl = sizeof(actionw);
        else
                ttl = sizeof(actionf);

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : (weapon ? actionw[seq]["action"] : actionf[seq]["action"]),
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int valid_enable(string usage)
{
        object me = this_player();

        if (! me)
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry" || usage == "sword";
        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
                return usage == 0;

        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
                return usage == "force" || usage == "unarmed"
                || usage == "dodge" || usage == "parry";
        else
        if (me->query_skill("sword", 1) < me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) < me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage == "parry";

        else
        if (me->query_skill("sword", 1) < me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) > me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry";

        else
        if (me->query_skill("sword", 1) > me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) < me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="sword" || usage == "parry";

        else
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry" || usage == "sword";

}

int double_attack() { return 1; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return;

        if ((int)me->query_skill("taixuan-gong", 1) < 150
           || me->query_skill_mapped("parry") != "taixuan-gong"
           || me->query_skill_mapped("force") != "taixuan-gong"
           || me->query_skill_mapped("unarmed") != "taixuan-gong"
           || query("neili", me)<500
           || ! living(me))
                return;

        cost = damage / 2;

        if (cost > 100) cost = 100;

        ap=ob->query_skill("force")*12+query("max_neili", ob)+
             ob->query_skill("count", 1) * 6;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "Ĭ��̫�����ھ���̫����"
                                            "�������ȫ��$N" HIR "ֻ�����й���"
                                            "$n" HIR "���ϣ���������ͭǽ����һ�㣬"
                                            "˿���������á�\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "һ�л���$n" HIR "����"
                                            "����ȴ�������ͭǽ������һ�㣬������ʱ"
                                            "��ʧ����Ӱ���١�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "����$n" HIR "һ����Х����������"
                                            "�Ľ�����$N" HIR "��һ�У�ȴû���ܵ�"
                                            "����˺���\n" NOR]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        string msg;
        int lvl;
        object weapon=query_temp("weapon", me);

        lvl = me->query_skill("taixuan-gong", 1);

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return 0;

        if (damage_bonus < 100
           || lvl < 140
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "taixuan-gong")
                return 0;

        // δѧ���������
        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                      return 0;
        }

        // �Ѿ����������
        if( query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             if (! objectp(weapon))
                  if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) != "sword"
                  && query("skill_type", weapon) != "blade" )
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) == "sword"
                 && me->query_skill_mapped("sword") != "taixuan-gong")
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) == "blade"
                 && me->query_skill_mapped("blade") != "taixuan-gong")
                         return 0;
        }

        // if (random(2) == 1)return 0;

        damage_bonus += factor; // ����Ч������
        if (damage_bonus / 2 > victim->query_con()/10)
        {
                addn("neili", -100, me);
                result = ([ "damage" : damage_bonus ]);
                // victim->receive_wound("qi", (damage_bonus - 76) / 2, me);
                // victim->add("neili", -((damage_bonus - random(70)) / 2), me);

                if( query("can_learned/taixuan-gong/enable_weapon", me) && objectp(weapon) )
                {
                        msg = random(2) ? HIM "$N" HIM "һ�й�����������ǧ�����ˣ�̫���ھ�"
                                           "��ʱԴԴ����͸��" + weapon->name() + HIM "ӿ��$n" HIM "��"
                                           "�ڣ�\n" NOR:
                                           HIM "$N" HIM "̫���ھ��ŷ���$n" HIM "ֻ��ȫ��һ�𣬵�ʱһ"
                                           "������֮��͸�ض�����" + weapon->name() + HIM "��Ѫ���죡\n" NOR;
                } else
                {
                        msg = random(2) ? HIW "$N" HIW "һ�й�����������ǧ�����ˣ�̫���ھ�"
                                           "��ʱԴԴ����ӿ��$n" HIW "���ڣ�\n" NOR:
                                           HIW "$N" HIW "̫���ھ��ŷ���$n" HIW "ֻ��ȫ��һ"
                                           "�𣬵�ʱ�������������������߹ǣ�\n" NOR;
                }
                result += ([ "msg" : msg ]);
                return result;
        }
}
int practice_skill(object me)
{
        return notify_fail("̫����ֻ����ѧ(learn)�������������ȡ�\n");
}

int valid_learn(object me)
{
        int level;

        if( !query("jieti", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
                return notify_fail("�����̫�������֮����һʱ��������ᡣ\n");

        if( query("gender", me) == "����" )
                return notify_fail("���޸����ԣ����������������������̫������\n");

        if( query("int", me)<27 )
                return notify_fail("����������Ȼ�������е㲻���ס�\n");

        if( query("dex", me)<27 )
                return notify_fail("���о��˰��죬ֻ����ʽʼ���޷�����ʩչ��\n");

        if( query("con", me)<27 )
                return notify_fail("���о��˰��죬ֻ���ø�����Щ���ʽʼ���޷�����ʩչ��\n");

        if( query("str", me)<27 )
                return notify_fail("���о��˰��죬�о�������Щ�ͣ�ʼ���޷�����ʩչ��\n");


        level = me->query_skill("taixuan-gong", 1);

        if (me->query_skill("force", 1) < level)
                return notify_fail("��Ի����ڹ�����⻹�������޷���������"
                                   "�����̫������\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("��Ի���ȭ�ŵ���⻹�������޷���������"
                                   "�����̫������\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
        return 1000;
}

string perform_action_file(string action)
{
        object me = this_player();

        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return "ѧ������д����Ҳ�޷�ʩչ̫������";

        return __DIR__"taixuan-gong/perform/" + action;
}

string exert_function_file(string action)
{
        object me = this_player();

        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return "ѧ������д����Ҳ�޷�ʩչ̫������";

        return __DIR__"taixuan-gong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n̫������"NOR"\n");
        write(@HELP

    ̫����Դ�����͵��϶����书��

        ѧϰҪ��
                �����Լ��ĸ�Ե
HELP
        );
        return 1;
}
