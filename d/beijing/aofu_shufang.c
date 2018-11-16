#include <ansi.h>
#include <room.h>
inherit ROOM;

string look_hua();
int valid_leave();

void create()
{
        set("short", "�����鷿");
        set("long", @LONG
�����������鷿��ȴû��һ���顣���ֹ���������Ŀ����
����ͭ�����ߵ��������ʣ����鱦ʯ��Ӧ�о��У�ֻҪӵ����
��һ�����͹����һ�����ˡ�����ǽ����һ����(hua)��
LONG);

        set("exits", ([
                "east" : __DIR__"aofu_zoulang3",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("item_desc", ([
                "hua" : (: look_hua :),
        ]));
        set("coor/x", -2840);
        set("coor/y", 7790);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_xian", "xian");
        add_action("do_turn", "turn");
}

string look_hua()
{
        object me = this_player();

        if (query("score", me) < 3000)
                return WHT "\n����һ���¾ɵĻ���û��"
                       "ʲô��ͬ��\n" NOR;

        set_temp("marks/��1", 1, me);
        return WHT "\n����һ���¾ɵĻ�������һ��΢΢"
               "¡�����̲�ס�����ƿ�������\n" NOR;
}

int do_xian(string arg)
{
        object me = this_player();

        if (! arg || arg != "hua")
                return 0;

        if( !query_temp("marks/��1", me) )
                return 0;

        write(HIC "\n���ƿ��������ֺ��澹������һ����"
              "�֣��ƺ�����ת����\n" NOR);
        set_temp("marks/��2", 1, me);
        return 1;
}

int do_turn(string arg)
{
        object ob, me = this_player();

        if (! arg || arg != "bashou")
                return 0;

        if( !query_temp("marks/��2", me) )
                return 0;

        if (query("exits/down"))
                return notify_fail("�����������֣����ƺ�ûʲô���á�\n");

        message_vision(HIY "\n$N" HIY "���������֣������Ȼ����"
                       "�������ֳ�һ�����ڡ�\n\n" NOR, me);
        set("exits/down", __DIR__"aofu_mishi");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "�����Ȼ��������������ԭ�أ����ܵ�����ڵ�"
                          "ס�ˡ�\n" NOR, room);
        delete("exits/down", room);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/��1", me);
        delete_temp("marks/��2", me);
        return ::valid_leave(me, dir);
}
