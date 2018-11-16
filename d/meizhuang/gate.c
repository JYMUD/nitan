#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "÷ׯ����");
        set("long", @LONG
�߹�һ��Ƭ÷�֣�����һ����ʯ���·������һ�����Ű�ǽ�Ĵ�
ׯԺ�⣬�е���������������д�š�÷ׯ���������֣��Ա����š���
�����⡻���֡����������������ƽ�Ĵ󹦳����⼸��������֮��͸
�Ų���Ӣ����
LONG );
        set("outdoors", "meizhuang");
        set("exits", ([
                "south"    : __DIR__"xiaolu",
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_knock", "knock");
}

int do_knock(string arg)
{
        object room, me = this_player();

        if (query("exits/north"))
                return notify_fail("���Ѿ��ǿ��ŵģ������ٷ���ȥ���ˣ�\n");

        if (arg == "4")
        {
                message_vision(HIC "$N" HIC "����ǰȥ������ͭ���������¡�\n" NOR, me);
                set_temp("step", 1, me);
                return 1;
        }

        if (arg == "2")
        {
                message_vision(HIC "$N" HIC "����ǰȥ������ͭ���������¡�\n" NOR, me);
                if( query_temp("step", me) == 1 )
                        set_temp("step", 2, me);
                else
                        set_temp("step", 0, me);
                return 1;
        }

        if (arg == "5")
        {
                message_vision(HIC "$N" HIC "����ǰȥ������ͭ���������¡�\n" NOR, me);
                if( query_temp("step", me) == 2 )
                        set_temp("step", 3, me);
                else
                        set_temp("step", 0, me);
                return 1;
        }

        if (arg == "3")
        {
                message_vision(HIC "$N" HIC "����ǰȥ������ͭ���������¡�\n" NOR, me);
                if( query_temp("step", me) == 3 )
                {
                        set_temp("step", 0, me);
                        set("exits/north", __DIR__"tianjing");
                        message("vision", HIY "�㾲���ĵȺ򣬹��˰��Σ��������ڻ���"
                                          "�Ĵ��ˡ�\n" NOR, this_object() );

                        if (! (room = find_object(__DIR__"tianjing")))
                                room = load_object(__DIR__"tianjing");

                        set("exits/south", __FILE__, room);
                        message("vision", HIY "÷ׯ�����ϵ�ͭ���н��������"
                                "���������Ÿ����ˡ�\n" NOR, room );
                        remove_call_out("close_passage");
                        call_out("close_passage", 10);
                } else
                {
                        set_temp("step", 0, me);
                }
                return 1;
        }
        message_vision(HIC "$N" HIC "����ǰȥ������ͭ�����˼��¡�\n" NOR, me);
        return 1;
}

void close_passage()
{
        object room;

        if (! query("exits/north"))
                return;

        message("vision", HIY "ֻ�����¸¸¡�������÷ׯ�ڵĻ�Ժ������"
                "��������ˡ�\n" NOR, this_object());

        if (room = find_object(__DIR__"tianjing"))
        {
                delete("exits/south", room);
                message("vision", "���ű���Ժ��������ˡ�\n", room );
        }
        delete("exits/north");
}
