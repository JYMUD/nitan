// Room: /d/quanzhou/hongfulou.c
// Last Modified by winder on May. 29 2001
#include <room.h> 

inherit CREATE_CHAT_ROOM; 

void create()
{
        set("short", "�踣¥");
        set("long", @LONG
����Ȫ�ݳ����ֺ����ϵĿ�ջ���¥������ǳ���¡����཭����
���������̸���ۣ����������Ǹ��������鱨�ĺõط���ǽ�Ϲ���һ��
����(paizi)��������һ����ǡ�
LONG );
        set("item_desc", ([
                "paizi" : "¥���ŷ���ÿҹ��ʮ��������\n",
        ]));
        set("exits", ([
                "west"   : __DIR__"northroad1",
                "north"  : __DIR__"majiu",
                "up"     : __DIR__"kedian2",
        ]));
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian16_b"->foo();
        //"/adm/npc/youxun"->come_here();
}

void init() 
{
        add_all_action(); 
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

        if( query_temp("rent_paid", me) && dir == "west" )
                return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�\n���˻���ΪС���ź����أ�\n");

        return ::valid_leave(me, dir);
}