// Room: /d/xiangyang/xuetang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "ѧ��");
        set("long", @LONG
������������ѧ�ã�����������һ����Ⱦ��һλׯ�����������
������̫ʦ���Ͻ�ѧ��������������������ѧ��ѧ����һ�Ź��ⰻȻ
���鰸������������ǰ�棬���ϰ��ż��������˵���װ�鼮��
LONG );
        set("exits", ([
                "west" : __DIR__"southjie1",
        ]));
        set("objects", ([
                __DIR__"npc/laoxiansheng" : 1,
        ]));
        set("coor/x", -7810);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}