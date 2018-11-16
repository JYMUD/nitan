#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nijiuyin-xinfa", 1);
        return lvl * lvl * 15 * 14 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N����һת��ȭͷЯ�ż�����ת�������ӳ����������磬��������������$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 120,
        "parry"  : 21,
        "damage" : 58,
        "lvl"    : 0,
        "damage_type": "����" 
]), 
([      "action" : "$N����һת��ȭͷЯ�ż�����ת�������ӳ����������磬��������������$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 61,
        "lvl"    : 180,
        "damage_type": "����"
]), 
([      "action" : "$N����һ�࣬һ�����������һ��������������ʱ����ӿ��$n��$l��",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 72,
        "lvl"    : 220,
        "damage_type": "����"
]),
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 143,
        "parry"  : 67,
        "damage" : 81,
        "lvl"    : 240,
        "damage_type": "����"
]), 
});

int valid_enable(string usage)
{               
                return usage == "force";
}

int valid_force(string force) { return 1; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("nijiuyin-xinfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        int i,skill,damage,lvl;
        
        skill = me->query_skill("nijiuyin-xinfa",1);
        if( query("jing", me)<60 )
                return notify_fail("��ľ���̫���ˡ�\n");
                
        if( query("qi", me)<200 )
                return notify_fail("�������������������ķ���\n");
         
        if (me->query_condition("jiuyin-except"))
                return notify_fail("����ȫ�޷��������ѣ�������������ȥ����������ķ���\n"); 
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                return notify_fail("���Ѿ�ѧ��������ˣ���ô����ȥ����������ķ���\n");
        }       
        
        if( query("sleep_room", environment(me)) )
                return notify_fail("��Ȼ����ô������Ϣ�ĵط��������书�����ǰ׳հ���\n");        
        
        if( skill>100 && query("shen", me)>-100 )
                return notify_fail("����а���书��������������ġ�\n");
        
        if( query("neili", me)<400 && random(10)<3 )
        {      
                message_vision(HIY "ͻȻ�㵫��һ����������������ͷ�����漴��ֻ�е�ȫ�����˺�Ѱ�ʹ��!\n"NOR,me);         
                me->apply_condition("jiuyin-except", skill + (int)me->query_condition("jiuyin-except"));
                return 1;
        }
        if( query("neili", me)<200 )
        
                return notify_fail("�������������������ķ���\n");
        
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 20);
        addn("neili", -50, me);
        tell_room(environment(me), 
MAG"ֻ��"+query("name", me)+"˫Ŀ���գ����������˫�ֱ�Բ��ͷ����ʱ��ð��һ˿˿��������֮
˫��֮���γ�һ����������Ȼֻ��"+query("name", me)+"��ɫʹ���ޱȣ���Ѫ����������ݳ���\n");

        return 1;
}

void skill_improved(object me)
{
    tell_object(me, HIR "���Ȼ���ĵ�����һ�ɶ���ٺ�.....��Ҫ��Ϊ���µ�һ......˭������Ϊ�У�\n" NOR );
    addn("shen", -100, me);
}
