//Room: /d/dali/kedian2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short", "�͵��¥");
        set("long", @LONG
����һ��ܴ�Ŀͷ�������ʮ�ּ�ª����ǽ����ʮ����Сľ����
���ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ��������������Ŵ��ǿյģ�
��������ŵ����˹�ȥ��
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("hotel",1);
        set("no_clean_up", 0);
        set("exits", ([
                "down" : __DIR__"kedian",
        ]));
        set("coor/x", -15200);
	set("coor/y", -1860);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}