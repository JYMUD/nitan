// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��������ȫ������ɫ�����ɣ������������٣�ʹ��һ��֮������
�������⡣��Χ�����滨��ݣ���֮������ס������俴�ƴֲڣ���ϸ��
֮�£�ȴ�������Ᾱ�����ܾ����Ȼ��ɣ���ͬ��Ȼ���ɵ�һ�㣬������
�ɶ��칤����һƬ�������졣��������С��ͨ���һ������ǰ��һ�԰�
��(diao)��
LONG );
         set("exits", ([
                       "west"  : __DIR__"taolin",
                "south" : __DIR__"bibochi",
                "enter" : __DIR__"shuilong",
        ]));

        set("item_desc", ([
                "diao" : "һ�԰׵���չ�����ɡ�������һ����ĵ��ӣ�\n"
                "����(mount)�Ϳ��Էɵ���ԭ��\n",
        ]));
        
         set("objects", ([
                 "/d/taohua/npc/shagu" : 1,
                "/d/taohua/npc/shitong" : 1,
                CLASS_D("taohua") + "/first" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        "/clone/board/taohua_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( (query("family/master_name", me) != "��Ӣ" )
         && (query("family/master_name", me) != "��ҩʦ" )
         && userp(me)
         && (!query_temp("shagu_pass", me) )
        && (dir == "enter")
        && present("sha gu", this_object()) )
        return notify_fail("\nɵ��ɵЦ�˼������쿪˫��һ����˵����Ҫ��ȥ��������һ����ɣ�\n�����˶������ң������ˣ�\n");
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_ride", "mount");
}
int do_ride(string arg)
{
        mapping myfam;
        object ob = this_player () ;
        
        myfam=query("family", ob);
/*
        if( !myfam || myfam["family_name"] != "�һ���" || !query("out_family", ob) )
        {
                message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻ��Ȼһ��......\n" +
                               HIR "���$Nˤ�˸��������ף�\n" NOR +
                               "�����׵��$N��������Ȥ����ֻ��ʶ�һ����ĵ��ӡ�\n" , ob ) ;
                ob -> receive_damage ("qi", 50) ;
                ob -> receive_wound  ("qi", 50) ;
                return 1;
        }
*/
        if( (int)query("sb_ride") ) 
                return notify_fail("���ڰ׵���æ��,���һ���ٳ���!\n" ) ;
        addn("sb_ride", 1) ;
        message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻչ��߷ɡ�\n\n"
                       "����һ��һ�����ν�����С������������\n" , ob );
        ob->move("/d/taohua/lantian") ;
        tell_object(ob, CYN  "\n�㲻�ϵط�ѽ�ɣ���ˮǧɽ����Ʈ�� ......\n\n" NOR ) ;
        call_out("taohua", 2 , ob );
        addn("sb_ride", -1) ;
        return 1 ;
}
void taohua( object ob )
{
        if (base_name(environment(ob)) != "/d/taohua/lantian")
                return;
        tell_object(ob, "�����ڷɵ�����ԭ���׵�����������\n\n"  ) ;
        ob -> move ("/d/guiyun/dayuan");
}
