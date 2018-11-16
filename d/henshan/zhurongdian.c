#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ף�ڵ�");
        set("long", @LONG
ף�ڵ������ʥ�������ף�ڡ�����ʯ��ǽ�����߸�������
����հ�ѩ��ΡȻ�����ں�ɽ���������ŵ�ʯ��Ͽ����С�[1��37m�����ճ���
��������[2��37��0m����������ԶԶ��ȥ�ַ��ۻ�����������ϻ����С�[1��31mʥ����
��[2��37��0m����鹶
LONG );
        set("exits", ([
                "southdown"  : __DIR__"wangritai",
                "northdown"  : __DIR__"wangyuetai",
                "westup"     : __DIR__"shanlu003",
                "east"       : __DIR__"changlang",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mi" : 1,
                CLASS_D("henshan") + "/first" : 1,
                __DIR__"npc/dizi1"   : 4,
                __DIR__"npc/xiangke" : 2,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", -5490);
	set("coor/z", 40);
	setup();

        "/clone/board/henshan_b"->foo();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir == "northdown" || dir == "southdown"
           || ! objectp(guard = present("mi weiyi", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}
