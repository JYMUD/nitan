// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "��԰");
        set ("long", @LONG
������ҵĺ�԰��������ɸ�ӡ���ͷ��ʯ�ʡ�����֮�������һ
��С������һ����¯����¯�в�����֦��ȼ�˵����㡣��ǰ�и��˹���
�����ͷ����֪����ʲôԸ�ġ�
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_ketang",
                "east"  : __DIR__"wan_citang",
        ]));
        set("objects", ([
                __DIR__"npc/kongxincai"    : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}