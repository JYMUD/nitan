#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
        "ͻȻ֮�䣬΢�紵����$n��Ӱһ�����·�û���κζ�����ȴ�����$N��һ�С�\n",
        "$n����һ����$N����һ�ɾ��������������գ��һ���ۣ��ٿ�ʱ��$n�Ѿ����˸�λ�á�\n",
        "$n��ָһ�㣬$Nȫ��һ�飬$n�����⵽һ�ԡ�\n",
        "$n����Ʈ�����������������Ʈ��������Ʈ��$N����󣬶����$N��һ�С�\n",
        "$Nֻ����ǰһ�����ƺ�����$n����һ�ϣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
        "$N�۾�һ����$n��û����Ӱ��ͻȻ$n���������һ��$N��ͷ������Ծ����\n",
        "$n����һЦ���߹�֮����$N����֪����Ǻã�ͣס�˹�����\n",
});

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", }); 

mapping *action = ({
([          "action":"ͻȻ֮�䣬΢�������$N��󻬳����࣬��ʱ�ֻص���ԭ��", // ����
            "force" : 1600,                                                   // ������
            "attack": 400,                                                    // ���е�
            "parry" : 300,                                                         // ������ҿ������м����мܵ���
            "dodge" : 1200,                                                          // �Ṧ������ͬparry
            "damage": 1500,                                                         // �˺���
            "lvl" : 0,                                                         // ��������Ҫ��ĵȼ�
            "skill_name" : "Ʈ��׷��",                                       // ��������
            "damage_type":  "����"                                           // �˺�����
]),
([          "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",    
            "force" : 1800,
            "attack": 500,
            "parry" : 300,
            "dodge" : 1350,
            "damage": 1600,
            "lvl" : 20,
            "skill_name" : "��Ȼ����",
            "damage_type":  "����"
]),
([          "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
            "force" : 2250,
            "attack": 600,
            "parry" : 350,
            "dodge" : 1550,
            "damage": 1700,
            "lvl" : 40,
            "skill_name" : "Ʈ��Ϸ��",
            "damage_type":  "����"
]),
([          "action":"$NͻȻ���з�һ�䣬$w�����������ʽ������ס�$n����֮�з������",
            "force" : 2300,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1600,
            "damage": 1800,
            "lvl" : 60,
            "skill_name" : "������",
            "damage_type":  "����"
]),
([          "action":"$N����Ʈ��������������ת�˼�ת���Ʋ���$n�����",
            "force" : 2400,
            "attack": 800,
            "parry" : 500,
            "dodge" : 1700,
            "damage": 2000,
            "lvl" : 80,
            "skill_name" : "����Ʈ��",
            "damage_type":  "����"
]),
([          "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�",
            "force" : 2600,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1650,
            "damage": 2200,
            "lvl" : 100,
            "skill_name" : "ӭ�����",
            "damage_type":  "����"
]),
([          "action":"$N�ȵ������ã������㼴�γ�$w�����ִ̳�������ת����ȥ",
            "force" : 3000,
            "attack": 900,
            "parry" : 450,
            "dodge" : 1800,
            "damage": 2300,
            "lvl" : 120,
            "skill_name" : "��������",
            "damage_type":  "����"
]),
([          "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
            "force" : 3400,
            "attack": 800,
            "parry" : 400,
            "dodge" : 1850,
            "damage": 2500,
            "lvl" : 140,
            "skill_name" : "Ʈ������",
            "damage_type":  "����"
]),
([          "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ������$wֱָ$n��$l",
            "force" : 3800,
            "attack": 1000,
            "parry" : 500,
            "dodge" : 1900,
            "damage": 2700,
            "lvl" : 160,
            "skill_name" : "��������",
            "damage_type":  "����"
]),
([          "action":"$N��س嵽$n��ǰ������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��",
            "force" : 4100,
            "attack": 1300,
            "parry" : 550,
            "dodge" : 2100,
            "damage": 3000,
            "lvl" : 180,
            "skill_name" : "�����ﲨ",
            "damage_type":  "����"
]),
([          "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£�����$w����$n��$l",
            "force" : 4400,
            "attack": 1300,
            "parry" : 500,
            "dodge" : 2300,
            "damage": 3200,
            "lvl" : 200,
            "skill_name" : "�������",
            "damage_type":  "����"
]),
([          "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n",
            "force" : 4800,
            "attack": 1400,
            "parry" : 600,
            "dodge" : 2700,
            "damage": 3400,
            "lvl" : 220,
            "skill_name" : "��֦��ҡ",
            "damage_type":  "����"
]),
});

