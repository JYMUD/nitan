// xiuxis.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
����һ���������е�С�ݣ������м���ż��Ŵ󴲣��������ӣ���
���Ǹ���Ϣ�ĵط������й�����ͣ�ʹ�˸���˯�⡣
LONG );
        set("exits", ([ 
                "east" : __DIR__"xiaodao2", 
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("sleep_room",1);
        set("no_clean_up", 0);
        set("coor/x", 50);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}