inherit ROOM;

void create()
{
        set("short", "��ͬ��");
        set("long", @LONG
�����߾������������ϰ��յľ�ס����ֻ����ͬ����������ЩС���棬
�����С�С�ӻ��̵ȡ�һЩ������������������
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad5",
                  "north" : __DIR__"hutong2",
        ]));

	set("coor/x", -6940);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}