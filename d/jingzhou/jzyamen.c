#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
һ�����ã����Ĵ��ţ����϶�����ڴ��ͭ����������յ�������
һյд�š����ݸ����á�����һյд�š��踮���������Ǿ������Ŵ���
���ڣ����ŵ�������ľ���Ž����ر��š����ྲ�����رܡ������ӷַ�
��ͷʯʨ�ӵ��Աߡ�ǰ����һ����ģ���Ȼ�ǹ�С����ԩ�õġ�������
������ǰѲ�ߡ�
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"ymzhengting",
                "north" : __DIR__"xidajie1",
        ]));
        set("objects", ([
                __DIR__"obj/lion" : 2,
                __DIR__"npc/yayi" : 4,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "south" &&
           objectp(present("ya yi", environment(me))))
                return notify_fail(CYN "���������ȵ����������䡭��\n" NOR);
        return ::valid_leave(me, dir);
}