// valid_enable()�������ظü��ܿɼ���������
int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "dodge" ||
               usage == "parry" ||
               usage == "unarmed";
}

// ����1��ʾ���ҿ���һ����ʽ
int double_attack() { return 1; }

// �������˵�˰ɣ���yanjiu��learn��ʱ����õĺ���
int valid_learn(object me)
{
        if (wiz_level(me)==0)
                return notify_fail("������ʦ�޷�ѧϰ�׻��񽣡�\n");
  
        if( query("int", me)<100 )
                return notify_fail("������ʲ��㣬�޷�����׻��񽣵����⡣\n");

        if( query("dex", me)<100 )
                return notify_fail("�����������������������׻��񽣡�\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�����������̫ǳ���޷�����׻��񽣡�\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("��Ļ����Ṧ����̫ǳ���޷�����׻��񽣡�\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("��Ļ�����������̫ǳ���޷�����׻��񽣡�\n");

        if (me->query_skill("sword", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("��Ļ��������������ޣ��޷�����������׻��񽣡�\n");

        if (me->query_skill("dodge", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("��Ļ����Ṧ�������ޣ��޷�����������׻��񽣡�\n");

        if (me->query_skill("parry", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("��Ļ����м��������ޣ��޷�����������׻��񽣡�\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("��Ļ���ȭ���������ޣ��޷�����������׻��񽣡�\n");

        return 1;
}

// ����Ǳ�׼��������Ҫ�޸�
string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

// ����Ǳ�׼��������Ҫ�޸�
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yh-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

// ����������Ϣ
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

// ���Է����к���õĺ��������罫���м���Ϊ�мܻ��Ṧ
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yh-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yh-jian", 1);

        if (ap / 2 + random(ap) < dp)
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
                        result += (["msg" : HIR "$n" HIR "����Ʈ�����������������Ʈ��"
                                            "��Ʈ��$N" HIR "����󣬶����$N" HIR "��"
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
                        result = HIY "$n" HIY "����Ʈ�����������������Ʈ����"
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

// �����м���Ϊ�Ṧʱ���ṦЧ��
int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yh-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 60;
        if (lvl < 150) return 80;
        if (lvl < 200) return 120;
        if (lvl < 250) return 160;
        if (lvl < 300) return 200;
        if (lvl < 350) return 240;
        return 300;
}

// �����жԷ�ʱ���õĺ���
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "����" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("yh-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || victim->is_busy()
           || damage_bonus < 120
            || query("neili", me)<300
            || query_temp("action_flag", me) == 0
           || me->query_skill("yh-jian", 1) < 120)
                return 0;

        // ������ʹ��PfmʱѶϢ�ظ�
        if( !query_temp("yh-jian/hit_msg", me) )
                message_vision(HIW "\n��ʱ��ֻ��$N" HIW "���Ȱ�������ϣ�" + name +
                               HIW "ָָ��㣬����ҹ�����ǣ���������$n" HIW "��\n"
                               NOR, me, victim);

        me->start_busy(1 + random(attack_time));
        addn("neili", -attack_time*20, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        return 1;
}

// ����ϰ����ʱ���õĺ���
int practice_skill(object me)
{
        return notify_fail(HIC "�׻���ֻ����[С���Թ�]ѧϰ��\n" NOR);
}

// ���е�ѧϰ�Ѷ�
int difficult_level()
{
        return 15000;
}

// ���е�perform�ļ�λ��__DIR__����ǰĿ¼��
string perform_action_file(string action)
{
        return __DIR__"yh-jian/" + action;
}