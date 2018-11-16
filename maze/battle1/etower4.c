// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ʯ��");

        set("long",@LONG
����ɽʯ�������ս���У�Ҳ��֪ͨ���δ���ֻ��Ũ����죬Խ
��Խ����ɭ����ʱ����Ұ�޺����������������з�ë��
LONG);

        set("exits",([
                "up" : __DIR__"etower5",
                "down" : __DIR__"etower3",
        ]));
        
        set("objects", ([
                __DIR__"npc/guarder" : 1,
        ]));
                
        set("outdoors", "battle");
        setup();
}

void init()
{
        string team_name;
        object ob;
        
        team_name = query("team_name", get_object(__DIR__"etang"));
        ob = present("guarder", this_object());
        if( objectp(ob) && !query_temp("battle/team_name", ob) )
                set_temp("battle/team_name", team_name, ob);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        object ob, wp, *inv;
        int i, j=0;

        if( dir == "up" )
        {
                if( objectp(ob = present("guarder", this_object())) )
                {
                        if( query_temp("battle/team_name", me) != query_temp("battle/team_name", ob) )
                        {
                                if( objectp(wp=query_temp("weapon", ob)) )
                                        message_vision("$N��$n�ȵ�������аħ������Ҫ�����·���������������е�"
                                                +query("name", wp)+"��Ӧ����Ӧ��\n",ob,me);
                                else
                                        message_vision("$N��$n�ȵ���ֻҪ���ڣ�����аħ���������������·��\n", ob, me);
                                return notify_fail("\n");
                        }
                }
        }

        return ::valid_leave(me, dir);
}
