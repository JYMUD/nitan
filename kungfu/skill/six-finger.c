// six-fingers.c ������
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string main_skill() { return "yinyang-shiertian"; }

mapping *action = ({
([      "name":   "���̽�",
        "action": "$N˫��Ĵָͬʱ����������������죬��" HIW "���̽�" NOR "������ʯ��"
                  "�쾪���������",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 0,
        "weapon" : HIW "���̽���" NOR,
        "damage_type":  "����"
]),
([      "name":   "���̽�",
        "action": "$N��Ĵָһ����������ָ������ʹ�����ɣ���" HIW "���̽�" NOR "������"
                  "��ŭ����ӿ��",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 10,
        "weapon" : HIW "���̽���" NOR,
        "damage_type":  "����"
]),
([      "name":   "���̽�",
        "action": "$N��Ĵָ���ӣ���" HIW "���̽�" NOR "��������һ����īɽˮ���ݺ���б"
                  "����·�۾�",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 20,
        "weapon" : HIW "���̽���" NOR,
        "damage_type":  "����"
]),
([      "name":   "���̽�",
        "action": "$N˫��Ĵָͬʱ�������" HIW "���̽�" NOR "���󿪴��أ����ɺ�ΰ��ÿ"
                  "һ�����з������֮��",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 30,
        "weapon" : HIW "���̽���" NOR,
        "damage_type":  "����"
]),
([      "name":   "������",
        "action": "$Nʳָ����������԰ת����" HIW "������" NOR "��һ����һ���Ĵ̳�����"
                  "��Ѹ�٣������ݺ�",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 40,
        "weapon" : HIW "��������" NOR,
        "damage_type":  "����"
]),
([      "name":   "������",
        "action": "$N�������٣�����ʳָ������״�������" HIW "������" NOR "����ʱ�ó�"
                  "����ָӰ",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 50,
        "weapon" : HIW "��������" NOR,
        "damage_type":  "����"
]),
([      "name":   "������",
        "action": "$NĴָһ����ʳָ�漴����������������죬���������������" HIW "��"
                  "����" NOR "������̳�",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 60,
        "weapon" : HIW "��������" NOR,
        "damage_type":  "����"
]),
([      "name":   "������",
        "action": "$N��ʳָ���ˡ�" HIW "������" NOR "��֮���ν�����ȴ��������ָ������"
                  "��Χ��һ��һ��",
        "force" : 480,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 70,
        "weapon" : HIW "��������" NOR,
        "damage_type":  "����"
]),
([      "name":   "�г彣",
        "action": "$N������ָһ������" HIW "�г彣" NOR "����ǰ�̳��������ĵ�����Ȼ��"
                  "�죬���ν���ֱָ$n",
        "force" : 560,
        "attack": 155,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 80,
        "weapon" : HIW "�г彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�г彣",
        "action": "$N����ָ����һ�̣���" HIW "�г彣" NOR "���εض��𣬽�����ָ����һ"
                  "���������������㿳��",
        "force" : 560,
        "attack": 145,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 90,
        "weapon" : HIW "�г彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�г彣",
        "action": "����ʯ֮�䣬$N��Ȼ���ƣ����ֶ�Ȼ̽������ָ��" HIW "�г彣" NOR
                  "����$nһ��",
        "force" : 560,
        "attack": 135,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 100,
        "weapon" : HIW "�г彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�س彣",
        "action": "$N��������ָ�������" HIW "�س彣" NOR "����·׾�͹��ӣ�һ���ۻ���"
                  "�ȵ������ĵ�����",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 110,
        "weapon" : HIW "�س彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�س彣",
        "action": "$N����б�У�����ָ��" HIW "�س彣" NOR "�����������ָ���Ѷ�׼$n��"
                  "����һ��ǿ�ҵľ���",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 120,
        "weapon" : HIW "�س彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�س彣",
        "action": "$N����ָ����һ�ӣ���������һ����׾�͹��ӵġ�" HIW "�س彣" NOR "��"
                  "������$nֱ�����",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 130,
        "weapon" : HIW "�س彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "����",
        "action": "$N����Сָһ�죬һ���������ٳ�Ѩ�м����������" HIW "����" NOR
                  "��������磬ָ��$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 140,
        "weapon" : HIW "������" NOR,
        "damage_type":  "����"
]),
([      "name":   "����",
        "action": "����$N����Сָһ�죬һ��������$P�ٳ�Ѩ�м��������һ�ɡ�" HIW "��"
                  "��" NOR "����ʱ����$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 150,
        "weapon" : HIW "������" NOR,
        "damage_type":  "����"
]),
([      "name":   "�ٳ彣",
        "action": "$N����Сָ������������ٳ�Ѩ������������" HIW "�ٳ彣" NOR "������"
                  "��䣬쬵Ĵ���$n",
        "force" : 480,
        "attack": 150,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 160,
        "weapon" : HIW "�ٳ彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�ٳ彣",
        "action": "$N��������ǰ�������Сָ��һ�С�" HIW "�ٳ彣" NOR "�������ص���$n"
                  "�������Ѩ",
        "force" : 530,
        "attack": 170,
        "dodge" : 90,
        "parry" : 95,
        "damage": 260,
        "lvl"   : 170,
        "weapon" : HIW "�ٳ彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�ٳ彣",
        "action": "$NСָһ������" HIW "�ٳ彣" NOR "����ʽ���ֻ���������������ͬ����"
                  "һ�㣬Ʈ������",
        "force" : 430,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 180,
        "weapon" : HIW "�ٳ彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�ٳ彣",
        "action": "$Nһ�С�" HIW "�ٳ彣" NOR "����������ת�޶��Σ�����������˹�����"
                  "����$n",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 190,
        "weapon" : HIW "�ٳ彣��" NOR,
        "damage_type":  "����"
]),
([      "name":   "�ٳ彣",
        "action": "$N����Сָһ�ӣ�һ�С�" HIW "�ٳ彣" NOR "�����̴��ƿմ̳�������"
                  "�񻨴̻�һ��",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 200,
        "weapon" : HIW "�ٳ彣��" NOR,
        "damage_type":  "����"
]),
});

