#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "�������졿" NOR);
        set("long", HIW @LONG

                ��         ��         ��

    ����һƬ��ʣ�ãã�ƺ������ܲ����κ����Զ��һ���Ʋʴ�
�������𣬼�����һ������(yunti)���ƺ������ϲ����ʡ�������

LONG NOR );
        set("item_desc", ([
                "yunti" : HIW "\nһ���ɫ���Ʋʰεض��������ϲ����ʡ�\n" NOR,
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/ultra/kuihua": 1,
                __DIR__"npc/ultra/dugu": 1,
                __DIR__"npc/ultra/huoshan": 1,
                __DIR__"npc/ultra/huang": 1,
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
                if ( (objectp(present("huang shang", environment(me)))
                  || objectp(present("dugu qiubai", environment(me)))
                  || objectp(present("huo shan", environment(me)))
                  || objectp(present("kuihua taijian", environment(me))))
                  && me->query("sky12/floor") < 8)
                {
                        write(CYN "ֻ��һ����ӰͻȻ�ζ�����������ǰ��\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "˳����������һ"
                               "�ݣ��������������Ʈ����ȥ����\n"
                               NOR, this_player());
                me->move("/kungfu/class/sky/sky8"); 
                return 1;
        }
        return 0;
}

