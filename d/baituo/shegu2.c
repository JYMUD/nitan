// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹�ɽ��");
        set("long", @LONG
���ǰ���ɽ�߹��е�ɽ·����һ������ȳ�����С�������ŵ���
����������������С�
LONG );

        set("exits", ([ 
                "southup"   : __DIR__"shegu1",
                "northwest" : __DIR__"shegu3",
        ]));

        set("outdoors", "baituo");
        set("shegu", 1);
        set("coor/x", -49970);
        set("coor/y", 20120);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}

int valid_leave(object me, string dir)
{
        object room;
        int i, w;

        room = load_object(__DIR__"shegu1");

        if (dir == "southup") {
                if( !query("baituo/shegu_permit", me) && query("defense", room) )
                        return notify_fail("�����߳��߹ȣ����ǹȿں�����������һ�߽�������ȳ��˱ǣ��о�����Щ��ѣ��\n"
                                "�������Ǽ�Ϊ�����Ķ�������ǿ��ͨ����\n");
        }
        return ::valid_leave(me,dir);
}