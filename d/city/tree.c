#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM; 

void create()
{
        set("short", "��������");
        set("long", @LONG
�����Ǵ����Ķ��ˣ�����ȫ��Ũ�ܵ�֦Ҷ��ʪ������̦޺��һ��
΢�紵������Ҷ���������������������������ȥ��ֻ����һ�����Σ�
���뻹�ǸϿ���ȥ�ɡ�
LONG );
        set("no_fight", 1); 
        set("valid_startroom", 1); 
        set("no_sleep_room",1); 
        set("outdoors", "city");
        set("item_desc", ([
                "tree" : GRN "\n����һ�þ޴���ϵĴ���"
                         "����֦Ҷ�ǳ���ï�ܡ�\n" NOR,
        ]));
        set("exits", ([
                "down" : __DIR__"guangchang",
                "up"  : __DIR__"tree2",
        ]));
        set("objects", ([
               // CLASS_D("xiakedao") + "/shi" : 1,
        ]));
        setup();
        call_other("/clone/board/comm_b", "???");
}

void init() 
{
        add_all_action(); 
        add_action("do_jump", ({ "tiao", "jump" }) );
        add_action("do_climb", ({ "pa", "climb" }) );
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

                me->move(__DIR__"tree2");
                
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

int do_jump(string arg)
{
        object me;
        me = this_player();
        
        if( !arg || arg != "down") return notify_fail("��Ҫ��������\n");
        
        if( me->is_busy() )  
                return notify_fail("����æ���أ�\n");
        
        message("vision",
                me->name() + "��ԥ��һ�£�����������������ȥ��\n���ء���һ���죬�ƺ�����"+me->name()+"�Һ���һ��!\n",
                environment(me), ({me}) );
        
        me->move(__DIR__"guangchang");
        message("vision",
                me->name() + "�Һ�һ���������ϵ���������\n",
                environment(me), ({me}) );
        
        return 1;
}

int valid_leave(object me, string dir)
{

        if ( dir=="down" && !wizardp(me))
                return notify_fail("�̸���֪�����ĸ����һ￳����⣬����ֻ�����(tiao)��ȥ��\n");

        if ( dir=="up" && !wizardp(me))
                return notify_fail("����û��ֱ���ߣ�������ֻ����(climb)��ȥ��\n");

        return 1;
}
