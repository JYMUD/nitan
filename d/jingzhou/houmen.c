inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǹص���ĺ��ţ�������ȥ����Զ����һ��Сɽ�¡�
LONG );
        set("exits", ([
                "south" : __DIR__"houdian",
                "northup" :__DIR__"xiaoshan",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}