// Written by Lonely@nitan.org
// pixie-jian

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return force == "riyue-xinfa" || force == "riyue-guanghua" || force == "kuihua-xinfa";
}

string *dodge_msg = ({
        "ͻȻ֮�䣬��Ӱ���ϣ�$n��󻬳����࣬��ʱ�ֻص���ԭ�أ������$N��һ�С�\n",
        "$n�ֱۻ�ת����$N������һ�ƣ�˳������һ�ԡ�\n",
        "$n�����������$N������Ѹ���ޱȵ�һ����˳������һ�ԡ�\n",
        "$n����Ʈ����������ȣ�ת�˼�ת���Ʋ���$N����󣬶����$N��һ�С�\n",
        "$Nֻ����ǰһ�����ƺ�����$n����һ�ϣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
        "$N�۾�һ����$n��û����Ӱ��ͻȻ$n���������һ��$N��ͷ������Ծ����\n",
        "$n��ȻһЦ������֮����$N����֪����Ǻã�ͣס�˹�����\n",
});

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", });

mapping *weapon_action = ({
([      "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
        "force" : 160,
        "attack": 40,
        "parry" : 30,
        "dodge" : 120,
        "damage": 150,
        "lvl" : 0,
        "skill_name" : "��Ӱ����",
        "damage_type":  "����"
]),
([      "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",
        "force" : 180,
        "attack": 50,
        "parry" : 30,
        "dodge" : 135,
        "damage": 160,
        "lvl" : 20,
        "skill_name" : "�Լ�С��",
        "damage_type":  "����"
]),
([      "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
        "force" : 225,
        "attack": 60,
        "parry" : 35,
        "dodge" : 155,
        "damage": 170,
        "lvl" : 40,
        "skill_name" : "������",
        "damage_type":  "����"
]),
([      "action":"$NͻȻ���з�һ�䣬$w�����������ʽ������ס�$n����֮�з������",
        "force" : 230,
        "attack": 70,
        "parry" : 40,
        "dodge" : 160,
        "damage": 180,
        "lvl" : 60,
        "skill_name" : "�з�һ��",
        "damage_type":  "����"
]),
([      "action":"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ���$n�����",
        "force" : 240,
        "attack": 80,
        "parry" : 50,
        "dodge" : 170,
        "damage": 200,
        "lvl" : 80,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�",
        "force" : 260,
        "attack": 70,
        "parry" : 40,
        "dodge" : 165,
        "damage": 220,
        "lvl" : 100,
        "skill_name" : "������ǰ",
        "damage_type":  "����"
]),
([      "action":"$N�ȵ������ã������㼴�γ�$w�����ִ̳�������ת����ȥ",
        "force" : 300,
        "attack": 90,
        "parry" : 45,
        "dodge" : 180,
        "damage": 230,
        "lvl" : 120,
        "skill_name" : "���ִ̳�",
        "damage_type":  "����"
]),
([      "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
        "force" : 340,
        "attack": 80,
        "parry" : 40,
        "dodge" : 185,
        "damage": 250,
        "lvl" : 140,
        "skill_name" : "��ǰһ��",
        "damage_type":  "����"
]),
([      "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ������$wֱָ$n��$l",
        "force" : 380,
        "attack": 100,
        "parry" : 50,
        "dodge" : 190,
        "damage": 270,
        "lvl" : 160,
        "skill_name" : "�����",
        "damage_type":  "����"
]),
([      "action":"$N��س嵽$n��ǰ������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��",
        "force" : 410,
        "attack": 130,
        "parry" : 55,
        "dodge" : 210,
        "damage": 300,
        "lvl" : 180,
        "skill_name" : "ֱ������",
        "damage_type":  "����"
]),
([      "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£�����$w����$n��$l",
        "force" : 440,
        "attack": 130,
        "parry" : 50,
        "dodge" : 230,
        "damage": 320,
        "lvl" : 200,
        "skill_name" : "����Ծ��",
        "damage_type":  "����"
]),
([      "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n",
        "force" : 480,
        "attack": 140,
        "parry" : 60,
        "dodge" : 270,
        "damage": 340,
        "lvl" : 220,
        "skill_name" : "��֦�Ͱ�",
        "damage_type":  "����"
]),
});

