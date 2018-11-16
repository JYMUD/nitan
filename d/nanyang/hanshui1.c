// This program is a part of NT MudLIB

inherit RIVER;

void create()
{
        set("short", "��ˮ�ϰ�");
        set("long", @LONG
��ǰ��һ�����η����Ĵ� (river)���������������۾���������
�ɴ���������������һ�����������̯����Ҿͽ������ڰ��ߣ�������
���֧һ��ľ�壬���ϰ����˻�������ĺ������㡣��ȥ��Զ��������
���Ϻӿڣ����ٹ����Ͷ�������ȴ��ɴ��ڶɡ�
LONG );
        set("outdoors", "nanyang");
        set("region", "nanyang_zone");
        set("to",__DIR__"hanshui2");

        set("exits", ([
                "south" : __DIR__"yidao2",
        ]));

        set("objects", ([
                __DIR__"npc/chuanfu1" : 1,
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("no_clean_up", 0);

        set("coor/x", 0);
	set("coor/y", 70);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
