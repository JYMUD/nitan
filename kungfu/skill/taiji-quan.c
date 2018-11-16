// taiji-quan.c ̫��ȭ

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *taijin = ({ "����������", "����������", "�����Ǿ���", "���������", "��մ����",  "�����־���","�귭", "����","����","����","����","����"});
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
         "$p�ۼ�$P$w����������ʹ��һ�С���ȸβ�����ҽ�ʵ������飬���𡰼����־���ճ��ճ�棬�����Ѵ�ס$P���󣬺ᾢ������$N����������ǰһ�壬�����������ʼվ����\n",
         "����$p˫��һȦ���籧̫����һ���ۻ��ޱȵ����������һ�����У�ֻ����$P��ԭ�ؼ�ת�߰��¡�\n",
         "$p��˫����������������˫�ֳ�Բ�λ������漴��Ȧ��Ȧ��һ��ԲȦ����һ��ԲȦ����Ȧ��СȦ��ƽȦ����Ȧ����Ȧ��бȦ��һ����̫��ԲȦ��������ʱ���׵�$P����ײײ�������������㲻�ȡ�\n",
         "$pʹ��һ�С����֡������ָߣ����ֵͣ�һ��ԲȦ�ѽ�$P$w��ס��\n",
         "$p����Ϣ΢�ϣ�����һ�С�б���ơ�����$P$w��ƫ��\n",
         "$p��һ����������������ת�����ƻӳ���һ��һӭ����$P�������������˻�ȥ��\n",
         "$p˫��һ����ʹ��һ�С����֡���˫���ᵽ�˼������������飬��$P$w�ļ���������ȥ��\n",
        "$p����˫��һ�ӭ��$w��ȥ������������$P$w����δ��֮�ʣ�ʩ������ȸβʽ������$w����£ס�����¡��𼦶���ʽ��������صأ��������գ�ȫ��ת������һö���ݡ�\n",
         "��������ʯ���һ˲֮�䣬$p����һ�������ǡ��׺����᡹��ǰ���У�$P�ľ�����ʱ��ա�\n",
});

