#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʥ��");
        set("long", @LONG
��ǰ����������ʥ���������ĺ��浹Ӱ������Ͱ��ƣ�����ˮ
�������Ŀ���������̻Ի͵�ѩɽ�������ɼ�����Զ���Ǽ��������
��ѩɽ��������ߴ������ɽ���ഫɽ�������ɾ�ס��ѩɽ���ڻ���
ѩˮ��������С�������Χȴ�Ǳ���Ũ�����������֣�ʹ�����ǰһ
Ƭ���ʣ��Ʋ������ܡ�
LONG );
        set("resource/water", 1);
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "xuedao");

        setup();
}

int valid_leave(object me, string dir)
{
        int total_steps;

        if (! userp(me)
            || query("family/family_name", me) == "ѩɽ��"
            || query("family/family_name", me) == "Ѫ����" )
        {
                total_steps = 1; 
        } else
        {
                me->receive_damage("jing", 5);
                me->receive_wound("jing", 5);
                message_vision(HIM "\nͻȻ��$N" HIM "������ǰ�ľ�����"
                               "Щ���ң���������ͷ��Ŀѣ��\n\n" NOR, me);

                total_steps = 5;
        }

        if (dir == "east")
                addn_temp("taohua/steps", 1, me);

        if (dir == "south")
                addn_temp("taohua/steps", -1, me);

        if( query_temp("taohua/steps", me) == total_steps )
        {
                me->move(__DIR__"hubian1");
                delete_temp("taohua/steps", me);
                write(HIC "\n����ɢ���������ǰ��Ȼ����������\n\n" NOR);
                return -1;
        }  

        if( query_temp("taohua/steps", me) == -total_steps )
        {  
                me->move(__DIR__"tulu3");
                delete_temp("taohua/steps", me);
                write(HIC "\n����ɢ���������ǰ��Ȼ����������\n\n" NOR);
                return -1;
        }

        return ::valid_leave(me, dir);
}