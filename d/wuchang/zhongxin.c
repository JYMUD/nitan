inherit ROOM;

void create ()
{
        set("short","���Ĺ㳡");
        set("long", @LONG
�������人����ĵش��ˡ�����㼯������ĺ������ˡ��ο͡�
�����������ò����֡���Ȼ�������Ҳ�ס������������Ȼ���ַǷ���
LONG);

        set("exits", ([
                "west": __DIR__"hzjie4",
                "east": __DIR__"dongmen",
                "south" : __DIR__"hzjie3",
                "north" : __DIR__"hzjie2",
        ]));
        set("objects",([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}