mapping *unarmed_action = ({
([      "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
        "force" : 100,
        "attack": 40,
        "parry" : 20,
        "dodge" : 70,
        "damage": 50,
        "lvl" : 0,
        "skill_name" : "��Ӱ����",
        "damage_type":  "����"
]),
([      "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",
        "force" : 120,
        "attack": 50,
        "parry" : 30,
        "dodge" : 65,
        "damage": 60,
        "lvl" : 12,
        "skill_name" : "�Լ�С��",
        "damage_type":  "����"
]),
([      "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
        "force" : 125,
        "attack": 60,
        "parry" : 35,
        "dodge" : 85,
        "damage": 70,
        "lvl" : 25,
        "skill_name" : "������",
        "damage_type":  "����"
]),
([      "action":"$NͻȻ���з�һ�䣬�ֱۺ����������ʽ������ס�$n����֮�з������",
        "force" : 130,
        "attack": 70,
        "parry" : 40,
        "dodge" : 60,
        "damage": 80,
        "lvl" : 5,
        "skill_name" : "�з�һ��",
        "damage_type":  "����"
]),
([      "action":"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ���$n�����",
        "force" : 140,
        "attack": 80,
        "parry" : 50,
        "dodge" : 70,
        "damage": 100,
        "lvl" : 35,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ���ָ�漴�̳�",
        "force" : 160,
        "attack": 70,
        "parry" : 40,
        "dodge" : 65,
        "damage": 120,
        "lvl" : 45,
        "skill_name" : "������ǰ",
        "damage_type":  "����"
]),
([      "action":"$N�ȵ������ã������㼴���ִ̳�һָ������ת����ȥ",
        "force" : 200,
        "attack": 90,
        "parry" : 45,
        "dodge" : 80,
        "damage": 130,
        "lvl" : 55,
        "skill_name" : "���ִ̳�",
        "damage_type":  "����"
]),
([      "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
        "force" : 190,
        "attack": 80,
        "parry" : 40,
        "dodge" : 85,
        "damage": 150,
        "lvl" : 65,
        "skill_name" : "��ǰһ��",
        "damage_type":  "����"
]),
([      "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ�����ƺ�������$n��$l",
        "force" : 180,
        "attack": 100,
        "parry" : 50,
        "dodge" : 70,
        "damage": 170,
        "lvl" : 75,
        "skill_name" : "�����",
        "damage_type":  "����"
]),
([      "action":"$N��س嵽$n��ǰ��ָ��ֱ��$n���ۣ�$n��æ�мܣ�����$N������ͻȻת��",
        "force" : 250,
        "attack": 130,
        "parry" : 55,
        "dodge" : 74,
        "damage": 200,
        "lvl" : 85,
        "skill_name" : "ֱ������",
        "damage_type":  "����"
]),
([      "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£����ƿ���$n��$l",
        "force" : 340,
        "attack": 130,
        "parry" : 50,
        "dodge" : 80,
        "damage": 220,
        "lvl" : 94,
        "skill_name" : "����Ծ��",
        "damage_type":  "����"
]),
([      "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ����һ������$n",
        "force" : 400,
        "attack": 140,
        "parry" : 60,
        "dodge" : 110,
        "damage": 240,
        "lvl" : 120,
        "skill_name" : "��֦�Ͱ�",
        "damage_type":  "����"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "dodge" ||
               usage == "parry" ||
               usage == "force" ||
               usage == "unarmed";
}

int double_attack() { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("pixie-jian", 1);
        return lvl * lvl * 17 * 15 / 100 / 200;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(weapon_action) - 1; i >= 0; i--)
                if (level >= weapon_action[i]["lvl"])
                        return weapon_action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -80;
        int p_e2 = -60;
        int f_e1 = 150;
        int f_e2 = 230;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl;
        mapping *action;

        if (objectp(weapon))
                action = weapon_action;
        else
                action = unarmed_action;

        ttl = sizeof(action);
        lvl = (int) me->query_skill("pixie-jian", 1);
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
                "damage_type" : action[seq]["damage_type"],
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if( query("character", me) == "��������" ||
            query("character", me) == "������" )
                return notify_fail("�����а��������а���������𼺣����������á�\n");

        if( query("gender", me) == "Ů��" &&
            !query("special_skill/ghost", me) )
                return notify_fail("�Թ�����û��˵��Ů�˿�����ϰ�������䡣\n");

        if( query("gender", me) == "����" &&
            !query("special_skill/ghost", me) )
        {
                me->receive_wound("qi", 50);
                return notify_fail(HIR "\n������������а��������ʱֻ����Ϣ��Ȼ��"
                                   "�ң���������\n" NOR);
        }

        /*
        if( !query("family/family_name", me) ||
            query("family/family_name", me) != "�������" )
                return notify_fail("��а����ֻ��������̵��˷�����ᡣ\n");
        */

        if( query("int", me)<34 )
                return notify_fail("������ʲ��㣬�޷�����а���������⡣\n");

        if( query("dex", me)<32 )
                return notify_fail("������������������������а������\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�����������̫ǳ���޷�����а������\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("��Ļ����Ṧ����̫ǳ���޷�����а������\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("��Ļ�����������̫ǳ���޷�����а������\n");

        if (me->query_skill("sword", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("��Ļ��������������ޣ��޷���������ı�а������\n");

        if (me->query_skill("dodge", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("��Ļ����Ṧ�������ޣ��޷���������ı�а������\n");

        if (me->query_skill("parry", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("��Ļ����м��������ޣ��޷���������ı�а������\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("��Ļ���ȭ���������ޣ��޷���������ı�а������\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("pixie-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("pixie-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$N" HIR "�۾�һ����$n" HIR "��û����"
                                            "Ӱ��ͻȻ$n" HIR "���������һ��$N" HIR "��"
                                            "ͷ������Ծ����\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "��ǰһ�����ƺ�����$n" HIR "��"
                                            "��һ�Σ����漴�ּ�$n" HIR "�ص�ԭ�أ�ȴ��"
                                            "��δ�뿪��\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "����Ʈ����������ȣ�ת�˼�ת"
                                            "���Ʋ���$N" HIR "����󣬶����$N" HIR "��"
                                            "һ�С�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "ͻȻ���Ӱ���Σ�$n" HIR "��󻬳�����"
                                            "����ʱ�ֻص���ԭ�أ������$N" HIR "��һ��"
                                            "��\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$N" HIY "�۾�һ����$n" HIY "��û����Ӱ"
                                 "������$N" HIY "��ͨ����˿����Ϊ���ң�����"
                                 "���С�\n" NOR;
                        break;
                case 1:
                        result = HIY "$N" HIY "��ǰһ�����ƺ�����$n" HIY "��"
                                 "��һ�Ρ�$N" HIY "һ����Ц����˲�俴��������"
                                 "ʵ��\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "����Ʈ����������ȣ�ת�˼�ת��"
                                 "����$N" HIY "��Ҳ�����������о�ֱ������\n"
                                 NOR;
                        break;
                default:
                        result = HIY "ͻȻ���Ӱ���Σ�$n" HIY "��󻬳����࣬"
                                 "����$N" HIY "����˼����׷���ϣ�����������"
                                 "����\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("pixie-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 40;
        if (lvl < 200) return 60;
        if (lvl < 250) return 80;
        if (lvl < 300) return 100;
        if (lvl < 350) return 120;
        return 130;
}


void cimu_end(object me, object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "Ĩ��Ĩ���ŵ�"
                                        HIR "��Ѫ" HIC "�������ܿ�"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIR "������Ĩ������ǰ��"
                                            "��Ѫ���ܿ����ˡ�\n" NOR);
                }
                delete_temp("block_msg/all", target);
        }
        return;
}

void poyuan_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->clear_condition("no_perform");
        }
        return;
}

void exert_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е�����Ѩ��������ʹ�����ɶ��ˡ�\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        // ��а��Ӱ��Ч
        if( random(20)<5 && query_temp("pixie-jian/pfm_jian", me) )
        {
                switch(random(8))
                {
                        case 0:
                                if( !query_temp("block_msg/all", victim) )
                                {
                                        set_temp("block_msg/all", 1, victim);
                                        call_out("cimu_end", 20, me, victim);
                                        message_combatd(HIR "$N" HIR "ֻ��˫Ŀһ���ʹ����ǰһ�ڣ���ʲô"
                                               "Ҳ�������ˣ���ʱ����ʹ��������\n" NOR, victim);
                                }
                                break;
                        case 1:
                                if (! victim->query_condition("no_perform"))
                                {
                                        victim->apply_condition("no_perform", 5);
                                        call_out("poyuan_end", 15, me, victim);
                                        message_combatd(HIR "$N" HIR "ֻ����ǰ��âһ���������漴ȫ��һ��"
                                                "��ʹ������Ѫ�������������\n$N��Ȼ��һ��������"
                                                "�����������������ƻ�ɢһ�㣬ȫȻ�޷����ơ�\n" NOR, victim);
                                }
                                break;
                        case 2:
                                set("jiali", 0, victim);
                                break;
                        case 3:
                                if (! victim->query_condition("no_exert"))
                                {                       
                                        victim->apply_condition("no_exert", 1);
                                        call_out("exert_end", 30, me, victim);
                                        message_combatd(HIR "$N" HIR "ֻ��������ˣ��漴ȫ��һ��"
                                                "��ʹ���������ˡ�\n$N��Ȼ��һ��������"
                                                "����������Ѩ����ʹ�ޱȡ�\n" NOR, victim);
                                }
                                break;
                        default:
                                if (! victim->is_busy())
                                        victim->start_busy(8);                          
                                break;
                }
        }
        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("pixie-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || ! living(victim)
           || random(3) > 0
           || damage_bonus < 120
           || query_temp("px_link", me)
           || query_temp("pixie-jian/hit_msg", me)
           || query("neili", me)<300
           || query_temp("action_flag", me) == 1
           || me->query_skill("pixie-jian", 1) < 120)
                return 0;

        if( query_temp("pixie-jian/pfm_jian", me) ) tell_object(me,HIG"---------------------------=\n"NOR);
        // ������ʹ��PfmʱѶϢ�ظ�
        if( !query_temp("pixie-jian/hit_msg", me) )
                message_combatd(HIW "\n��ʱ��ֻ��$N" HIW "���Ȱ�������ϣ�" + name +
                               HIW "ָָ��㣬����ҹ�����ǣ���������$n" HIW "��\n"
                               NOR, me, victim);

        //me->start_busy(1 + random(attack_time / 10));
        addn("neili", -200, me);
        set_temp("px_link", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        delete_temp("px_link", me);
        return 1;
}

int practice_skill(object me)
{
        return notify_fail(HIC "��а����ֻ��ͨ����ϰ����а���ס��򡸿���"
                           "���䡹��ѧϰ��\n" NOR);
}

int difficult_level()
{
        return 800;
}

string perform_action_file(string action)
{
            return __DIR__"pixie-jian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"pixie-jian/exert/" + action;
}
/*
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;

        if( userp(me) && !query("reborn/times", me) )
                return;

        skill = me->query_skill("pixie-jian", 1);
        if( random(skill)>400 && objectp(weapon=query_temp("weapon", me)) )
        {
                enemy = me->query_enemy();
                if (! sizeof(enemy)) return;
                addn_temp("str", skill/10, me);
                addn_temp("dex", skill/10, me);
                // �����е��˾��Զ����й���
                for (i = 0; i < sizeof(enemy); i++)
                {
                        for (j = 0; j < (skill / (60 * sizeof(enemy))); j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),0);
                                }
                        } else break;
                }
                addn_temp("str", -skill/10, me);
                addn_temp("dex", -skill/10, me);
        }
}
*/

int help(object me)
{
        write(HIC"\n��а������"NOR"\n");
        write(@HELP

    Ҫ˵��а��������Ҫ�ӡ��������䡷̸��

    ���������䡷��һλ�¹�����������һλ����֣�Ϊʲ���ڻ�
������̫�࣬����˭Ҳ��֪������춱��������ص��书��ȴ�Ǿ���
֮�������ٶ�������ʼ����һ���ܾ������ɡ�������ǰ���ⲿ����
Ϊ����������������Ժ���á���ʱ���������·��ɺ�Ҷ��ʦ������
һλ���Ǵ�۵��˲���������������书���ԣ��õ����ɱ�����
�����书���ǡ������о����ֱ꣬��������ʼ��û����ʼ��������
���书��

    һ�ջ�ɽ�ɵ�����Ͳ��ӷ嵽�������������ͣ�͵����������
���䡷����ʱ�Ҵ�֮�ʣ����˲���ͬʱ�ı�ȫ�飬���¶��˷ֶ���
һ�˶�һ�룬�����ص���ɽ����ͬ�������֡����϶��˽����й���
һ��ӡ֤����Ȼţͷ�������죬ȫȻ�ϲ����������˶����ŶԷ���
�����飬ֻ���Լ����ǵĲ��ǶԵġ���ɽ�Ľ�������֮���ɴ˶���

    ��Ҷ��ʦ���÷��ִ��£���֪���ⲿ����������ѧ��������
���������֮���������ѵĻ��ǵ�һ�أ�ֻ����һ���ܴ�ͨ����
����Ҳûʲ�ᡣ��һ��ֻҪ�а�����ʱ�������ˡ���Ҷ����
��ǲ������Ӷ�Ԫ��ʦǰ����ɽ��Ȱ�����̶�λ��������ϰ������
����ѧ��

    ��Ԫ��ʦ�ϵû�ɽ�����̶��˶��������ྴ������˽�ġ�����
���䡷��һ������Ǹ�⣬һ��ȴ�Ծ���������ѧ������̡��ⲻ֪
��Ԫ���Ǻ�Ҷ�ĵ�����ӣ������е���ѧȴδ�ɴ��ڡ����¶�Ԫ��
ʦ���������������Ǳ��о��ģ���ڼ��Խ��ͣ�����ȴ���Լ��¡�
��Ԫ��ʦ�书�������������Ǿ�������֮�ˣ�����һ�侭�ģ��㼺
�����Ｘ�䣬��ȻҲ˵��ͷͷ�ǵ���

    �������̶������ǵı��Ѳ��࣬��������һת���������ִ���
�ۿۡ���Ԫ��ʦ�ڻ�ɽ��ס�˰��գ�������𣬵��Ӵ�ȴҲû�ٻ�
������������ȥ�����ú�Ҷ��ʦ���յ���Ԫ��ʦ��һͨ���ţ�˵��
���������֣����⻹�ף�����Ŀ�ټ�ʦ�����ơ�

    �����һ���£���ɽ�ɵ���͵�����������䡷֮��Ҳ������⡣
������ʱ��ħ��ʮ����������ɽ���ڻ�ɽ����һ����ս��ħ��ʮ��
�϶��������ˣ���ܶ�ȥ��������Ͳ��ӷ����˾�����һ���б�����
��������¼���������䡷Ҳ��ħ�̶���ȥ��

    ��Ԫ��ʦ����֮�ᣬ����ԭ�գ��������ߵ�����ȡ��Զͼ��Ȣ
�����ӣ������ھ֣��ڽ����Ϻ�����Ҹ���һ����ҵ��

    ���������µĺ�Ҷ��ʦ԰��֮ʱ���ټ����˵��ӣ�˵���ⲿ��
���ǰ��������㼴����Ͷ��¯�л𻯡���Ҷ˵���ⲿ��ѧ���ž�
�������������ؼ�֮���������׫���˲�δ����Ϊ��ͨ��͸��
���µ�����̫�ࡣ�����ǵ�һ���ѹ��������ѹ�����ֱ�ǲ��ܹ���
�ɹ�������������ʵ������֮����

    ��Զͼ�ı�а�������Ǵӡ��������䡷��ƪ��������书����
��ϵ��ͬԴ����а��������ʮ��·����һ���Ӳ��⴫������ʹ�ô�
����֮�˸�������Ѹ�ݹ��죬������˵�֪���з�����Ŀ��ֻ֪��
����ʽ�˷�����˼����Զͼ����¼�ġ���а���ס���������Լ���
���ͣ��ʽ�ħ�����صġ��������䡷�����ţ�������Щ���ݡ�����
�����ϰ�˹�������ѭ��������֮�������εõ�������������
�ţ���һֱ�ǽ����ϱܶ���̸�����ܡ���й¶���أ�������ɱ��֮
����

        ѧϰҪ��
                �Թ���̫��
HELP
        );
        return 1;
}
