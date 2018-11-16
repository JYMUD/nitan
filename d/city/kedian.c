#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

void create()
{
	set("short", "�͵�");
        set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ȴ�Ƿǳ���¡������οͶ�ѡ��
��������ţ��������������������صķ������顣��С����������
æ������ת���Ӵ�����ǻ�����Ŀ��ˡ��͵�����˴Ӳ�¶�棬������
��˭���и��ָ����Ĳ²⡣�͵����ǽ�Ϲ���һ������(paizi)��
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : WHT "\n\n        ����������������������������������\n"
                              "        ��                              ��\n"
                              "        ��    " NOR + HIW "¥���ŷ���ÿҹʮ��������" NOR + WHT "  ��\n"
                              "        ��                              ��\n"
                              "        ����������������������������������\n\n\n" NOR,
	]));
	set("objects", ([
                __DIR__"npc/fuxinglaoren" : 1,
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/qi"     : 1,
                "/u/shulele/shashou/npc/yangxu-yan.c" : 1,
	]));
	set("exits", ([
                "east" : __DIR__"majiu",
          "service":"/d/city/advice/advice",
		"west" : __DIR__"beidajie1",
		"up"   : __DIR__"kedian2",
		"south": __DIR__"kedian4",
                "north": __DIR__"stock",
	]));


	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	"/clone/board/kedian_b"->foo();
        "/adm/npc/youxun"->come_here();
}

void init()
{
        add_all_action();
}

int valid_leave(object me, string dir)
{

	if( !query_temp("rent_paid", me) && dir == "up" )
	        return notify_fail(CYN "��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n" NOR);

	if( query_temp("rent_paid", me) && dir == "west" )
	        return notify_fail(CYN "��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�\n" NOR);

	return ::valid_leave(me, dir);
}
