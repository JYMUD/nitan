inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����ǹص���ĺ����жѷ����㡢������ǽ�ϵ�ᣲ���
�������µġ�
LONG );
        set("exits", ([
                "north" : __DIR__"houmen",
                "south" : __DIR__"guanmiao",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}