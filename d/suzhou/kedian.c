// Room: /d/suzhou/kedian.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
        set("short", "�͵�");
        set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ǳ���¡������οͶ�ѡ��������
�ţ��������������������صķ������顣��С����������æ������ת��
�Ӵ�����ǻ�����Ŀ��ˡ�
    ǽ�Ϲ���һ������(paizi)��
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "¥���ŷ���ÿҹ��ʮ��������\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer3" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"beidajie1",
                "up"   : __DIR__"kedian2",
        ]));

	set("coor/x", 1120);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian4_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס����\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�
���˻���ΪС���ź����أ�\n");

        return ::valid_leave(me, dir);
}