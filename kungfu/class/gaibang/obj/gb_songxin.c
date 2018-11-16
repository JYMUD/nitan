// Last Modified by winder on Nov. 15 2000
// gb_songxin.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        int time;
        time=query_temp("songxin_time", me);
        me->set("no_get");

        if (duration < 1)
        {
                if( query_temp("gb_songxin", me) )
                {
                        tell_object(me, HIY "��ʱ���ѹ�������ʧЧ��\n" NOR);
                }
                delete_temp("gb_songxin", me);
                delete_temp("songxin_name", me);
                delete_temp("songxin_zuji", me);
                delete_temp("songxin_target_name", me);
                delete_temp("letter_steal", me);
                delete_temp("zuji", me);
//                me->delete_temp("wait");
                set_temp("gb_songxin_late", 1, me);
                   me->clear_condition("gb_songxin");
//this is dest letter
                if(present("secret letter", me))
                        destruct(present("secret letter", me));
                return 0;
        }
        if (!duration) return 0;
/*    
        if (random(10)>3)
        {
                if( query("tili", me)<80 )
                {
                        tell_object(me, RED "�������������ţ�����̫�ྫ����������ͣ����Ъһ�£�\n" NOR);
                        set_temp("wait", 1, me);
                        me->start_busy(1);
                }
                else
                {
                        addn("tili", -50+random(50), me);
                        delete_temp("wait", me);
                }
        } 
*/
//���ٱ����Ļ���
        if(duration > time/7 && present("secret letter", me) &&
                !query_temp("wait", me) && duration<time && 
                !query_temp("songxin_zuji", me) && random(10)>7 && 
                (interactive(me)) && !query("no_fight", environment(me)) && 
                query("disable_type", me) != "<���Բ���>" )
        {
                tell_object(me, HIY "�������Щ����ƺ����˸������ˣ�\n" NOR);
                me->start_busy(1);
                call_out("zuji", 0, me);    
        }
        me->apply_condition("gb_songxin", duration - 1);
        return 1;
}

void zuji(object me)
{
        object obj; 
        if (present("secret letter", me)) 
        {
                tell_object(me,"����Լ�о�������Χ�˹�������!!! \n");
                if (random(10)>9)
                {
//this is killer kill npc
                        tell_object(me, RED "��⣡����Ҫ����!\n" NOR);

                        obj = new("/kungfu/class/gaibang/npc/npc1");
                        set("target", me, obj);
                        obj->move(environment(me));
                        set_temp("songxin_zuji", 1, me);

                        if( query("combat_exp", me)>300000 )
                        {
                                call_out("killer_clone", 1, me);    
                        }
                }
                else
                {
//this is stealer steal letter
                        obj = present("secret letter", me);
                        destruct(obj);
                        tell_object(me,RED"���������������һ���´������ã��ű�͵��!\n"NOR);
                        set_temp("songxin_zuji", 1, me);
                        obj = new("/kungfu/class/gaibang/npc/snpc1");
                        set("target", me, obj);
                        obj->move(environment(me));
  
                        if( query("combat_exp", me)>300000 )
                        {
                                call_out("stealer_clone", 1, me);    
                        }
                }
        delete_temp("gb_songxin", me);
        delete_temp("songxin_name", me);
        delete_temp("songxin_zuji", me);
        delete_temp("songxin_target_name", me);
        delete_temp("letter_steal", me);
        delete_temp("zuji", me);
//        me->delete_temp("wait");
        set_temp("gb_songxin_late", 1, me);
           me->clear_condition("gb_songxin");
        }
        else
        {
                tell_object(me,"�����ͳ��������ҵĶ����һ��׷ɱ!\n");
        }   
    return;
}

void killer_clone(object me)
{
        object obj;

        tell_object(me,"��⣬�ֳ������˸��ˡ���!!! \n");
        obj = new("/kungfu/class/gaibang/npc/npc2");
        set("target", me, obj);
        obj->move(environment(me));
        return;
}

void stealer_clone(object me)
{
        object obj;

        tell_object(me,"��⣬�ֳ������˸��ˡ���!!! \n");
        obj = new("/kungfu/class/gaibang/npc/snpc2");
        set("target", me, obj);
        obj->move(environment(me));
        return;
 }

string query_type(object me)
{
        return "job";
}
