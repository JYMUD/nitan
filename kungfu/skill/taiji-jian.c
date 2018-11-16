// taiji-jian.c ̫������

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int taiji(object me, object victim, object weapon, int damage);
int raozhi(object me, object victim, object weapon, int damage);

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
         "$p���ֽ���б����$W��������˸���Ȧ��ƽ����$P$w֮�ϣ�����������$w��ʱһ����\n",
         "$p$W�����֣�����ǰ��������ԲȦ��$P��$p�������࣬��סȫ�����ް�ֿ�϶��\n",
         "$p����δ��ʹ�ϣ���ȻȦת��ͻȻ֮�䣬$P��ǰ�����˼�����ɫ��Ȧ����ȦСȦ����ȦбȦ����˸���ѡ�$P�۾�һ����ֻ�û��С�\n",
         "$p��������ר־����һ��̫������ʹ��Բת���⣬�����쳣����ס�Ż���\n",
         "$p��̫�����С��������衹��ʽ�⿪��$P��$p����ʱ�������ᣬ����ڼҽ�������������$p���֣�����һ����\n"
});
string *taiji_msg = ({
         "$N��������̤�ϣ��������֣�һ�С��������¡�������ʵʵ�������ֽ����У������Ϲ�â��˸�������͵ķ�����΢����",
         "$N�������¿��ϡ�������������̫���������Ҫ֮���������˳���������һ���˿������಻��",
         "$N����$w������ǰ��������һ���Ρ�$nֻ��һ��ɭɭ������ֱ�ƹ���",
         "$N������������������$w��ס������ͻȻƽ�̣����⼱��������������δ���$P��һ����������$n�����ߴ�ҪѨ",
         "$N����δ��ʹ�ϣ���ȻȦת��ͻȻ֮�䣬$n��ǰ�����˼�����ɫ��Ȧ����ȦСȦ����ȦбȦ����˸����",
         "$N�������õĹ�ȦԽ��Խ�࣬������ʱ��$Pȫ��������������Ȧ֮�У���Ȧһ��δ������һ��������\n$w��ʹ�ü��죬ȴ������˿����������֮�����������֮�����Ѵ�춻���",
         "$nֻ������ǧ�ٱ�$w��ס��$Nȫ��$N�������ƣ��˵��Ǿ���������\n����������������ɵı���ȴ���ƶ���ǧ�ٸ���Ȧ�����˳�һ�㣬����ӿ��",
         "$N����һ��һ�е��๥����������ʮ�н�����ɵ����ƣ�ͬʱ��Ϊ���ƣ�ʹ$n�޷�����"
});
mapping *action = ({
([      "action" : "$N�鲽������һ��"+(order[random(13)])+"�����ѵ�ˮ��"NOR"������$w���������һ��������$n��$l",
        "lvl" : 0,
        "skill_name" : "���ѵ�ˮ"
]),
([      "action" : "$N��ǰ����һ�������ֽ���������$wʹ��һʽ"+(order[random(13)])+"��ָ���롹"NOR"ֱ��$n��$l",
        "lvl" : 4,
        "skill_name" : "ָ����"
]),
([      "action" : "$N��������һ�죬���ֽ���������$wʹ��һʽ"+(order[random(13)])+"������ǡ�"NOR"����$n��$l",
        "lvl" : 9,
        "skill_name" : "�����"
]),
([      "action" : "$N˫ϥ�³�������$wʹ��һʽ"+(order[random(13)])+"��̽��ʽ��"NOR"�����¶��ϼ���$n��$l",
        "lvl" : 14,
        "skill_name" : "̽��ʽ"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"�������Ӳ���"NOR"��$w���϶��»���һ���󻡣�ƽƽ����$n��$l��
ȥ",
        "lvl" : 19,
        "skill_name" : "�����Ӳ�"
]),
([      "action" : "$N���������һš��һ��"+(order[random(13)])+"��������β��"NOR"������$w������$n��$l��ȥ",
        "lvl" : 24,
        "skill_name" : "������β"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"������ɨ��"NOR"��һ��"+(order[random(13)])+"������ɨ��"NOR"������ƽָ��һ���ǳɺ�ɨ$n��
$l",
        "lvl" : 29,
        "skill_name" : "����ɨ����ɨ"
]),
([      "action" : "$N������ϥ������$wбָ��һ��"+(order[random(13)])+"������Ͷ�֡�"NOR"����$n��$l",
        "lvl" : 34,
        "skill_name" : "����Ͷ��"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"��������ˮ��"NOR"��$w���¶��ϻ���һ���󻡣�ƽƽ�ػ���$n��$l",
        "lvl" : 39,
        "skill_name" : "������ˮ"
]),
([      "action" : "$Nʹ��"+(order[random(13)])+"���������¡�"NOR"��$w��������ԲȦ������ֱ�������಻�ϻ���$n
��$l",
        "lvl" : 44,
        "skill_name" : "��������"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"������Ҷ��"NOR"��$w����ػ�������Բ����Ѹ�ٵ���$n��$l��ȥ",
        "lvl" : 49,
        "skill_name" : "����Ҷ"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"������ͷ��"NOR"��$w����һ������ҸߵĴ󻡣�бб��ն��$n��$l",
        "lvl" : 54,
        "skill_name" : "����ͷ"
]),
([      "action" : "$Nʹ��"+(order[random(13)])+"��ʨ��ҡͷ��"NOR"��$w�������󻮳�һ�����֣���$nȦ������",
        "lvl" : 59,
        "skill_name" : "ʨ��ҡͷ"
]),
([      "action" : "$N���̤ʵ���ҽ���㣬һ��"+(order[random(13)])+"������ָ·��"NOR"������$w����һ�Ž�����
����$n��$l",
        "lvl" : 64,
        "skill_name" : "����ָ·"
]),
([      "action" : "$N����Ծ��һ��"+(order[random(13)])+"��Ұ��������"NOR"��$w�ڰ���л�ΪһȦ��â������$n
��$l",
        "lvl" : 69,
        "skill_name" : "Ұ������"
]),
([      "action" : "$N����ǰ���󹭣�һ��"+(order[random(13)])+"������ʽ��"NOR"������$wֱ��$n��$l",
        "lvl" : 74,
        "skill_name" : "����ʽ"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"��С���ǡ�"NOR"����������һ�죬���ֽ���������$wƽƽ����$n��
$l��ȥ",
        "lvl" : 79,
        "skill_name" : "С����"
]),
([      "action" : "$N������ϣ�һ��"+(order[random(13)])+"����Գ�׹���"NOR"������$wбб����$n��$l��ȥ",
        "lvl" : 84,
        "skill_name" : "��Գ�׹�"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"��ӭ�絧����"NOR"��$w���������һ�ӣ�$nȴ����һ�ɾ���ӭ��Ϯ
����",
        "lvl" : 89,
        "skill_name" : "ӭ�絧��"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"��˳ˮ���ۡ�"NOR"��$w���϶��»���һ���󻡣�ƽƽ����$n��$l��
ȥ��",
        "lvl" : 94,
        "skill_name" : "˳ˮ����"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"�����Ǹ��¡�"NOR"��$w����$n��$l",
        "lvl" : 99,
        "skill_name" : "���Ǹ���"
]),
([      "action" : "$NͻȻ�̶���������һ��"+(order[random(13)])+"���������¡�"NOR"��$w���¶��ϵ���$n��$l��ȥ",
        "lvl" : 104,
        "skill_name" : "��������"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"������ʽ��"NOR"��$w���¶������컮��һ���󻡣�ƽƽ����$n��$l
��ȥ",
        "lvl" : 109,
        "skill_name" : "����ʽ"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"���Ʒ��붴��"NOR"��$w���϶��»���һ���󻡣�ƽƽ����$n��$l��
ȥ",
        "lvl" : 114,
        "skill_name" : "�Ʒ��붴"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"������չ�᡹"NOR"������Ծ������$w����$n��$l",
        "lvl" : 119,
        "skill_name" : "����չ��"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"�����ֽ���"NOR"��$w����һƬ���̣�ƽƽ����$n��$l��ȥ",
        "lvl" : 124,
        "skill_name" : "���ֽ�"
]),
([      "action" : "$N��������棬������ǰһ�ˣ�һ��"+(order[random(13)])+"�������пա�"NOR"��$w��$n��$l��
ȥ",
        "lvl" : 129,
        "skill_name" : "�����п�"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"����ɨ÷����"NOR"������Ծ�ڰ�գ�����$wɨ��$n��$l",
        "lvl" : 90,
        "skill_name" : "��ɨ÷��"
]),
([      "action" : "$Nһ��"+(order[random(13)])+"��ȴ���齣��"NOR"�����Ծ����أ�$w�س飬���ֹ���$n��$l",
        "lvl" : 139,
        "skill_name" : "ȴ���齣"
]),
([      "action" : "$N���Ȱ�����ף�һ��"+(order[random(13)])+"������Ʊա�"NOR"��������ָ��ת������$n��$l",
        "lvl" : 144,
        "skill_name" : "����Ʊ�"
]),
([      "action" : "$N����š���������鱧��һ��"+(order[random(13)])+"������հ�ա�"NOR"��$w�й�ֱ��������$n��$l",
        "lvl" : 149,
        "skill_name" : "����հ��"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("int", me)<26 )
                return notify_fail("����������̫��������̫������Ҫ�衣\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("taiji-quan", 1) < 100)
                return notify_fail("���̫��ȭ���̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����̫��������\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("taiji-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������̫��������\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<100 )
                return notify_fail("�������������̫��������\n");

        if( query("neili", me)<75 )
                return notify_fail("�������������̫��������\n");

        me->receive_damage("qi", 50);
        addn("neili", -64, me);
        return 1;
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
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
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -50;
        int p_e2 = -45;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 60;
        int m_e2 = 150;
        int i, lvl, seq, ttl = sizeof(action), busy_time;
        object victim;
        string *limbs, limb, target, msg;

        lvl = (int) me->query_skill("taiji-jian", 1);
        busy_time = lvl/20;
        if( objectp(victim = me->select_opponent()) )
        {
                limbs=query("limbs", victim);
                limb = limbs[random(sizeof(limbs))];
                target = victim->name();
        }

//////// ����˫�� yun taiji���˫��/////
        if( query_temp("double_attack", me) )
        {
                return ([
                        "action" : HIW"ͻȻ֮�䣬$N�������֣�����һ������$n$l��������һ�¿�������"NOR,
                        "force"  : 350+random(100),
                        "dodge"  : -80,
                        "parry"  : -80,
                        "damage" : 200+random(50),
                        "damage_type" : "����" ]);
        }
////////̫���� chan ����û��/////
        if( query_temp("chan/"+target, me) )
        {
                victim->start_busy(2);
                addn("neili", -20, me);
                addn_temp("chan/"+target, 1, me);

                if( query_temp("chan/"+target, me) >= busy_time )
                        delete_temp("chan/"+target, me);
        }
//////// perform raozhi���˫�������� ////
        if( random(query_temp("wudang/raozhi", me))>50 ||
                query_temp("raozhi_attack", me) )
        {
                switch(query_temp("raozhi_attack", me) )
                {
                        case 1: msg =HIY"�����һ�����죬$w"+HIY+"����������ֱ����$p$l"NOR;
                                break;
                        case 2: msg =HIC"˭֪$N�$w"HIC"���������ؾ�������ɻ�������һ�䣬���糤��֮�Σ���������"NOR;
                                break;
                        default: msg = HIW"ͻȻ��$N$w"HIW"�ƿգ�����$n"+limb+"��������;������΢������Ȼ���˹�ȥ��б��$p$l"NOR;
                                break;
                }
                addn_temp("wudang/raozhi", -1, me);
                addn("neili", -25, me);
//              if( wizardp(me) )
//                      tell_object(me, sprintf("\nap: %d", COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK)));
                return ([
                        "action": msg,
                        "dodge" : -100,
                        "parry" : -100,
                        "force" : 380+random(120),
                        "damage": 220+random(80),
                        "damage_type":"����",
                        "post_action": (: raozhi :)
                ]);
        }
///////////yun taiji�����ͨ��////////////
        if( query_temp("taiji", me) && query("neili", me)>100 )
        {
                addn_temp("taiji_fight", 1, me);
                addn("neili", -10, me);
                return ([
                        "action": taiji_msg[random(sizeof(taiji_msg))],
                        "force" : 420+random(120),
                        "dodge" : -100-random(50),
                        "parry" : -100-random(50),
                        "damage": 220+random(80),
                        "damage_type" : random(2)?"����":"����",
                        "post_action" : (: taiji :) ]);
        }
/////////// ��û�еĻ�/////////
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
int taiji(object me, object victim, object weapon, int damage)
{
        int n = random(2);

        if( damage == RESULT_DODGE )
        {
                if( n == 0 && me->query_skill_mapped("unarmed") == "taiji-quan"
                && me->query_skill_prepared("unarmed") == "taiji-quan" )
                {
                        set_temp("double_attack", 1, me);
                        weapon->unequip();
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        weapon->wield();
                }
                else
                {
                        set_temp("double_attack", 1, me);
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        message_combatd("\n$N���ǽ������֣�����ǰ��������ԲȦ��$n��$P�������࣬��סȫ�����ް�ֿ�϶��\n"NOR,me,victim);
                }
                delete_temp("double_attack", me);
                return 1;
        }
        else if( damage <= 0 )
        {
                message_combatd("$p����$P�����й��ྡྷ������Լ��ֱ��������顣\n", me, victim);
//              if( !victim->is_busy() )
//              victim->start_busy(1+random((int)(me->query_skill("force")/150)));
                addn("neili", -(me->query_skill("force")/10), victim);
        }
        return 1;
}
int raozhi(object me, object victim, object weapon, int damage)
{
        int level = (int)me->query_skill("taiji-jian", 1)/2;
        string ductile;

        if( !objectp(weapon) ) return 1;
        ductile=query("id", weapon);
        addn_temp("raozhi_attack", 1, me);

        if( damage == RESULT_DODGE && query_temp("raozhi_attack", me)<3 )
        {
                addn_temp("apply/attack", level, me);

                if( query_temp("raozhi_attack", me) == 1 ||
                        ( (ductile == "bailong jian" || ductile == "ruanjian"
                                 || ductile == "shuixinjian") && query("neili", me)>500) )
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);
                else delete_temp("raozhi_attack", me);

                addn_temp("apply/attack", -level, me);
                return 1;
        }
        else delete_temp("raozhi_attack", me);
        return 1;
}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("taiji-jian", 1) < 100 ||
            !(m_weapon=query_temp("weapon", me)) ||
            !living(me) || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("taiji-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "һ�����е�" + m_weapon->name() +
                                            HIC "��������һ��ԲȦ����Ȼ��$N" +
                                            HIC "�Ĺ���ȫȻ��ա�\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "����" + m_weapon->name() + HIC
                                            "��������ָ��$N" HIC "�����е�������\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "�ζ����е�" + m_weapon->name() +
                                            HIC "����ס�ı�ý��ƣ���$N"
                                            HIC "��ȫ�޷���׽��������\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "һ�����е�" + m_weapon->name() +
                                 HIY "��������һ��ԲȦ��$N"
                                 HIY "��Ҳ������������ֱ�룬��Ϯ$n"
                                 HIY "��\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "����" + m_weapon->name() + HIY "������"
                                 HIY "��ָ��$N" HIY "�����е�����������$N"
                                 HIY "����һ�䣬�������̲���Ϊ������\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "�ζ����е�" + m_weapon->name() +
                                 HIY "����ס�ı�ý��ƣ�Ȼ��$N"
                                 HIY "������񣬾���������˿������$n"
                                 HIY "���Ի�\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("taiji-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"taiji-jian/" + action;
}
int help(object me)
{
        write(HIC"\n̫��������"NOR"\n");
        write(@HELP

    ��̫��ȭ��ѧԭ����ͬ��������������ʦ����ʱ�չ���ã���
��Բ�ڣ����޹̶���ʽ������������ʤ���У��������Ǻ������ӡ�
̫����������һ����Ϊ�����൱��̫��ȭ�����������Ͻ���

        ѧϰҪ��
                ̫��ȭ20��
                ̫����20��
                ����100
HELP
        );
        return 1;
}
