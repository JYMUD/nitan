#include <ansi.h>
inherit ROOM;

int do_move(string arg);

void create()
{
        set("short", "Ĺ��");
        set("long", @LONG
���߹��˲ݵأ���ǰͻȻ��һƬ�����أ�ͻأ��������һ����Ĺ��
Ĺ������ʯͷ�Ѿ��ವ�ˣ����ĳ�����������Ĺ��Ĺǰû��������Ҳ
û���κεı�ǣ���֪������ǰ����λ�����󳼵�ĹѨ��Ĺ�ſڱ�һ
��Ĵ�ʯͷ(shi)��յ�˿����͸��
LONG );
        set("outdoors", "gumu");
        set("exits", ([
                "east"  : __DIR__"xuanya",
                "west"  : __DIR__"huangshalin",
                "north" : __DIR__"caodi",
        ]));

        set("objects", ([
               __DIR__"npc/yufeng" : 1+random(3),
               __DIR__"npc/sun" :  1,
        ]));

        set("item_desc", ([
               "shi": HIC "���ǿ��ʯ���²���������£��������š�" NOR + YEL"����ʯ" HIC
                      "�������֡�\n" NOR,
        ]) );
        set("coor/x", -3220);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "luo");
        add_action("do_move", "tui");
}

int do_move(string arg)
{
        object me=this_player();

        if( !arg || arg != "shi" ) {
                return notify_fail("��Ҫ�ƶ�ʲô��\n");
        }

        if( (int)me->query_str() > 33 ) {
                message_vision(HIC "$N" HIC "վ��ʯǰ��˫�Ʒ����ƶ���ʯ��ֻ���þ�ʯ"
                       "֨֨��������\n�������ȥ���ֳ�һ���Ż�����\n" NOR,
                       this_player());
                set("exits/south", __DIR__"mudao01");
                remove_call_out("close");
                call_out("close", 5, this_object());
        } else
                message_vision("$N���������ƾ�ʯ����ʯ��˿������ֻ�ð��ˡ�\n", this_player());
        return 1;
}

void close(object room)
{
        message("vision", HIW "\nֻ����ʯ��֨֨�ػص�ԭ�ء�\n" NOR, room);
        delete("exits/south", room);
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "south"
           || ! objectp(guard = present("sun popo", this_object()))
            || !query("family", me) )
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}