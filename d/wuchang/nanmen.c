inherit ROOM;

void create ()
{
        set ("short","����");
        set ("long", @LONG
�����ǾŽ������š���������˺ܶࡣ����ս����������Ž�����
�ܷ�������ʱ��������������������������ٱ�ҫ��������վ�����
��������������ˡ�
LONG);

        set("exits", ([
                "north":__DIR__"hzjie5",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}