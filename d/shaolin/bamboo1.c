// Room: /d/shaolin/bamboo1.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һƬ���ܵ����֡������˼�������Ω�����ߵ��·�棬��ɮ
��ľ������΢�紵����Ҷ�������������������˳���Ϊ֮һ�ӣ�����
���ѵ��������ڡ�
LONG );
        set("exits", ([
                "northeast" : __DIR__"bamboo"+(random(13)+1),
                "southwest" : __DIR__"bamboo2",
                "northwest" : __DIR__"bamboo"+(random(13)+1),
                "southeast" : __DIR__"bamboo"+(random(13)+1),
                "south" : __DIR__"qfdian",
        ]));
        create_door("south","ľ��","north",DOOR_CLOSED);
        set("outdoors", "shaolin");
        set("no_clean_up", 0);
        setup();
}

void init()
{
        set_temp("bamboo/count", 0, this_player());
}

int valid_leave(object me, string dir)
{
        if( dir == "southwest")addn_temp("bamboo/count", 1, me);
        else if( dir == "south" ) delete_temp("bamboo/count", me);
        else addn_temp("bamboo/count", -1, me);

        return ::valid_leave(me, dir);
}
