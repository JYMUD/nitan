// /d/lanzhou/kedian.c

inherit ROOM;

void create()
{
        set("short", "˳���ջ");
        set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ǳ���¡���������ֶ������˿��ˡ�
��С����������æ������ת���Ӵ�����ǻ�����Ŀ��ˡ�ǽ�Ϲ���һ����
��(paizi)��
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
//        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "¥���ŷ���ÿҹ��ʮ��������\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"market",
                "south" : __DIR__"majiu",
                "up"    : __DIR__"kedian2",
        ]));

	set("coor/x", -15740);
	set("coor/y", 3800);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian11_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

        if( query_temp("rent_paid", me) && dir == "north" )
        return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�
���˻���ΪС���ź����أ�\n");

        return ::valid_leave(me, dir);
}