// Room: /d/yueyang/jiudian.c 
// Last Modifyed by Winder on Dec. 4 2001
inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
����������ͥ�Ĺ������˲�֪���������¥������Ľ�����񼣶�
��������������ˣ�Ҳ���һ�����������Ĵ��¥�ˡ�������������
�ˣ����˵û���ڶ���¥�ȹ����߾ƣ�������ͥ�㣬Ҳ���Ǻ����ˡ�
LONG );
        set("exits", ([
                "east"  : __DIR__"nanjie",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -6210);
	set("coor/y", -3020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}