mapping sub_skills = ([
        "shaoshang-sword"  : 120,
        "shangyang-sword"  : 120,
        "zhongchong-sword" : 120,
        "guanchong-sword"  : 120,
        "shaoze-sword"     : 120,
        "shaochong-sword"  : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "���ϻ���") && (!query("reborn/times", me) || member_array("���ϻ���", query("reborn/fams", me)) == -1) )
        {
                tell_object(me, "���о���һ�����ֻ���Ĳ��Ƕ��ϻ���ĸ����޷�������а���\n");
                return 0;
        }

        if( query("int", me)<32 || me->query_int()<44 )
        {
                tell_object(me, "��������ϣ�ֻ�����ֽ�������ǣ����������������ԣ���"
                                "�������һ��\n");
                return 0;
        }

        if( query("con", me)<26 || me->query_con()<39 )
        {
                tell_object(me, "��������ϣ�ֻ��ȫ�������Ҵܣ���ð���ǣ�������������"
                                "�����ײſ���������\n");
                return 0;
        }

        if( query("gender", me) == "����" )
        {
                tell_object(me, "���޸����ԣ������������������������񽣡�\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "����������񽣼�����£��������о�һ��ѧ�ʿ��ܸ��а�"
                                "����\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 200)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }

        if ((int)me->query_skill("force") < 300)
        {
                tell_object(me, "��������ϣ��������ѣ��Լ����ڹ�ˮƽ�������д���ߡ�\n");
                return 0;
        }

        if( query("max_neili", me)<5000 )
        {
                tell_object(me, "��������ϣ������᲻��������������Ӧ�ü�������������\n");
                return 0;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 100)
        {
                tell_object(me, "��������ϣ����������ѧ��������һ����ø�����������\n");
                return 0;
        }

        if (random(10) < 5)
        {
                tell_object(me, "��������񽣵İ����������򣬻���������һ�ξ��ܹ��ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIY "һ�󷲳�����ӿ����ͷ���㼸��������̾����ǰ�������ֳ�����"
                            "������\n���Ǽ䣬������ͨ�������񽣡�\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}
int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�������񽣱�����֡�\n");

        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "���ϻ���") &&
            (!query("reborn/times", me) || member_array("���ϻ���", query("reborn/fams", me)) == -1))
                return notify_fail("���о���һ�����ֻ���Ĳ��Ƕ��ϻ���ĸ����޷�������а���\n");

        if( query("int", me)<32 )
                return notify_fail("���о��˰��죬ֻ�����ֽ�������ǣ�����޷������о���\n");

        if( query("con", me)<26 )
                return notify_fail("���о���һ�����ֻ������ǰ������ð��̫��Ѩͻͻ������\n");

        if (me->query_skill("literate", 1) < 120)
                return notify_fail("����������񽣼�����£�����������ѧ��ˮƽ�����о��ġ�\n");

        if (me->query_skill("lamaism", 1) < 120)
                return notify_fail("�㷢���������кܶ����������ķ��йأ�������⡣\n");

        if (me->query_skill("buddhism", 1) < 120)
                return notify_fail("�㷢���������кܶ����������ķ��йأ�������⡣\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("�������̫�����޷�ѧ�����񽣡�\n");

        if ((int)me->query_skill("finger", 1) < 120)
                return notify_fail("��Ļ���ָ����򲻹���\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("������ڱ��������������ڹ���ˮƽ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("������ڱ�������������ָ����ˮƽ��\n");

        return 1;
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage,cost;
        cost=40;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<160 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<160 )
                return notify_fail("������������������񽣡�\n");
        if( skill>100 && query("shen", me)<1 )
                return notify_fail("�����书�����������¡�\n");
        if ((int)me->query_skill("six-finger", 1)>150) cost=80;
        if ((int)me->query_skill("six-finger", 1)>250) cost=150;
        me->receive_damage("qi", cost);
        addn("neili", -150, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        string name;

        if (userp(me))
                attack_time = (int)(me->query_skill("six-finger", 1) / 50);
        else
                attack_time = (int)(me->query_skill("six-finger", 1) / 25);

        // �ſ�NPC�Ĺ�������
        if (userp(me) && attack_time > 6)
                attack_time = 6;

        if (! me->is_busy()
        && living(victim)
        && random(3) == 0
        && !query_temp("action_flag", me)
        && !query_temp("six-finger/hit_msg", me)
        && damage_bonus > 120
        && query("neili", me)>400
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 180
        && me->query_skill("jingluo-xue", 1) >= 200)
        {
                if( !query_temp("six-finger/hit_msg", me) )
                        message_combatd(HIW "\n��ʱ��$N" HIW "ֻ��˼����ӿ������������"
                                       "����·��������չ�֣���ʱʮָ�׵�����ȥ��������"
                                       "���޾���\n" NOR, me, victim);

                //me->start_busy(1);

                addn("neili", -attack_time*50, me);

                set_temp("action_flag", 1, me);
                for (i = 0; i < attack_time; i++)
                {
                        if (! me->is_fighting(victim))
                                break;
                        COMBAT_D->do_attack(me, victim, 0, 0);
                }
                delete_temp("action_flag", me);
        }

        if (damage_bonus > victim->query_dex() / 10
        && damage_bonus > 150
        && query("neili", me)>200
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 160
        && me->query_skill("jingluo-xue", 1) >= 180)
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", damage_bonus, me);
                return random(2) ? HIR "��������������һ�����죬���Ͼ��ɽ�����һЩѪ��"
                                   "��\n" NOR:

                                   HIR "��ֻ�������͡�һ�����죬һ��Ѫ����$n" HIR "����"
                                   "������\n" NOR;
        }
        return 1;
}


/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames);
}
*/

