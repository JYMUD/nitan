// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "��¥");
        set ("long", @LONG
�������ŵ���ס�ĵط�������һ���а˸����ӣ����������������
�⣬����Ķ�ס�����ǽ�Ϲ��˼��ѵ�����
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "west"   : __DIR__"wan_dating",
                "north"  : __DIR__"wan_chaifang",
        ]));
        set("objects", ([
                __DIR__"npc/shencheng" : 1,
                __DIR__"npc/sunjun"    : 1,
                __DIR__"npc/boyuan"    : 1,
                __DIR__"npc/fengtan"   : 1,
        ]));

        set("coor/x", -7100);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}