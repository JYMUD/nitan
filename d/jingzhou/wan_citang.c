// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
����һ���ưܵ����á��������ǻҳ������ζ������ǲ��ơ�
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "west" : __DIR__"wan_huayuan",
        ]));
        set("objects", ([
                __DIR__"npc/taohong" : 1,
        ]));

        set("coor/x", -7100);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}