mapping *action = ({
([      "action" : "$Nʹһ��"+(order[random(13)])+"����ȸβ��"NOR"��˫�ֻ��˸���Ȧ������$n��$l",
        "skill_name" : "��ȸβ",
        "lvl" : 0
]),
([      "action" : "$Nʹһ��"+(order[random(13)])+"�����ޡ�"NOR"�������������£���������ӳ�������$n��$l",
        "skill_name" : "����",
        "lvl" : 5
]),
([      "action" : "$N���ֻ��գ������ɹ����ƣ���������ʹһ��"+(order[random(13)])+"��������ʽ��"NOR"����$n��$l��ȥ",
        "skill_name" : "������ʽ",
        "lvl" : 10
]),
([      "action" : "$N˫�ֻ������������ϣ��������£�ʹһ��"+(order[random(13)])+"���׺����᡹"NOR"���ֻ�$n�����ź�$l",
        "skill_name" : "�׺�����",
        "lvl" : 15
]),
([      "action" : "$N��������ǰ���£�����΢ת������һ����Ȧ��ʹһ��"+(order[random(13)])+"��§ϥ�ֲ���"NOR"������$n��$l",
        "skill_name" : "§ϥ�ֲ�",
        "lvl" : 20
]),
([      "action" : "$N�������������������ںϣ�ʹһ��"+(order[random(13)])+"���ֻ����á�"NOR"����$n��$l��ȥ",
        "skill_name" : "�ֻ�����",
        "lvl" : 25
]),
([      "action" : "$N���ֱ��ƺ�����ǰ����ȭ�����´�����һ��"+(order[random(13)])+"����׿�����"NOR"������$n��$l",
        "skill_name" : "��׿���",
        "lvl" : 30
]),
([      "action" : "$N���ǰ̤�벽������ʹһ��"+(order[random(13)])+"�������롹"NOR"��ָ������$n��$l��ȥ",
        "skill_name" : "������",
        "lvl" : 35
]),
([      "action" : "$N��"+(order[random(13)])+"����ͨ�ۡ�"NOR"�����һ���������������Ͼ�����Ʋ������$n��$l��ȥ",
        "skill_name" : "��ͨ��",
        "lvl" : 40
]),
([      "action" : "$N��������ԣ�ת�����������·ֱ�ӳ�������ʹһ��"+(order[random(13)])+"��б��ʽ��"NOR"������$n��$l",
        "skill_name" : "б��ʽ",
        "lvl" : 45
]),
([      "action" : "$N�����鰴������ʹһ��"+(order[random(13)])+"���������š�"NOR"����$n��$l��ȥ",
        "skill_name" : "��������",
        "lvl" : 50
]),
([      "action" : "$N˫����ȭ����ǰ��󻮻���һ��"+(order[random(13)])+"��˫������"NOR"����$n��$l",
        "skill_name" : "˫����",
        "lvl" : 55
]),
([      "action" : "$N�����黮������һ��"+(order[random(13)])+"��ָ�ɴ���"NOR"����$n���ɲ�",
        "skill_name" : "ָ�ɴ�",
        "lvl" : 60
]),
([      "action" : "$Nʩ��"+(order[random(13)])+"������ʽ��"NOR"�����ֻ���$n��$l�����ֹ���$n���ɲ�",
        "skill_name" : "����ʽ",
        "lvl" : 65
]),
([      "action" : "$N�ɱ۴��֣�����ǰ����������ʹһ��"+(order[random(13)])+"�����֡�"NOR"������$n��$l",
        "skill_name" : "����",
        "lvl" : 70
]),
([      "action" : "$N������������ʹһ��"+(order[random(13)])+"���𼦶�����"NOR"����$n��$l��ȥ",
        "skill_name" : "�𼦶���",
        "lvl" : 75
]),
([      "action" : "$N�����ɹ����ƣ�˫���������ϣ�������ǰ�Ƴ�һ��"+(order[random(13)])+"����̽��"NOR"",
        "skill_name" : "��̽��",
        "lvl" : 80
]),
([      "action" : "$N����ʹһʽ��"+(order[random(13)])+"����Ů����"NOR"��������$n��$l��ȥ",
        "skill_name" : "��Ů����",
        "lvl" : 85
]),
([      "action" : "$N���־���ǰ��������ǰƲ����ʹһ��"+(order[random(13)])+"������Ʋ����"NOR"����$n��$l��ȥ",
        "skill_name" : "����Ʋ��",
        "lvl" : 90
]),
([      "action" : "$N�����鰴������ʹһ��"+(order[random(13)])+"��ת����ȡ�"NOR"����$n��$l��ȥ",
        "skill_name" : "�������",
        "lvl" : 95
]),
([      "action" : "$N�������ϻ�������������ʹһ��"+(order[random(13)])+"����������"NOR"����$n��$l��ȥ",
        "skill_name" : "��������",
        "lvl" : 100
]),
([      "action" : "$Nʹһ��"+(order[random(13)])+"���Դ���"NOR"������§��ϥ���������´���$n��$l",
        "skill_name" : "�Դ�",
        "lvl" : 120
]),
([      "action" : "$N˫���ȱ�����״�����طֿ������������£�һ��"+(order[random(13)])+"��Ұ����ס�"NOR"����$n��$l�����Ŵ�ȥ",
        "skill_name" : "Ұ�����",
        "lvl" : 150
]),
([      "action" : "$N��������ǰ���£��ұ�΢����ʹһ��"+(order[random(13)])+"��������ɽ��"NOR"����$n��$l��ȥ",
        "skill_name" : "������ɽ",
        "lvl" : 180
]),
([      "action" : "$N˫�־��¸�����������ǰ����ʮ��״��һʽ"+(order[random(13)])+"��ʮ���֡�"NOR"����$n��$l��ȥ",
        "skill_name" : "ʮ����",
        "lvl" : 210
]),
([      "action" : "$N���̤һ���鲽��˫�ֽ����ʮ��ȭ��һ��"+(order[random(13)])+"���������ǡ�"NOR"����$n��$l��ȥ",
        "skill_name" : "��������",
        "lvl" : 240
]),
([      "action" : "$N��������ڳ���������ֱ���ұ�΢����ʹһ��"+(order[random(13)])+"������"NOR"����$n��$l�����Ŵ�ȥ",
        "skill_name" : "�����",
        "lvl" : 270
]),
([      "action" : "$N˫���쿪������Ϊ�ᣬ����������һ����Բ����\nһ��"+(order[random(13)])+"��ת�������"NOR"����$n�������¶�������������Ӱ֮��",
        "skill_name" : "ת�����",
        "lvl" : 300
]),
([      "action" : "$N˫����ȭ�����ֻ����������ʣ����ֻ�����ǰ�Ƴ���\nȭ�������һ��"+(order[random(13)])+"���乭�仢��"NOR"��ֱ��$n���Ѷ�ȥ",
        "skill_name" : "�乭�仢",
        "lvl" : 400
]),
([      "action" : "$N˫������ǰ���ƣ��ɸ�����ǰ�����Ƴ���һ��"+(order[random(13)])+"������Ʊա�"NOR"��һ�ɾ���ֱ��$n",
        "skill_name" : "����Ʊ�",
        "lvl" : 500
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }
int valid_combine(string combo)
{
        return combo == "wudang-zhang" || combo == "paiyun-shou";
}

int valid_learn(object me)
{
        if( query("int", me)<26 )
                return notify_fail("����������̫��������̫��ȭ��Ҫ�衣\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��̫��ȭ������֡�\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻹����޷�ѧ̫��ȭ��\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("�������̫�����޷���̫��ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < 100)
                return notify_fail("��Ļ���ȭ����򲻹����޷�ѧ̫��ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("taiji-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷����������̫��ȭ��\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<70 )
                return notify_fail("�������������̫��ȭ��\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -50;
        int p_e1 = -70;
        int p_e2 = -60;
        int f_e1 = 400;
        int f_e2 = 600;
        int i, lvl, seq, ttl = sizeof(action);
        string msg;
        lvl = (int) me->query_skill("taiji-quan", 1);
/////////yun taiji/////////
        if( query_temp("taiji", me) && query("neili", me)>100 )
        {
                addn_temp("taiji_fight", 1, me);
                msg = random(2)==1?
                        HIW"ֻ��$N���鶥�������ذα����������Ρ�����׹�⣬˫�ֱ��˸�̫��ʽ��ԲȦ����������̫����\n�Ѵ������һ���Ķ������ľ��磬���ʹ����̫��ȭ�е�"NOR:
                        HIW"ɲʱ��$N����̫��ȭּ�С����ɷ��ɣ���չδչ�������ⲻ�ϡ��ľ�΢����֮����\nʹ��һ������������ˮ�������ޱȡ����ʹ����̫��ȭ�е�"NOR;
                msg = msg + order[random(sizeof(order))] + taijin[random(sizeof(taijin))] + NOR;
        if ( lvl > 250
        && random(lvl) > 200
        && random(10)>3)
        {
                addn("neili", -10, me);
                return ([
                        "action" : msg,
                        "force" :  600,
                        "dodge":   -180,
                        "damage":   500,
                        "parry":   -180,
                        "damage_type" : random(2)==1?"����":"����",
                ]);
        }
  }
  //////��ͨ����////////
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

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("taiji-quan", 1) < 100 ||
            !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("taiji-quan", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "�溬΢Ц��˫�������������"
                                            "һ��ԲȦ����Ȼ��$N" +
                                            HIC "�Ĺ���ȫ��������\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "���Ҹ񵵣�ʹ��������ǧ����ַ���"
                                            "����$N" HIC "�Ĺ��������Ρ�\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "������ȭ"
                                            HIC "��������Ȼ������ȴ��$N"
                                            HIC "�е�����ճ�ͣ������泩��\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "�溬΢Ц��˫�������������"
                                 "һ��ԲȦ��Ȼ��$N" +
                                 HIY "��Ҳ�������ֻ���ֱ�룬��Ϯ$n"
                                 HIY "��\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "���Ҹ񵵣�ʹ��������ǧ����ַ���"
                                 "����$N" HIY "����ȴ�Ǳ仯�޷�������ѭ����\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "������ȭ"
                                 HIY "����������ȴ��$N"
                                 HIY "�е�ճ�ͣ�����$N"
                                 HIY "���̱仯���࣬�����п��ٽ���$n"
                                 HIY "��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("taiji-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"taiji-quan/" + action;
}
string query_description()
{
        return
        "̫��ȭ��Ϊ��ĩԪ���䵱�����������������ϵ���֮˵��������Ȼ��������"
        "��죬�Ծ��ƶ����ᷢ���ˣ���Ϊ����֮����ϳ���ѧ��ȭ��ʱ˫��Բת��"
        "ÿһ�ж�����̫��ʽ�������仯����΢���ʵ�ǿ�������ѧ�д���δ�е�"
        "����ء�����Ϊ�����鶥�������ذα����������Ρ�����׹�⡹ʮ�����֣�"
        "���������У���������������һ������·ȭ����Ҫּ��"
        "̫��ȭ����Ҫ�������ɷ��ɣ���չδչ�������ⲻ�ϣ����������Ϊ����һ����";
}

int help(object me)
{
        write(WHT"\n̫��ȭ��"NOR"\n");
        write(@HELP

    ̫��ȭ��Ϊ��ĩԪ���䵱�����������������ϵ���֮˵������
��Ȼ����������˸ա�������ǧ���������죬�Ծ��ƶ�����
���ˣ���Ϊ����֮����ϳ���ѧ��ȭ��ʱ˫��Բת��ÿһ�ж�����
̫��ʽ�������仯����΢���ʵ�ǿ�������ѧ�д���δ�е�����
�ء�����Ϊ�����鶥�������ذα����������Ρ�����׹�⡹ʮ����
�֣��������У���������������һ������·ȭ����Ҫּ��
    ̫��ȭ����Ҫ�����ɷ��ɣ���չδչ�������ⲻ�ϣ��������
��Ϊ����һ����

        ѧϰҪ��
                ̫����20��
                ����100
HELP
        );
        return 1;
}
