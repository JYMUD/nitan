// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����������ڶ�����ʪ�쳣������ˮ��ſ�׹�£����ڵ����Сˮ��
�У��������졣�������̫���������Ҫ����������
LONG );

        set("exits", ([
                "east"  : __FILE__,
                "south" : __DIR__"neidong",
                "west"  : __DIR__"neidong",
                "north" : __DIR__"neidong",
        ]));

        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_use","use");
}

int do_use(string arg)
{
        object me = this_player();

        if (! arg || arg == "") 
                return 0;
                
        if (! present("fire", me))  
                return 0;
                
        if (arg == "fire") 
        {
                tell_object(me, "���Ż��ӳ�գ����߳����⡣\n");
                     me->move(__DIR__"qingyin");
        }
        return 1;
}

int valid_leave(object me, string dir)
{
        int kar;

        kar=80-query("kar", me);

        if (random(kar) == 1) 
        {
                tell_object(me, "���ߵþ�ƣ���������ڵ��˶��⡣\n");
                me->move(__DIR__"qingyin");
                return 1;
        }

        return ::valid_leave(me,dir);
}