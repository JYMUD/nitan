#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "��һ���졿" NOR);
        set("long", HIW @LONG

                һ         ��         ��

    ����һƬ��ʣ�ãã�ƺ������ܲ����κ����Զ��һ���Ʋʴ�
�������𣬼�����һ������(yunti)���ƺ������ϲ����ʡ�������


LONG NOR );

        set("exits", ([
                "out" : __DIR__"tianmen",
]));
        set("item_desc", ([
                "yunti" : HIW "\nһ���ɫ���Ʋʰεض��������ϲ����ʡ�\n" NOR,
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/tie": 1,
        ]));
        set("sky", 1);
        setup();
}

void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "�����׶���˵������û��ʹ�ù������ӣ�����ô��������ģ��ߣ�\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        
        add_action("do_move", "jump");
        add_action("do_move", "move");
        add_action("do_move", "tiao");
        add_action("do_move", "enter");
        add_action("do_move", "up");
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "yunti")
        {
                if ( objectp(present("tie chuanjia", environment(me)))
                     && me->query("sky12/floor") < 2)
                {
                        write(CYN "ֻ��������һ�����ȣ�����λ" +
                              RANK_D->query_respect(me) + CYN
                              "����ͣ������\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "˳����������һ"
                               "�ݣ��������������Ʈ����ȥ����\n"
                               NOR, this_player());
                me->move("/kungfu/class/sky/sky2"); 
                return 1;
        }
        return 0;
}

