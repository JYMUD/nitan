#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        HIW "$n" HIW "��ǰһ���������������뽣���Ϊһ�壬$N" HIW "Ŀ�ɿڴ���һʱ�����ҳ����������\n" NOR,
        HIW "ֻ��$n" HIW "����������������������ʱ��������Ӱ��$N" HIW "�ۻ����ң��޴ӹ�����\n" NOR,
        HIW "$n" HIW "�����ڹ��������ɽ�����������������է�ֽ���$N" HIW "����Χס�����ﻹ�л��ṥ����\n" NOR,
});

string *parry_msg = ({
        HIG "$N" HIG "һ�й�����$n" HIG "���˲��ܣ�������â��������������о������������Ρ�\n" NOR,
        HIG "$n" HIG "��¶΢Ц��������Ȼ��û�Ϊһ����������$N" HIG "�����������޷���֮���塣\n" NOR,
        HIG "$n" HIG "���Ų�æ�����н�������ǰ����һ�������Ļ��ߣ�����$N" HIG "����ȫ�����⡣\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("lunhui-sword", 1);
        return lvl * lvl / 100 * 15 * 38  / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        
        lvl = (int)me->query_skill("lunhui-sword", 1);
        
        if (me->query_skill_mapped("force") == "lunhui-sword")
                return lvl * 14 / 10;

        return 0;
}

mapping *action = ({
([      "action": HIW "$N" HIW "ʹ�����켫���������������ޱȣ��û��������ǹ⣬ͻȻ�����콣ʽ��Ϊһ��������$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "skill_name" : "�켫��",
        "damage_type": "����"
]),
([      "action": HIM "$N����$w" HIM "��������է�֣��������˵�������һʽ���˼����ʹ������ʱ����������$n" HIM "��Χ" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "�˼��",
        "damage_type": "����"
]),
([      "action": HIG "$N" HIG"һ�����Ƴ��գ����������ʹ�����������䣬����$n" HIG "�����������ޱȣ�������η" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 450,    
        "skill_name" : "�����",
        "damage_type": "����"
]),
([      "action": HIR "$N" HIR "���轣����ʹ��������������һ�ɺ�����$w" HIR "��������Ұ������꣬��Х��ӿ��$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "lvl"   : 300,        
        "skill_name" : "������",
        "damage_type": "����"
]),
([      "action": HIC "$N" HIC "�߶�������һʽ�����޵�������ɲʱ�����񱼣�����������Ϣ�������Ѿ�Ϯ��$n" HIC "$l" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,       
        "skill_name" : "���޵�",
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "�߾�$w" HIY "����â���²�����һʽ����������ʹ�������������ž����ŭ���̿���Ϯ��$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "������",
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "��¶΢Ц�����һ��������һʽ��" HIR "�����ֻ�" HIY "��ʹ�������������ʱ������ɫ��â����$n",
        "force" : 700,
        "attack": 650,
        "dodge" : 110,
        "parry" : 650,
        "damage": 650,
        "skill_name" : "�����ֻ�",
        "damage_type": "����"
]),
});

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry" || usage == "dodge" || usage == "parry" || usage == "force";
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string main_skill()
{
        return "lunhui-sword";
}

mapping sub_skills = ([
        "tianji-dao"  : 500,
        "diyu-dao"    : 500,
        "egui-dao"    : 500,
        "chusheng-dao": 500,
        "renjian-dao" : 500,
        "xiuluodao"   : 500,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        ob = environment(me);

        // ������޷�����
        if( query_temp("apply/mask_flag", me) )
        {
                tell_object(me, "�������ȡ����ߡ�\n");
                return 0;
        }

        if( !query("lunhui", ob) )
        {
                tell_object(me, "���������ֻؽ��������ֻ�˾�У���Ҫ�����Ϲ����������֮����\n");
                return 0;
        }
        
        if( query("reborn/times", me) < 3 )
        {
                tell_object(me, "��ת�������������޷������ֻصľ��裡\n");
                return 0;
        }

        if( query("int", me)<40 )
        {
                tell_object(me, "��������ϣ�ֻ��˼�����ң�������������ԣ���"
                                "�������һ��\n");
                return 0;
        }
        if( query("con", me)<40 )
        {
                tell_object(me, "��������ϣ�ֻ��ȫ�������Ҵܣ���ð���ǣ�������������"
                                "�����ײſ���������\n");
                return 0;
        }
        if( query("str", me)<40 )
        {
                tell_object(me, "��������ϣ�ֻ��˫�����ۣ�ȫ����\n");
                return 0;
        }
        
        if( query("dex", me)<40 )
        {
                tell_object(me, "��������ϣ��������������ʱ���޷������ڻ��ͨ��\n");
                return 0;
        }

        if (random(100) != 1 && ! wizardp(me))
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ�����������ֻؽ���\n");
                return 0;
        }

        if (me->query_skill("sword", 1) < 700)
        {
                tell_object(me, "�������������㣬���������������ֻؽ���\n");
                return 0;
        }
        if (me->query_skill("force", 1) < 700)
        {
                tell_object(me, "������ڹ�����㣬���������������ֻؽ���\n");
                return 0;                
        }
        if (me->query_skill("martial-cognize", 1) < 700)        
        {
                tell_object(me, "����ѧ��������㣬���������������ֻؽ���\n");
                return 0;                
        }
        if (me->query_skill("dodge", 1) < 700)        
        {
                tell_object(me, "������Ṧ����㣬���������������ֻؽ���\n");
                return 0;                
        }        
        if ((int)me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "�������ķ���Ϊ���㣬���������������ֻؽ���\n");
                return 0;        
        }
        /*
        // �����ֻص�
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
        {
                tell_object(me, "���ֻص㲻�㣬�޷������������ֻؽ���\n");
                return 0;
        }
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);
        */
        me->save();

        tell_object(me, HIW "һ�󷲳�����ӿ����ͷ���㼸��������̾�����Ǽ䣬����ۻ��ף�����һ��Ī��\n"
                        "�ı�������ʦ̩�����ָ߳���ʤ������̩ɽ��С����֮����Ȼ��������ֻ������\n����"
                        "��ѧ���ڿ����Ƕ�ô����С��Ц��\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name() + "������"HIY"�����ֻؽ�"HIM"��\n");
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_learn(object me)
{

        // ��12T��ͻ
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return notify_fail("��о����ڵ�������ת�������������ƺ����������ڹ���\n");
                
        if( query("str", me)<40 )
                return notify_fail("������������㡣\n");

        if( query("int", me)<40 )
                return notify_fail("���������Բ��㡣\n");

        if( query("dex", me)<40 )
                return notify_fail("�����������㡣\n");
                
        if( query("con", me)<40 )
                return notify_fail("��������ǲ��㡣\n");                        
                
        if( query("max_neili", me)<8000 )
                return notify_fail("���������Ϊ�������������������ֻؽ���\n");

        if ((int)me->query_skill("force", 1) < 700)
                return notify_fail("����ڹ����̫ǳ���������������ֻؽ���\n");

        if ((int)me->query_skill("sword", 1) < 700)
                return notify_fail("��Ľ����������㣬�������������ֻؽ���\n");

        if ((int)me->query_skill("dodge", 1) < 700)
                return notify_fail("����Ṧ�������㣬�������������ֻؽ���\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 700)
                return notify_fail("�����ѧ�������㣬�������������ֻؽ���\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("��������ķ���Ϊ���㣬�������������ֻؽ���\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������������ֻؽ���\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������������ֻؽ���\n");
                
        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("�����ѧ����ˮƽ���ޣ��޷���������������ֻؽ���\n");                

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("��Ļ����Ṧˮƽ���ޣ��޷���������������ֻؽ���\n"); 

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷���������������ֻؽ���\n"); 
                                                
        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("��Ļ����м�ˮƽ���ޣ��޷���������������ֻؽ���\n"); 
                                                                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail("�����ֻؽ�������޷��򵥵�ͨ����ϰ������\n");
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 350) return 120;
        return 150;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 200;
        if (lvl < 250) return 300;
        if (lvl < 350) return 400;
        return 500;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{

        string *desc;
        object weapon;
        
        weapon=query_temp("weapon", me);
        
        if (! objectp(weapon))return damage_bonus;
        
        desc = ({
                HIY "$N" HIY "΢Цһ�������赭д������" + weapon->name() + HIY "����һ�����������$n" HIY "��\n" NOR,
                HIG "$N" HIG "�������������������������������⻯������ؽ�$n" HIG "���֡�\n" NOR,
                HIR "$N" HIR "��������" + weapon->name() + HIR "��ɷʱ����ͻ�䣬���Ϯ����$n" HIR "ֻ��������˵���������ܡ�\n" NOR,
        });
        
        if (me->is_busy() 
           || random(4) >= 1
           || ! living(victim) 
           || damage_bonus < 120 
           || query("neili", me)<500
           || me->query_skill("lunhui-sword", 1) < 700) 
                return 0; 

        // ׷����Ч
        victim->receive_wound("qi", damage_bonus * 2, me);
        // 1200������׷��50%�˺�
        if (me->query_skill("lunhui-sword", 1) >= 1200)
                victim->receive_wound("qi", damage_bonus / 2, me);
        
        if (random(3) == 1)victim->start_busy(3 + random(3));
        
        if( random(10) == 1)addn("neili", -1*me->query_skill("lunhui-sword",1)*2, victim);
        
        return desc[random(sizeof(desc))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, cost;

        if ((int)me->query_skill("lunhui-sword", 1) < 350
           || me->query_skill_mapped("parry") != "lunhui-sword"
           || query("neili", me)<200
           || ! living(me))
                return;

        
        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force", 1) * 4 + ob->query_skill("martial-cognize", 1);
        dp = me->query_skill("lunhui-sword", 1) * 6 + me->query_skill("martial-cognize", 1);

        if( query("reborn/times", ob) < 4 )dp+=1000;
        
        if (dp + random(dp / 2) >= ap)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIW "΢΢һЦ��������һ�����⣬��ʧ�ˡ�\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "$n" HIW "������磬���˷���������$N" HIW "���л��⡣\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" HIW "������������ǰ�������罫��Χס�����κ���ʽ���޴ӹ�����\n" NOR]);
                        break;
                }
                return result;
        }
}
string perform_action_file(string action)
{
        return __DIR__"lunhui-sword/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"lunhui-sword/exert/" + action;
}

int difficult_level()
{
        return 25000;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("lunhui-sword", 1); 

        if( lvl >= 500 && 
            !query("can_perform/lunhui-sword/xiuluo", me) )  
        { 
                tell_object(me, HIC "��ͨ�����ֻؽ���" HIR "���޽���" HIC "���İ��ء�\n" NOR);     
                set("can_perform/lunhui-sword/xiuluo", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 600 && 
            !query("can_perform/lunhui-sword/lan", me) )  
        { 
                tell_object(me, HIC "��ͨ�����ֻؽ���" HIR "������" HIC "���İ��ء�\n" NOR);     
                set("can_perform/lunhui-sword/lan", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }
}
