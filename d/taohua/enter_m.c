// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "ʯ�����");
        set("long", @LONG
����һƬ������ɰʯ̲���ϱ���һ��СС�ĸ��壬�����ƺ���һ����
ʯ�󣬵���һ�ɱ�����������ʯ��ʹ�˿����������о�����ͨ������
��ΨһС·�ֱ�һ���ʯ��(shibei)��ס��
LONG );

        set("exits", ([
                "south" : __DIR__"harbor",
        ]));

        set("item_desc", ([
                "shibei" : "
ʯ������ʮ�ֹ⻬���ƺ�������������Ħ���������м����֣�
����������ص�������������˳��֪�����档
\n",
        ]));

        set("coor/x", 8970);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
}

void init()
{
         add_action("do_push", "push");
}


int do_push(string arg)
{
        object me = this_player();

        if (!arg || arg != "shibei")
                return notify_fail("ʲ�᣿\n");

        if( me->query_str()<25 && query("combat_exp", me)>100000 )
        {
                return notify_fail("��û��ô�������ᶯʯ����\n");
        }

        /*
        if( (query("age", me)-query("taohua_maze", me))<query("taohua_maze2", me) )
                return notify_fail("�������ͨ���һ������������������\n");
        */

        message_vision(HIW "ʯ������������棬ʯ����ӿ��һ�ɹַ�Ю��Ũ����$N������\n"
                       "$N��Ӱ��ʱ��ʧ��Ũ��֮��......\n\n\n\n\n" NOR, me);

        if( query("taohua_maze", me) )
                me->move("/d/taohua/maze/zhongshu");
        else
                me->move("/d/taohua/maze/maze"+(random(63)+1));

        return 1;
}