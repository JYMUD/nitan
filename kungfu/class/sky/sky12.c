#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "��ʮ�����졿" NOR);
        set("long", HIW @LONG

                ʮ��         ��         ��

    ����һƬ��ʣ�ãã�ƺ������ܲ����κ����Զ��һ���Ʋʴ�
�������𣬼�����һ������(yunti)���ƺ������ϲ����ʡ�������

LONG NOR );
        set("item_desc", ([
                "yunti" : HIW "\nһ���ɫ���Ʋʰεض��������ϲ����ʡ�\n" NOR,
]));
        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/vin": 1,
        ]));
        set("sky", 1);
        setup();
}

void init()
{
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
                if ( objectp(present("vin", environment(me)))
                  && me->query("sky12/floor") < 13)
                {
                        write(CYN "ֻ��һ����ӰͻȻ�ζ�����������ǰ��\n" NOR);
                        write(HIC "��ԯ��˵����Ҫ��ȥ���Ȱ������һ��" HIR "��Ը" NOR "��\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "˳����������һ"
                               "�ݣ��������������Ʈ����ȥ����\n"
                               NOR, this_player());
                me->move("/kungfu/class/sky/sky13"); 
                return 1;
        }
        return 0;
}

