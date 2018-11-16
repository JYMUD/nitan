// mj_tasting.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        object monk,room;
        room = load_object("/d/mingjiao/gangmingding");
        monk = present("yin tianzheng", room); 
        if (duration < 1) {
                addn("start_tast", -1, monk);
                tell_object(me, HIY "��Ļ���ʱ�䵽�ˣ�����Ӧ�û�ȥ�����ˡ�\n" NOR);
                delete_temp("protecting", me);
                delete_temp("protect", me);
                set_temp("finish_tast", 1, me);
                set_temp("tast_count",query_temp("tasted",  me), me);
                return 0;
        }
        if (!duration) return 0;
        me->apply_condition("mj_will_tast", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}