#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short","���");
        set("long", @LONG
����˳���ջ�����ǣ����깩Ӧ���ʲ��ϡ�������紾�ӣ���
���ǻ����ǣ����Ǻ����տ���������ι�����㣬��ϴˢ�ø�Ǭ������
һֱ�ź򵽿�����·����������µ���ľ���϶���һ����ľ�� (paiz
i)������жѷ������Ѳ��ϣ�������һ����ۡ�
LONG );
        set("outdoors", "lanzhou");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "north"  : __DIR__"kedian",
        ]));
	set("coor/x", -15740);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}