// This program is a part of NT MudLIB
// qishang-quan.c ����ȭ

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N������ɽ��һʽ�����������˫ȭ���ƶ���������$n��$l",
        "lvl" : 0,
        "skill_name" : "�������"
]),
([        "action" : "$N�������أ�����������һʽ��ľ�ѳ��ۡ���������$n�Ƴ�",
        "lvl" : 10,
        "skill_name" : "ľ�ѳ���"
]),
([        "action" : "$N�������飬����������ޣ�һʽ��ˮ�����¡�����$n�޿ɶ���",
        "lvl" : 20,
        "skill_name" : "ˮ������"
]),
([        "action" : "$N����Ծ��һʽ���𺣵�ɽ����˫ȭ���ջ��£��Ʋ��ɵ�",
        "lvl" : 30,
        "skill_name" : "�𺣵�ɽ"
]),
([        "action" : "$N����һ����һʽ�������������ȭ���¶��ϣ�����$n",
        "lvl" : 40,
        "skill_name" : "��������"
]),
([        "action" : "$N����һת��һʽ������Ҳҡ�������$n����ǰ���",
        "lvl" : 48,
        "skill_name" : "����Ҳ�"
]),
([        "action" : "$N���λ�λ������ȭ����һʽ���������ա�������˷�����ȭӰ",
        "lvl" : 54,
        "skill_name" : "��������"
]),
([        "action" : "$N��Хһ������ǰ̤��һ����˫ȭ�й�ֱ����һʽ�����߽��ˡ�����Ȼ����$n��ǰ��",
        "lvl" : 60,
        "skill_name" : "���߽���"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("������ȭ������֡�\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("����ڹ���򲻹����޷�ѧ����ȭ��\n");

        if ((int)query("max_neili", me) < 1800)
                return notify_fail("���������Ϊ�������޷�������ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("��Ļ���ȭ����򲻹����޷�������ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("qishang-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���������޷��������������ȭ��\n");

        return 1;
}

int practice_skill(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if ((int)query("qi", me) < 60)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)query("neili", me) < 70)
                return notify_fail("�����������������ȭ��\n");
        /*
        if ((int)me->query_skill("qishang-quan",1) % 20 == 0 &&
                (int)me->query_skill("qishang-quan",1) < 200)
                return notify_fail("�������ȭ���˹ؼ������ô�����޷�����\n");
        */
        me->receive_damage("qi", 50);
        addn("neili", -60, me);
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
        int d_e1 = 5;
        int d_e2 = 30;
        int p_e1 = -50;
        int p_e2 = -5;
        int f_e1 = 250;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qishang-quan", 1);
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
                "damage_type" : "����",
        ]);
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        mixed result;
        int lvl;
        int flvl;

        lvl  = me->query_skill("qishang-quan", 1);
        flvl = query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (random(lvl) > 80 && (int)query("neili", me) > 300)
        {
                victim->affect_by("qs_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ]));
                result = ([ "damage" : damage_bonus ]);
                addn("neili", -200, me);

                switch(random(7))
                {
                case 0 :
                        msg = MAG"$N��������ʹ������ȭ�ܾ��еġ�"HIR"���ľ�"MAG"����˫ȭһ�ɸ���֮����$n��ȥ��\n"NOR;
                        break;
                case 1 :
                        msg = HIB"$N����һ��������ȭ��ʹ������ȭ�ܾ��еġ�"HIR"�˷ξ�"HIB"����˫ȭƮ��������$n��ʱ�о�һ������֮��ӭ�������\n"NOR;
                        break;
                case 2 :
                        msg = HIC"$N��ȭ����ʹ������ȭ�ܾ��еġ�"HIR"�ݸγ���"HIC"����˫ȭ�������ᣬ��$n��ȥ��\n"NOR;
                        break;
                case 3 :
                        msg = HIG"$N��������ʹ������ȭ�ܾ��еġ�"HIR"�����"HIG"����˫ȭ�����иգ����һ������֮������$n��ȥ��\n"NOR;
                        break;
                case 4 :
                        msg = HIY"$N��������ʹ������ȭ�ܾ��еġ�"HIR"��ʧ��"HIY"����˫ȭ����������������ֱ��$n��ȥ��\n"NOR;
                        break;
                case 5:
                        msg = HIM"$N��������ʹ������ȭ�ܾ��еġ�"HIR"���㱾�"HIM"������$n�ͳ�һ�ɺ��֮����\n"NOR;
                        break;
                case 6:
                        msg = HIR"$N���һ�����뷢���ţ�ʹ���������ܾ���������˫ȭ����������������ٱ������$n��\n"NOR;
                        break;
                }
                msg += HIW"$nֻ����$N��һȭ֮�й����߹ɲ�ͬ��������ðٶˣ���ԥ���ѱ������������ȫ����ʱ�������ص����ˡ�\n" NOR;
                result += ([ "msg" : msg ]);
                return result;
        }
}

void skill_improved(object me)
{
        object *ob;
        int i, skill;
        skill = me->query_skill("qishang-quan", 1);

        if (query("max_neili", me) < skill * 15 && skill < 200)
        {
                switch(random(5)){
                case 0 :
                        tell_object(me, HIR"���ͷ����ѨͻȻһ����΢��ʹ���Ƿ������ˣ�\n"NOR);
                        addn("max_neili", -random(100), me);
                        break;
                case 1 :
                        tell_object(me, HIR"����������ѨͻȻ��ʹ�ѵ����Ǹ������ˣ�\n"NOR);
                        addn("combat_exp", -random(7000), me);
                        break;
                case 2 :
                        message_vision(HIR"$N�������ˣ�ͻȻ���Դ󷢡��޷������ˣ�\n"NOR, me);
                        me->set_skill("qishang-quan", skill - 1);
                        break;
                case 3 :
                        tell_object(me, HIR"���ϱ�����ѨͻȻһʱ�����ѵ������������ˣ�\n"NOR);
                        addn("max_neili", -random(100), me);
                        break;
                case 4 :
                        tell_object(me, HIR"��ͻȻ�������������������н�ľˮ�������У��޷������ˣ�\n"NOR);
                        me->set_skill("qishang-quan", skill-2);
                        break;
                }
                // me->unconcious();
        }
}

string perform_action_file(string action)
{
        return __DIR__"qishang-quan/" + action;
}

int help(object me)
{
        write(HIC"\n����ȭ��"NOR"\n");
        write(@HELP

    ����ȭ��ȭ�����ˡ�������ɵĲ���֮�أ�������лѷΪ����
�𣬴���������е���������ȭ�ס����Ӷ����ɡ���Ϊ���ˣ�ʵ��
Ϊÿ��һȭ���������ֲ�ͬ�ھ���ʹ�˲�֪�����֮�࿹��

                    ������������������������
                    ��    ����ȭ�ܾ�      ��
                    ��  ����֮����������  ��
                    ��  �����˷δݸγ���  ��
                    ��  ���뾫ʧ���㱣�  ��
                    ��������������Ƿ�    ��
                    ������������������������

        ѧϰҪ��
                ֻ����лѷѧϰ
                ����200
HELP
        );
        return 1;
}