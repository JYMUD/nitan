int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, "�ٸ�����ͨ�����ˣ�\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��Ϊ" + me->name(1) + "һֱû�ܱ�" +
                        "���ù鰸����˵�ٸ��Ѿ�ȡ����ͨ���");
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
                        tell_object(me, "һ�����绮�����գ���������ǰΪ���������¼������ɵ��ķ��飡\n"  );
                else 
                if (i > 10)  
                        tell_object(me, "����������˹������������������������������������ô�໵�£��ò��ᱻ��ǲ�ɣ�\n");
                else 
                        tell_object(me, "����ñ���һ�������ĵ�ӿ����һ�ɺ��⣺����\n");

                set_temp("die_reason", "����ǲ����", me);
        }

        me->apply_condition("killer", duration - 1);
        return 1;
}
