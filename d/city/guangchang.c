#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����㳡");
        set("long", @LONG
�����ǳ��е������ģ�һ���ܿ����Ĺ㳡��������ʯ���档����
���е��˳������������������������������ݡ�����һ�ô���
��(tree)�̸���ڣ��ݴ�����ǧ������䣬���������е���ʷ��֤��
���ɵײ���һ���ܴ������(dong)������Կ������������Ը��ص���
�����������������������У�һ�ɷ������󣬶��߲�ʱ�ش������ʵ�
��������������������������ˣ�һƬ�ྲ��
LONG );
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n����һ���ڲ����еĴ󶴣����治֪��"
                         "��Щʲô�Ź֡�\n" NOR,
                "tree" : GRN "\n����һ�þ޴���ϵĴ�������֦Ҷ�ǳ�"
                         "��ï�ܡ�\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

        set("objects", ([
                __DIR__"npc/jpl2": 1,
                __DIR__"npc/liapo" : 1,
                "/clone/npc/walker"  : 1,
        ]));

	set("coor/x", 0);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_climb", "climb");
        add_action("do_jump", "jump");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
        	return 0;

        if (arg == "dong")
        {
                if( objectp(query_temp("is_riding", me)) )
                        return notify_fail("û��˵��������������������ġ�\n");

                if (me->is_busy())
                {
                        return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
                        return 1; 
                }

                message("vision", HIC + me->name() + HIC "һ������������"
                                  "�˽�ȥ��\n" NOR, environment(me), ({me}));

                me->move("/d/gaibang/inhole");
                message("vision", HIC + me->name() + HIC "�Ӷ������˽���"
                                  "��\n" NOR, environment(me), ({me}));
                return 1;
        }
}


int do_jump(string arg)
{
        object room, me=this_player();
        if( !arg || arg != "up" ) return 0;

        room = get_object( "/adm/daemons/fairyland_quest/room_door_hj" );
        if( !room ) return 0;

        tell_room(environment(me),query("name", me)+"ʹ��������һ����ͻȻ����һ�����磬"+
                query("name", me)+"��ʱ����εò�֪���١�\n",me);

        write("��ʹ��������һ��������ƽ�ؾ���һ�����磬��������������ˡ��þ�����\n");
        me->move(room);
        tell_room(room,"��Ȼһ������Ϯ����"+query("name", me)+"�ѳ��������\n",me);
        return 1;
}

int do_climb(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "tree" || arg == "up")
        {
                if( objectp(query_temp("is_riding", me)) )
                        return notify_fail("û��˵�������������ﻹ�������ġ�\n");

                if (me->is_busy())
                {
                        return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
                        return 1; 
                }

                if( query("gender", me) != "Ů��" )
                        message("vision",
                                me->name() + "սս���������Ŵ��������̸���ƨ��һŤһŤ����������\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision",
                                me->name() + "����һ������ȹƮƮ�������Ӱ���ϴ�������\n",
                                environment(me), ({me}) );
                else 
                        message("vision",
                                me->name() + "սս������ץס����������ȥ��\n", 
                                environment(me), ({me}) );        

                me->move(__DIR__"tree");
                
                if( query("gender", me) != "Ů��" )
                        message("vision",
                                me->name() + "�������������������\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision","һ������������㶨��һ����"+
                                me->name() + "�Ѿ���������������ǰ��\n",
                                environment(me), ({me}) );
                else  
                        message("vision", me->name() + "սս�����ش���������������\n", 
                                environment(me), ({me}) );
                                
                return 1;
        }
}