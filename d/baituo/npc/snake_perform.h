// Code of JHSH

#include <ansi.h>

int auto_perform_duwu()
{
        object me = this_object();
        object *target;
        int damage, poison, i;

        poison=query("snake_poison", me);
        target = all_inventory(environment(me));

        if( me->is_busy() ) return 0;

        if( query("jingli", me)<poison)return 0;
        
        message_vision(HIR"���$NѪ�����ͷһ��һ������״�ɲ�����Ȼ�ſڣ��������һ�����\n\n"NOR,me);

        for(i=0; i<sizeof(target); i++) {

                if( !living(target[i]) || target[i] == me || query("race", target[i]) == "����")continue;

                if( random(poison) > target[i]->query_skill("force") || !living(target[i]) )
        {
                        damage=random(poison*10-query("neili", target[i]));
                        if(damage > 800) damage = 800;
                        if(damage < 100) damage = 100;

                     target[i]->affect_by("snake_poison",
                              ([ "level" : poison + random(poison),
                                 "id":query("id", me),
                                 "duration" :  poison]));

                        target[i]->receive_damage("qi", damage,  me);
                        target[i]->receive_wound("qi", random(damage), me);
                        target[i]->start_busy(1+random(2));
                        message("vision", target[i]->name() + "������΢΢һ�Σ��е����㲻����\n", environment(me), target[i]);
                        tell_object(target[i], RED"��ͻȻ�е�һ��ͷ�Σ�ԭ��"+me->name()+"������ĺ����Ǿ綾֮��ڿ�����ɢ���������������߶���\n"NOR);
                }
                else {
                        tell_object(target[i], WHT"��������ס���������������߶���\n"NOR);
                }
        }
        me->start_busy(1);
        addn("jingli", -(random(50)+poison/3), me);

        return 1;
}

int auto_perform_chan()
{
        object me = this_object();
        object target = me->select_opponent();
        object owner;
        object here = environment(me);
        int damage;

        if( query("jingli", me)<500)return 0;

        if( query("race", target) == "����")return 0;
        if( me->is_busy() || query_temp("snake_chan", target))return 0;

        set_temp("try_chan", 1, me);
        set("default_actions", (:call_other,__FILE__,"query_action":), me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        set("default_actions", (:call_other,"/adm/daemons/race/snake.c","query_action":), me);
        delete_temp("try_chan", me);
        return 1;
}

int auto_perform_double()
{
        object me = this_object();
        object target = me->select_opponent();

        if( me->is_busy() || !living(me) ) return 0;

        set("default_actions", (:call_other,__FILE__,"query_action":), me);
        set_temp("double_hit", 1, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        set_temp("double_hit", 2, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        delete_temp("double_hit", me);
        set("default_actions", (:call_other,"/adm/daemons/race/snake.c","query_action":), me);

        return 1;
}

mapping query_action()
{
       object me = this_object();
        string msg1, msg2;
        msg1 = HIR"�����������죬$N���Ѵ�ǰ��"+(random(2)?"��":"��")+"�ߵ���ͷ˻˻���ţ���Ȼҧ��$n��$l"NOR;
        msg2 = RED"һ�ڲŸ�ҧ����ȴ��$N��һ��ͷҲת��������������ҧ��$n$l"NOR;

        if( query_temp("double_hit", me) )
        return ([
        "action":query_temp("double_hit", me) == 1?msg1:msg2,
        "force" : 400,
        "dodge" : 10,
        "parry" : 10,
        "damage" : 400,
        "weapon" :"����",
        "damage_type":"ҧ��"]);

        else return ([
        "action": HIR"���$N���ɶ೤������һ�ˣ���Ȼ��$n���Ͼ���"NOR,
        "force" : 400,
        "dodge" : 0,
        "parry" : 0,
        "damage" : 400,
        "weapon" :"����",
        "damage_type":"����"]);
}
