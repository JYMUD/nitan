// liuyang-zhang.c ��ɽ������

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
void sun1(object me, object victim, object  weapon, int damage);
void sun2(object me, object victim, object  weapon, int damage);
void sun3(object me, object victim, object  weapon, int damage);
void sun4(object me, object victim, object  weapon, int damage);
void sun5(object me, object victim, object  weapon, int damage);
void sun6(object me, object victim, object  weapon, int damage);
int baihong(object me, object victim, int damage);
mapping *action = ({

([      "action" : "$Nһ��"RED"�������۽�"NOR"�����Ƶ�������֮�ϣ�����$n",
        "lvl" : 0,
        "skill_name" : "�����۽�"
]),
([      "action" : "$Nһ��"HIY"�������ƶ�����"NOR"����ɫ���أ�˫����ƮƮ������$n",
        "lvl" : 20,
        "skill_name" : "�����ƶ���"
]),
([      "action" : "$Nһ��"HIR"����б��·��ϼ����"NOR"��˫�ƻû�һƬ��Ӱ����$n�������ڡ�",
        "lvl" : 30,
        "skill_name" : "��б��·��ϼ��"
]),

//([    "action" : "$Nһ��"HIG"������������"NOR"����$n��$l��������",
//      "lvl" : 40,
//      "skill_name" : "��������"
//]),
([      "action" : "$Nһ��"GRN"������һ���ͽ��ѡ�"NOR"��ֻ��һƬ��Ӱ����$n",
        "lvl" : 40,
        "skill_name" : "����һ���ͽ���"
]),

([      "action" : "$N˫��ƽ�ӣ�һ��"BLU"����ϼ�����"NOR"����$n",
        "lvl" : 60,
        "skill_name" : "��ϼ������"
]),
([      "action" : "$Nһ��"HIW"�����ղγ��֡�"NOR"��ֻ��һƬ��Ӱ����$n",
        "lvl" : 70,
        "skill_name" : "���ղγ���"
]),

([      "action" : "$N������Σ�����һ��"HIC"����ϼ��Ѧᡡ�"NOR"����$n��ͷ��",
        "lvl" : 80,
        "skill_name" : "��ϼ��Ѧ�"
]),
([      "action" : "$Nʩ��"HIB"�������������"NOR"�����ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
        "lvl" : 90,
        "skill_name" : "���������"
]),
//([    "action" : "$Nʩ��"HIR"�����������"NOR"��˫��ͬʱ����$n��$l",
//      "lvl" : 100,
//      "skill_name" : "�������"
//])
  ([ "action":
HIY"$Nʹ��"HBBLU+HIW"��ɽ������"NOR+HIY"��һ��"HIR"������������"HIY"ǿ�������������಻��������Ϣ֮��
������ɽ����֮�Ƴ�$n��ȥ��һ����ʽ�ƾ������ƥ��"NOR,
        "lvl" : 201,
                "force":                500,
     //           "damage":               300,
                 "post_action":               (:sun1:),
                "damage_type":  "����",
       ]),
//2
  ([ "action":
HIY"$N����ȫ��������������棬һ��"HIW"���������ա�"HIY"ȫ�����·����޴�Ĺ�â����
�۵Ĺ�âʹ$n�޷����ۣ�$N���Ϸ���ǿ�ҵ��¶�ʹ$nȫ������������
���¯֮��ʹ����֡�"NOR,
        "lvl" : 210,
        "force":        520,
     //   "damage":       350,
        "post_action":               (:sun2:),
        "damage_type":  "����",
        ]),
//3
  ([ "action":
HIY"$N�����˾������澭�����������棬������ת�ھ����ߵ��ﻯΪ˪��ʹ��\n"
HBBLU+HIW"��ɽ������"NOR+HIY"������"HIC"����ʢ��˥��"HIY"��ǿ����ھ���ʹ$n������������
������Ϣ�����ܵ����ص����˿�����Ѫ��"NOR,
           "lvl" : 220,
           "force":       540,
       //    "damage":      400,
           "post_action":               (:sun3:),
           "damage_type":  "����",
      ]),
//4
  ([ "action":
HIC"$N����ӥ�������ʹ��"HBBLU+HIW"��ɽ������"NOR+HIC"������"HIW"�����������"HIC"�Թ����������$n���ķ������䲻��˫
���˹���$n�������˻���ȥ��"NOR,
        "lvl" : 230,
          "force":        560,
      //    "damage":       450,
          "post_action":          (:sun4:),
          "damage_type":  "����",
        ]),
//5
  ([ "action":
HIM"$Nʹ��"HBBLU+HIW"��ɽ������"NOR+HIM"������"HIC"��������ѩ��"HIM"��$N���η���ȫ��ɢ��������˪������ѩ
��������裬$n��ȫ���������ܵ����Σ�$N�û���������͵Ϯʹ���ܴ���"NOR,
        "lvl" : 240,
           "force":        580,
     //      "damage":       500,
          "post_action":      (:sun5:),
           "damage_type":  "����",
        ]),
//6
  ([ "action":
HIR"$N�۾�˫���˾����棬����ǿ�������ʹ��"HBBLU+HIW"��ɽ������"NOR+HIR"������"HIY"�������ƻ�"HIR"������
�ƾ�����$nȫ���������ᾢ�������������"NOR,
        "lvl" : 250,
           "force":        600,
     //      "damage":       600,
           "post_action":      (:sun6:),
           "damage_type":  "����",
        ])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="zhemei-shou"; }

int valid_learn(object me)
{
        if( query("str", me)<30 )
                return notify_fail("���о��˰��죬�о�������Щ�ͣ�ʼ���޷�����ʩչ��\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("����ɽ�����Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("����ڹ���򲻹����޷��������ơ�\n");

        if( query("max_neili", me)<200 )
                return notify_fail("�������̫�����޷��������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyang-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ɽ�����ơ�\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<40 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<30 )
                return notify_fail("���������������ɽ�����ơ�\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e2 = -10;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 160;
        int f_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liuyang-zhang", 1);

        if( random(query_temp("lingjiu/baihong", me))>50 || query_temp("baihong_attack", me) )
        {
                string msg;
                switch(query_temp("baihong_attack", me) )
                {
                        case 1: msg = "����$N����һ���������ƹ�$N�����ӣ�ֱ����$p$l";
                                break;
                        case 2: msg = WHT"˭֪$Nһ��δ�ߵڶ����������������ؾ����������糤��֮�Σ���������"NOR;
                                break;
                        default: msg = WHT"ͻȻ��$N�����ƿգ�����$n���������棬�����絶��ת��б��$p$l"NOR;
                                break;
                }

                addn_temp("lingjiu/baihong", -1, me);
                addn("neili", -30, me);

                return ([
                        "action": msg,
                        "force" : 380+random(120),
                        "dodge" : -60,
                        "parry" : -80,
                        "damage": 220+random(80),
                        "damage_type":"����",
                        "post_action": (: baihong :)
                        ]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        if ( /*me->query_family() =="lingjiu" &&*/ (int)me->query_skill("bahuang-gong",1) >= 250)
        {
                        seq=sizeof(action)-6+random(6);
                        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : action[seq]["force"],
                "damage"      : action[seq]["damage"],
                "post_action"   : action[seq]["post_action"],
                "damage_type" : random(2) ? "����" : "����",
          ]);
        }
        if (seq > sizeof(action)-6)
                seq = sizeof(action)-6;
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "����" : "����",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liuyang-zhang/" + action;
}
void sun1(object me, object victim, object weapon, int damage)
{
         if( ((query("combat_exp", me)+random(2000000))>(query("combat_exp", victim)+random(2000000)) )
         || random(50)>40)
         {
           message_combatd(HIR"��������֮"HBRED+HIM"����ɽ���졿\n"NOR, me, victim);
           victim->receive_damage("qi",200);
           COMBAT_D->report_status(victim);
           message_combatd(HIR"��������֮"HBBLU+HIC"���κ�����\n"NOR, me, victim);
           victim->receive_wound("qi",100);
           COMBAT_D->report_status(victim);
           message_combatd(HIR"��������֮"HBGRN+HIG"������޼���\n"NOR, me, victim);
           if( (query("neili", victim)-100)<0 )
             set("neili", 0, victim);
           else addn("neili", -100, victim);
           COMBAT_D->report_status(victim);
         }else message_combatd(HIW"$n˳��������$N�����ྡྷ�Ĺ�����\n"NOR, me, victim);

}
void sun2(object me, object victim, object weapon, int damage)
{
        if(((me->query_skill("dodge")+random(100)) > (victim->query_skill("dodge")+random(100)))
         || random(50)>40)
        {
          message_combatd(HIR"\n$nһ����С�ı�$N�������ྡྷ���ˡ�\n"NOR, me, victim);
          victim->receive_damage("qi",200);
          victim->apply_condition("hot_poison",random(10)+1);
          COMBAT_D->report_status(victim);
        }
}
void sun3(object me, object victim, object  weapon, int damage)
{
       if(((me->query_skill("force")+random(500)) > (victim->query_skill("force")+random(500)))
         || random(50)>30)
       {
         message_combatd(HIC"\n$n�ܲ��˺�����ȵļ尾�������ص����ˡ�\n"NOR, me, victim);
         victim->receive_damage("qi",300);
         victim->apply_condition("cuff_power",1);
         COMBAT_D->report_status(victim);
       }
}
void sun4(object me, object victim, object weapon, int damage)
{
       if(((me->query_skill("parry")+random(100)) > (victim->query_skill("parry")+random(100)))
         || random(50)>45)
       {
         message_combatd(HIY"\n$n���㲻������$N�����������ˡ�\n"NOR, me, victim);
         victim->receive_wound("qi",200);
         victim->apply_condition("bleeding",random(10)+1);
         COMBAT_D->report_status(victim);
       }
}
void sun5(object me, object victim, object weapon, int damage)
{
       if( ((query("parry", me)+random(100))>(query("parry", victim)+random(100)) )
         || random(50)>40)
       {
         message_combatd(HIW"\n$Nʹ����ɽ������֮���С���ɽ��÷�֡���$n������ǣ���޷�ʹ����\n"NOR, me, victim);
         victim->receive_damage("qi",200);
         victim->start_busy(me->query_skill("liuyang-zhang",1)/100);
         COMBAT_D->report_status(victim);
       }
}

void sun6(object me, object victim, object weapon, int damage)
{
       if( ((query("combat_exp", me)+random(2000000))>(query("combat_exp", victim)+random(2000000)) )
         || random(50)>45)
       {
         message_combatd(HIG"$N"HIY"�����ƻ�"HIG"һ����$n�˾����ﾹ�о��տյ��������ھ���\n"NOR, me, victim);
         if( query("neili", victim)<500 )
          set("neili", 0, victim);
         else
          addn("neili", -500, victim);
 //        COMBAT_D->report_status(victim);
       }
}

int baihong(object me, object victim, int damage)
{
        int level = (int)me->query_skill("liuyang-zhang", 1)/2;

        addn_temp("baihong_attack", 1, me);

        if( damage == RESULT_DODGE && query_temp("baihong_attack", me)<3 )
        {
                addn_temp("apply/attack", level, me);

                if( query_temp("baihong_attack", me) == 1 )
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);
                else delete_temp("baihong_attack", me);

                addn_temp("apply/attack", -level, me);
                return 1;
        }
        else delete_temp("baihong_attack", me);
        return 1;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("liuyang-zhang", 1); 

        if( lvl >= 1000 && query("reborn/times", me) &&
            !query("can_perform/liuyang-zhang/zun", me) )  
        { 
                tell_object(me, HIC "��ͨ������ɽ�����ơ�" HIR "�˻Ķ�����" HIC "���İ��ء�\n" NOR);     
                set("can_perform/liuyang-zhang/zun", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
}

int help(object me)
{
        write(HIC"\n��ɽ�����ƣ�"NOR"\n");
        write(@HELP

    ��ɽ������Ϊ���չ��书������

        ѧϰҪ��
                ��ڤ��20����˻�����Ψ�Ҷ���20��
                ����50
HELP
        );
        return 1;
}
