// Room: /d/shaolin/bamboo12.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һƬ���ܵ����֡������˼�������Ω�����ߵ��·�棬��ɮ
��ľ������΢�紵����Ҷ�������������������˳���Ϊ֮һ�ӣ�����
���ѵ��������ڡ�
LONG );
        set("exits", ([
                "south" : __DIR__"bamboo"+(random(13)+1),
                "north" : __DIR__"bamboo13",
                "east" : __DIR__"bamboo"+(random(13)+1),
                "west" : __DIR__"bamboo"+(random(13)+1),
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "north")addn_temp("bamboo/count", 1, me);
        else addn_temp("bamboo/count", -1, me);

        return ::valid_leave(me, dir);
}
