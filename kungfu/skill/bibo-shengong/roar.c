// roar.c 
// by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<600
        ||  (int)me->query_skill("bibo-shengong", 1) < 50)
                return notify_fail("����������������Ľ���һ��, ��������˼�ֻ����\n");
                
        skill = me->query_skill("force", 1) / 4 + me->query_skill("bibo-shengong", 1);
        addn("neili", -150, me);
        me->receive_damage("qi", 10);
        
        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ�ܹ�������! \n");

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "��������˼�ȫ����������" 
                        "һ�����̺�������ԶԶ�Ĵ��˿�ȥ��������ֹ��\n" NOR, me); 
        
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++) 
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;
                        
                if (! living(ob[i]) || wizardp(ob[i]) || 
                    (query("age", ob[i])<17 && userp(ob[i])) )
                        continue;
                        
                
                if (skill / 2 + random(skill / 2) < (int)ob[i]->query_skill("force"))
                        continue;
 
                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
                      
                damage=skill-(query("max_neili", ob[i])/30);
                if (damage > 0) 
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me );
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "��ֻ������ǰһƬģ��������" 
                                    "���ƺ�������ɽ�����������......\n"); 
                }
        }
        return 1;
}