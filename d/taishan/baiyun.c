// Room: /d/taishan/baiyun.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "���ƶ�");
        set("long", @LONG
���ƶ����������ѣ���ش����£����о�����Σ�Ҷ��ϡ���������
���������������⡰���ơ��������ơ���������Ⱦ������������¡�
LONG );
        set("exits", ([
                "eastup" : __DIR__"xiangshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 290);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}