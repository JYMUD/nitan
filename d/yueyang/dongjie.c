// Room: /d/yueyang/dongjie.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ���ֳ��ֿ����ʯ�������ɨ��ʮ�ָɾ��������£�ż��С
��������������͸��������Ŷ������ߡ�ԭ�������߾��Ǹ��ã�����
��Ȼ���֣�������ȴʮ�ְ������ϱ���һ����ݡ����������Ŀ��̳�ȥ
Ъ�ţ�������Ҳʱ��ǰȥ���������ġ�
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"zhongxin",
                "south" : __DIR__"chaguan",
                "north" : __DIR__"yamen",
        ]));
        set("objects", ([
                __DIR__"npc/liumang" : 1,
        ]));
	set("coor/x", -6190);
	set("coor/y", -3010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}