int double_attack()
{
        return 1;
}
mapping query_action(object me, object weapon)
{
        int d_e1 = 25;
        int d_e2 = 5;
        int p_e1 = -30;
        int p_e2 = -50;
        int f_e1 = 800;
        int f_e2 = 1000;
        int i, lvl, seq, ttl = sizeof(action);

        if (random(me->query_skill("six-finger",1)) > 60 &&
                me->query_skill("kurong-changong",1) > 60 &&
                query("neili", me)>100 )
        {
                addn("neili", -50, me);
                return ([
                        "action" : "$N��Ȼ���ý����е���·����һһӿ����ͷ��ʮָ�׵�����ȥ�����������޾��������ݺᣬ��������\n"
                        "��·������ת��ʹ��$n��ʱ������ң�����ȫ������ʹ��������Ѫ�����ϱ������ʹ̧ͷһ����һ������ӭ���ֵ�\n",
                        "dodge": -50,
                        "parry": -50,
                        "damage": 800,
                        "force": 800,
                        "damage_type": "����"]);
        }
        else
        {
                if (random(10) == 8)
                {
                        addn("neili", -200, me);
                        return ([
                                "action": HIC "$N" HIC "��Ȼ���ý����е���·����һһӿ����ͷ��ʮָ�׵�����ȥ�����������޾���\n" NOR
                                "��ʱֻ���Ĵ������ݺᣬ����������·������ת��ʹ��$n��ʱ������ң�����ȫ������\n"
                                "ʹ������" HIR "��Ѫ" NOR "�����ϱ������ʹ̧ͷһ����һ������ӭ���ֵ�",
                                "attack": 140,
                                "dodge" : -150,
                                "parry" : -120,
                                "damage": 1000,
                                "force" : 1000,
                                "damage_type": "����"]);
                }
                lvl = (int)me->query_skill("six-finger", 1);
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
                        "damage_type" : random(2) ? "����" : "����",
                ]);
        }
}

