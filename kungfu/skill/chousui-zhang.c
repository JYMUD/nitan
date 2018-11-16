// chousui-zhang.c ������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": ""HIB"$N����¶�������Ц�ݣ�����������ɫ��˫��ɨ��$n��$l"NOR"",
        "lvl"   : 0,
        "skill_name" : "������"
]),
([        "action": ""BLU"$NͻȻ������ת��������$n��˫�Ʒ���������$n��$l"NOR"",
        "lvl"   : 10,
        "skill_name" : "������"
]),
([        "action": ""HIB"$N�������������֣�һ�С���ʬ���������ޱȵ�ץ��$n��$l"NOR"",
        "lvl"   : 20,
        "skill_name" : "������"
]),
([        "action": ""BLU"$N˫��Ю��һ���ȳ�֮������$n��$l"NOR"",
        "lvl"   : 30,
        "skill_name" : "������"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo)
{
        return combo == "sanyin-zhua";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("��Ļ����������㣬�޷��������ơ�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷��������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("����Ʒ��������㣬�޷��������ơ�\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ̫�����޷��������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĳ����Ʒ���\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("��ı�����ֲ�����ϰ��\n");
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˡ�\n");
        if( query("neili", me)<40 )
                return notify_fail("������������������ơ�\n");
        if (me->query_skill("chousui-zhang", 1) < 50)
                me->receive_damage("qi", 45);
        else
                me->receive_damage("qi", 40);
        addn("neili", -25, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chousui-zhang", 1);
        flvl=query("jiali", me);

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl*2 + random(flvl*2),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 10) ])))
        {
                // �����ǳ����Ƶ� perform sandu �е�ɢ������ת�����
                if (me->query_skill("poison", 1) < 101)
                        set("body_poison", me->query_skill("poison",1)+1, me);
                if (me->query_skill("poison", 1) > 100)
                        set("body_poison", me->query_skill("poison",1)+10, me);
                //  ɢ������
                return HIW "$n" HIW "ֻ��һ�󼫺����ĵ����𣬿���������$N" HIW "���ϵľ綾��\n" NOR;
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
        int d_e1 = -45;
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 210;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        if (present("huo yan", environment(me)))
        {
                if( random(me->query_skill("strike"))>250 && query("neili", me)>1000 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": BLU "$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ�������ҧ��⣬" HIR "һ����"
                                "Ѫ���������ȥ��\n�ǻ������һ����" HIW "�漴��Ϊ������$N�͵����Ӽ���������"
                                "�ݰ���ת��ʮ���Ȧ�ӣ�\n" HIR "�����������������Ѷ��ز��𣬱���һ����ǽ����$nѹ��ȥ" NOR,
                                "force" : 450,
                                "dodge" : -100,
                                "parry" : -100,
                                "weapon": "����",
                                "damage_type": "����"]);
                }
                if (random(me->query_skill("strike")) > 215 &&
                    query("neili", me)>800 )
                    {
                        addn("neili", -75, me);
                        return ([
                                "action": HIG "$N������ȣ�������ʢ���̻�ͻȻ����һ��"
                                          HIR "����Ļ�����$n���������\nʹ�����ͣ�ȥ����죬"
                                          HIG "ֻ��һ���̵Ļ����ڿ��й�µµ��Ѹ��ת��" NOR,
                                "force" : 420,
                                "dodge" : -90,
                                "parry" : -90,
                                "weapon": "����",
                                "damage_type": "����"]);
                }
                if (random(me->query_skill("strike")) > 180 &&
                    query("neili", me)>600 )
                {
                        addn("neili", -50, me);
                        return ([
                                "action": HIR "$N����һ����һ�ɾ���ֱ�������֮�У�"+HIG+"�������ֳַ�һ��ϸϸ���̻𣬱���һ��ˮ�߰㣬\n"
                                          HIW "$N����Ӷ������ɾ����Ϯ$n����" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG "�̻�" NOR,
                                "damage_type": "����"]);
                }
                if (random(me->query_skill("strike")) > 150 &&
                    query("neili", me)>500 )
                {
                        addn("neili", -20, me);
                        return ([
                                "action": HIR "$N�漴����б�ĳ�һ��"+HIG+"�̻�"+HIR+"��$n��ȥ���������ڣ�"+HIG+"����һ����ɫ���ߺ��Կռʣ�����ڶ���\n"
                                          HIR "��ɫ�������ޣ�"+BLU+"���ǹ��죬��â��˸����"+HIG+"��ӳ��$nͷ���Ա�"NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG"�̻�"NOR,
                                "damage_type": "����"]);
                }

                if (random(me->query_skill("strike")) > 120 &&
                        query("neili", me)>400){
                        addn("neili", -10, me);
                        return ([
                                "action": HIR "$NͻȻ��˫ü����һ��������ʳָ�����㣬������������������죬"+HIG+"��������𻨣���������һ�㣬\n"
                                          "��$N���������£��ִ�����Ϯ��$n������Ѹ��֮��" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": "��",
                                "damage_type": "����"]);
                }
        }
        lvl = (int) me->query_skill("chousui-zhang", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n�����ƣ�"NOR"\n");
        write(@HELP

    �������Ʒ����Ը�ʬ���������¡�
    �����������צ������

        ѧϰҪ��
                ������10��
                ����60
HELP
        );
        return 1;
}
