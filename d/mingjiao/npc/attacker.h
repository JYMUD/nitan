void init()
{
        object ob, me = this_player();
        if ( interactive(me) 
           && query_temp("mj/xunluo", me )
           && query_temp("mj/attacker", me )
           && query("outer_times", random(this_object())) == 1
          ) {
                 ob = new("/d/mingjiao/npc/attacker");
                 message_vision("\nһ����ӰͻȻ�������˳�������ס$N��ȥ·��\n\n", me); 
                 ob->move(environment(me));
                 addn_temp("mj/attacker", 1, me);
                 addn_temp("mj/attacker1", 1, me);
                 ob->do_copy(me);
                 ob->kill_ob(me);
        }
}

int valid_leave(object me, string dir)
{
        object ob;
        if( query_temp("mj/xunluo", me )
          && objectp(ob=present("attacker", environment(me)))
           && query("victim", ob) == query("id", me )
          && !userp(ob))
            return notify_fail(ob->name()+"һ�Բ�����������������ǰ��\n");
            return ::valid_leave(me, dir);
} 
