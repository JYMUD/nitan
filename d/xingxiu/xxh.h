// Room: /d/xingxiu/xxh.h
// Last Modified by winder on Apr. 25 2001

int valid_leave(object me, string dir)
{
        if ( dir == "north")
              if( userp(me))addn_temp("mark/steps", 1, me);
        if ( dir == "south")
              if( userp(me))addn_temp("mark/steps", -1, me);
        if ( dir == "west")
              if( userp(me))addn_temp("mark/step", 1, me);
        if ( dir == "east")
              if( userp(me))addn_temp("mark/step", -1, me);
        if( query_temp("mark/steps", me) >= 6 )
        {
                me->move(__DIR__"huangdi");
                delete_temp("mark/steps", me);
                delete_temp("mark/step", me);
                tell_room(environment(me), me->name()+"���ϱߵ����޺����˹�����\n", ({ me }));
                return notify_fail("���۵ð���������߳������޺���\n");
        }
        if( query_temp("mark/steps", me) <= -6 )
        {
                me->move(__DIR__"xxh");
                delete_temp("mark/steps", me);
                delete_temp("mark/step", me);
                tell_room(environment(me), me->name()+"�ӱ��ߵ����޺����˹�����\n", ({ me }));
                return notify_fail("���۵ð���������߳������޺���\n");
        }
        if( query_temp("mark/step", me) <= -3 )
        {
                me->move(__DIR__"xiaolu");
                delete_temp("mark/steps", me);
                delete_temp("mark/step", me);
                tell_room(environment(me), me->name()+"�����ߵ����޺����˹�����\n", ({ me }));
                return notify_fail("���۵ð���������߳������޺���\n");
        }

        if( query_temp("mark/step", me) >= 3 )
        {
                me->move(__DIR__"xiaojing");
                delete_temp("mark/steps", me);
                delete_temp("mark/step", me);
                tell_room(environment(me), me->name()+"�Ӷ��ߵ����޺����˹�����\n", ({ me }));
                return notify_fail("���۵ð���������߳������޺���\n");
        }
        return ::valid_leave(me,dir);
}
