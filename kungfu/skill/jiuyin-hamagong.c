inherit FORCE;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N����һת��ȭͷЯ�ż�����ת�������ӳ����������磬��������������$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 100,
        "parry"  : 21,
        "damage" : 160,
        "lvl"    : 0,
        "damage_type": "����" 
]), 
([      "action" : "$N����һת��ȭͷЯ�ż�����ת�������ӳ����������磬��������������$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 100,
        "damage_type": "����"
]), 
([      "action" : "$N����һ�࣬һ�����������һ��������������ʱ����ӿ��$n��$l��",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 250,
        "lvl"    : 150,
        "damage_type": "����"
]),
([      "action" : "$N˫��΢��������ƽ�죬���������󡹦����������һ������$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 152,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 200,
        "damage_type": "����"
]), 
([      "action" : "$N���۱�ס��������Ծ�����۾�Ҳ��������������$n���˳�ȥ",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 202,
        "parry"  : 53,
        "damage" : 300,
        "lvl"    : 220,
        "damage_type": "����"
]),
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 243,
        "parry"  : 67,
        "damage" : 350,
        "lvl"    : 250,
        "damage_type": "����"
]), 
});

int valid_enable(string usage)
{ 
        int lvl = (int)this_player()->query_skill("jiuyin-hamagong", 1);

        if (lvl >= 200)    
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";
       
}

string main_skill()
{
        return "jiuyin-hamagong";

}
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-hamagong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}


mapping sub_skills = ([
        "nijiuyin-xinfa" : 250, 
        "hama-gong" : 250,            
        ]);

int valid_learn(object me)
{
        if( query("character", me) == "��������" )
                return notify_fail("�����а������������󡹦�����쳣�����ƻ��˼���"
                                   "�����Ǳ���Ϊ�\n");
                                   
        if( query("gender", me) == "����" )
                return notify_fail("���޸����ԣ���������������������ľ�����󡹦��\n");
        if ((int)me->query_skill("jiuyin-hamagong", 1) < 240)
                return notify_fail("��Ծ�����󡹦��⻹�����������ȥ���벻ͨ!\n"); 

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("��Ļ�����������㣬��������󡹦��\n");        
                
        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jiuyin-hamagong", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ�������������ľ�����󡹦��\n"); 

        if( query("max_neili", me)<4300 )
                return notify_fail("�����ڵ�������Ϊ���㣬������������󡹦��\n");

        if( query("str", me)<30 )
                return notify_fail("�����������������޷����������󡹦��\n");
                
        if( query("con", me)<34 )
                return notify_fail("��������ǲ������޷����������󡹦��\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ������󡹦��\n");

        return ::valid_learn(me);
}

int get_finish(object me)
{
        object ob;

        if( query("gender", me) == "����" )
        {
                tell_object(me, "��������ϣ�ֻ����Ѫ��ӿ�������Լ������������޷�����������󡹦��\n" NOR);
                return 0;
        }

        if( query("character", me) == "��������" )
        {
                tell_object(me, "��������ϣ����þ�����󡹦а���ݺᣬ���Ƚ���Լ���ôҲ�޷������һ��\n" NOR);
                return 0;
        }

        if( query("character", me) == "������" )
        {
                tell_object(me, "��������ϣ����þ�����󡹦а���ݺᣬ���Ƚ���Լ���ôҲ�޷������һ��\n" NOR);
                return 0;
        }

        if( query("con", me)<34 )
        {
                tell_object(me, "��������ϣ������Լ����������̫��޷���������󡹦�ڵ��书��һ��\n");
                return 0;
        }

        if( query("str", me)<30 )
        {
                tell_object(me, "��������ϣ������Լ������������������޷���������󡹦�ڵ��书��һ��\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "����þ�����󡹦�ڵ��书��������£��������о�һ��ѧ�ʿ��ܸ��а�����\n");
                return 0;
        }
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                tell_object(me, "���Ѿ�ѧ��������ˣ���ô��������ת�ɹ���\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 190)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ������޷���������󡹦�ڵ��书��һ��\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "������Լ��������̣��޷���������������󡹦��\n");
                return 0;
        }

        if (random(10) < 6)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ�������ߺ�һ��\n");
                return 0;
        }

        tell_object(me, HIW "һ�󷲳�����ӿ����ͷ����Ĭ�������󡹦��һ��Ī��������������ӿ��ͷ���ٻ�Ѩ��\n"
                        "�����������ң��漴���ֳŵأ�˫�ŵ������ϣ����¡�һ�����أ����������ܽС��쳹��ء�\n"
                        "�����������㵫��ȫ���ޱ��泩!�ƺ���������������������!\n" NOR);
        CHANNEL_D->do_channel(me,"rumor",sprintf("��Ȼ%s���¡�һ�����أ����������ܽ�,�쳹��ء�",query("name", me)));
        CHANNEL_D->do_channel(me,"rumor",sprintf("%s����ø��������ѣ�������ת�������������ŷ���岻���ؼ�������󡹦�ˡ�",query("name", me)));
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int practice_skill(object me)
{
        return notify_fail("������󡹦ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("jiuyin-hamagong", 1);

        if (damage_bonus < 150
           || lvl < 200
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "jiuyin-hamagong"
           || me->query_skill_mapped("unarmed") != "jiuyin-hamagong"
           || me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return 0;

        if (damage_bonus / 4 > victim->query_con())
        {
                addn("neili", -40, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                return WHT "ֻ��$N" HIR "���¡�"NOR"" WHT "һ�����أ��漴����������ǰ��ȫ������һ��$nʼ�ϲ���\n"
                       "��һ�����ͻȻ��ֻ��Ӳ�Ӵ��У���ʱȫ��һ���������������һ����Ѫ��\n" NOR;
        }
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiuyin-hamagong", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-hamagong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-hamagong/exert/" + action;
}

