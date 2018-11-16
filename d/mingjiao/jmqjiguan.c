#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "��ľ�����");
        set("long", @LONG
����ǰ��Ȼһ���������У�ֻ������ǰ�󣬵�����������ǵص�
��֪���ľ����������ɰأ�������ɼ������һ����ʵ��֦Ҷ��һ��
���ɡ��������գ�������ա����ƺ���ʧ�˷�����ûͷ��Ӭ�㵽
���Ҵ���
LONG );
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        if (this_player()->query_family() == "����") return;
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIG"ͻȻһ���ľ׮��������������$N��\n"NOR, this_player());
}

int valid_leave(object me, string dir)
{
        int total_steps ;
        mapping myfam;

        total_steps = 10 ;
        if ( total_steps <= 0 ) total_steps = 1 ;
        myfam = (mapping) query("family", this_player());
        if(myfam && myfam["family_name"] == "����")
                total_steps = 1 ;
        if ( dir == "west")
                addn_temp("mingjiao/steps",1,me);
        if ( dir == "east")
                addn_temp("mingjiao/steps",-1,me);

        if (query_temp("mingjiao/steps", me) == total_steps)
        {
                me->move(__DIR__"jmqshenmu");
                delete_temp("mingjiao/steps", me);
                tell_object(me, "�����˰��죬�����ߵ���ľ������! \n");
                return 1;
        }

        if (query_temp("mingjiao/steps", me) == - total_steps )
        {
                me->move(__DIR__"jmqshulin6");
                delete_temp("mingjiao/steps", me);
                tell_object(me, "�����˰��죬�����ߵ���ľ������! \n");
                return 1;
        }

        return ::valid_leave(me,dir);
}