//Edited by fandog, 02/15/2000
inherit ROOM;

void create()
{
        set("short", "�紨��ջ");
        set("long", @LONG
����һ�Ҽ�Ǯ�����Ŀ�ջ������ǳ���¡������οͶ�ѡ��������
�ţ��������������������صķ������顣��С����������æ������ת��
�Ӵ�����ǻ�����Ŀ��ˡ�ǽ�Ϲ���һ������(paizi)��
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
//        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "¥���ŷ���ÿҹ��ʮ��������\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"majiu",
                "north" : __DIR__"hzjie4",
                "up"   : __DIR__"kedian2",
        ]));

	set("coor/x", -5100);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
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