#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short", "�һ�����");
        set("long", @LONG
����Ƭ�һ��ĺ�������һ���޼�ȫ��ʢ�����һ���΢��
��������Ӣ�ͷס���Χ�����ĵġ�Զ��ż������һ����С���
���в���������������������ȥ�ĺá�
LONG );
        set("outdoors", "taohua");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));             
}

int valid_leave(object me, string dir)
{
        int total_steps;

        if( query("family/family_name", me) == "�һ���"
           || me->query_skill("qimen-wuxing") >= 150)
        {
                total_steps = 1; 
        } else
        {
                    me->receive_damage("qi", 15);
                    me->receive_wound("qi", 15);
                    message_vision(HIM "\nͻȻ��һ���һ��������㼲"
                               "��$N" HIM "��\n\n" NOR, me);

                total_steps = 30;
        }

        if (dir == "north")
                    addn_temp("taohua/steps", 1, me);

        if (dir == "south")
                    addn_temp("taohua/steps", -1, me);

        if( query_temp("taohua/steps", me) == total_steps )
        {
                         me->move(__DIR__"tao_in");
                    delete_temp("taohua/steps", me);
                    write(HIC "\n�����˰��죬�����߳����һ�����\n\n" NOR);
                   return -1;
        }  

        if( query_temp("taohua/steps", me) == -total_steps )
        {  
                me->move(__DIR__"tao_out");
                    delete_temp("taohua/steps", me);
                    write(HIC "\n�����˰��죬�����߳����һ�����\n\n" NOR);
                return -1;
             }

        return ::valid_leave(me,dir);
}
