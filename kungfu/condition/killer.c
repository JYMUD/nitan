int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, "官府不再通缉你了！\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "因为" + me->name(1) + "一直没能被" +
                        "缉拿归案，听说官府已经取消了通缉令。");
                return 0;
        }

        if( query("no_fight", environment(me)) || 
            query("room_owner_id", environment(me)) )
        {
                int i = random(30);
                
                me->receive_damage("jing",query("max_jing", me)/5);
                me->receive_damage("qi",query("max_qi", me)/5);
                me->receive_wound("jing",query("max_jing", me)/10);
                me->receive_wound("qi",query("max_qi", me)/10);
                if ( i > 20) 
                        tell_object(me, "一道闪电划过长空，你想起以前为非作歹的事迹，不由得心发虚！\n"  );
                else 
                if (i > 10)  
                        tell_object(me, "天空中响起了滚滚雷声，你怔怔地望着天喃喃自语：我做了这么多坏事，该不会被天遣吧！\n");
                else 
                        tell_object(me, "你觉得背脊一凉，打心底涌起了一股寒意：鬼！！\n");

                set_temp("die_reason", "遭天遣而死", me);
        }

        me->apply_condition("killer", duration - 1);
        return 1;
}
