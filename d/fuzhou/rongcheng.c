// Room: /d/fuzhou/rongcheng.c
// Date: May 12.1998 by Java
inherit ROOM;

void create()
{
        set("short", "�ų���");
        set("long", @LONG
�ų�����ȫʡ���Ŀ͵꣬����ǳ���¡������οͶ�ѡ��������
�ţ�������������������ʡ�ķ������顣��С������������æ������
��ת�����ݵķ�������ʵ������˳����������¥˯��ȥ��
    ǽ�Ϲ���һ������(paizi)��
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : "¥���ŷ���ÿҹ��ʮ��������\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
            "south" : __DIR__"dongdajie",
            "north" : __DIR__"majiu",
            "up"    : __DIR__"rongcheng2",
        ]));
	set("coor/x", -70);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian5_b"->foo();
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