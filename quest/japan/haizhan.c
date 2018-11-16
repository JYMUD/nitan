// /job/japan/haizhan.c
// by akuma 10:52 AM 11/30/2003
// source from hanghai_room.c

#include <ansi.h>
inherit ROOM;
#define MST        __DIR__"haizhan_master"                // ��γ�ǣ���Ϸָ����֧��

void create()
{
        set("short", "����");
        set("long", @LONG
ãã��֮�У����ҽ��Ӹ���ƺƵ��������ձ����ӡ�
LONG);
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("cost", 0);
        setup();
}

void init()
{
        add_action("do_game", "haizhan");
        add_action("do_quit", "quit");
}

int do_game(string arg)
{
        object me = this_player(), mst_obj;

        if ( !arg || arg != "��ʼ" ) return 0;        // "game over" �Ȳ������� MST ������С�

        if( !query_temp("job/fleet", me))return notify_fail("������ʹ��ƺ���ս����\n");

        if ( file_size( MST + ".c" ) < 1 ) return notify_fail("��ս��ͣ���Ϸ�ү��Ъ�ˡ�\n");

        write("\n����⽢��������ʻ��ƺ�ս������\n\n");
        mst_obj = new( MST );
        mst_obj->new_game(me);
        mst_obj->move(me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("job/haizhan", me))return notify_fail("ս���Ѿ���ʼ�������������ӡ�\n");

        return ::valid_leave(me, dir);
}

int do_quit()
{
        write("���ﲻ���˳���Ϸ��\n");
        return 1;
}