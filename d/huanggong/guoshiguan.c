// Room: /d/huanggong/guoshiguan.c

inherit ROOM;

void create()
{
        set("short", "��ʷ��");
        set("long", @LONG
��ʷ���Ǻ����峼�Ƿ�����޹�ʷ����ĳ������. ����Ĳ�����
��. ��Ҫ�Ƿ�־��ʷ��.
LONG
        );
        set("exits", ([
                "northwest"  : __DIR__"wenhua",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2780);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}