string query_parry_msg(object victim_weapon)
{
        switch (random(4))
        {
        case 0:
                return "$n������������������ݺύ������������$NΨ��������̾��ͽ���κΡ�\n";
        case 1:
                return "$n�������ܣ�һ���г彣ֱϮ$N����ǰ��Ѩ���ȵ�$Nֻ�л����Ծȡ�\n";
        case 2:
                return "$n���������������ص���ֱ���$Nüë���䣬������ͨ����Ҳ����ǰ����֣�\n";
        default:
                return "$nһ����Ц�����ν����Ĵ�ɢ������$N����ס��Ω����ǿ֧�š���Լ�԰�����$n�ķ�����\n";
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("six-finger", 1)) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + ob->query_skill("parry") + mp;
        dp = me->query_skill("parry") / 2 +
             me->query_skill("force") / 2 +
             me->query_skill("six-finger", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);


                result += (["msg" : HIC "$n" HIC "Σ��֮ʱ������һ�ң�����һָ��һ�����������ֱ��$N��ȥ��\n"
                                    HIC "$N" HIC "�����������׺ݣ����ò��������أ�����ܿ���\n" NOR]);

                return result;
        }
}

/*
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("six-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

*/
int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"six-finger/" + action;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("six-finger", 1); 

        if( lvl >= 180 && 
            !query("can_perform/six-finger/qi", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "���ν���" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/qi", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 200 && 
            !query("can_perform/six-finger/gz", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "��������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/gz", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
        
        if( lvl >= 220 && 
            !query("can_perform/six-finger/shen", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "��������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/shen", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 240 && 
            !query("can_perform/six-finger/six", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "��������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/six", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 260 && 
            !query("can_perform/six-finger/zong", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "�ݺ�����" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/zong", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                             

        if( lvl >= 800 && query("reborn/times", me) &&
            !query("can_perform/six-finger/tian", me) )  
        { 
                tell_object(me, HIC "��ͨ���������񽣡�" HIR "������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/six-finger/tian", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                 
} 


int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n�����񽣣�"NOR"\n");
        write(@HELP

    �������Ǵ�����ϲ���֮�ء�������Ϊ������ѧ֮��������
����Ϊ��������֮�����׼ҵ����޷������ð¡������񽣲�����ͨ
����������������������ָ�������˵������Σ��༴����������

        ѧϰҪ��
                ��������120��
                ����1200
HELP
        );
        return 1;
}

