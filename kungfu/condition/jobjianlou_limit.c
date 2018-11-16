#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        object room;
        object obb;
        int step;
        string site;

        if (duration < 1) return 0;  
        
        me->apply_condition("jobjianlou_limit", duration - 1);  
        room = environment(me);     

        if( query_temp("guo_shoucheng/where", me) )
        if( query_temp("guo_shoucheng/where", me) != query("site", room )
         && !query_temp("guo_shoucheng/job_over", me) )
        {
                message_vision(HIY "һ���α��ܹ�����$N˵�������Ȼ�������ӣ�" +
                               "��ȥ��������ˣ�\n" NOR, me);

                set_temp("guo_shoucheng/failed", 1, me);
                me->apply_condition("jobjianlou_limit", 0);  
        }

        if( query_temp("guo_shoucheng/start_job", me )
         && query_temp("guo_shoucheng/where", me) == query("site", room) )
        {
                if (duration % 2 == 0 && duration > 20)     
                {
                        step = random(9) + 1;
                        message_vision(HIY "��Ȼ$N�Ӽ�����ƺ���������" HIW + chinese_number(step) +
                                       HIY "������һ��" HIR "�ɹż���" HIY "��̽ͷ̽�ԡ�\n" NOR, me);
                        obb = new("/quest/quest5/job2/robber4");
                        obb->move("/d/xiangyang/"+query("site", room)+step);
                        obb->change_ob(me);
                        set("where",query("site",  room), obb);
                } else
                if (duration % 10 == 0)  
                        message_vision(HIY "$Nͨ������ھ����Ѳ���ų���������" +
                                       "���Ǻ���û�з����κε��顣\n" NOR, me);
        }

        if (me->is_ghost())
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobjianlou_limit", 0);
                return 0;
        }

        if (duration == 1
         && query_temp("guo_shoucheng/where", me) == query("site", room) )
        {
                message_vision(CYN "\nһ���س��α��ܹ���˵�����ɹ�������ʱ�������ˣ�" +
                               "$N���Ի�ȥ�����ˣ�\n"NOR,me);
                if( query_temp("guo_shoucheng/start_job", me) )
                        set_temp("guo_shoucheng/job_over", 1, me);
                delete_temp("guo_shoucheng/start_job", me);
                me->apply_condition("jobjianlou_limit", 0);     
        }
        return CND_CONTINUE;      
}

