// Room: /d/xiangyang/northgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "��������");
        set("long", @LONG
�����������ǵı����ţ�ֻ�������Ϸ����š������š��������֡�
���Ÿ����ɣ���Լ�������࣬�����ĳ�����������ȭͷ���С����
�����Ŷ���Լ���ɣ���Լÿ������ʱ���ͻ��ٱ����ء��������ɹ���
���ַ������ǣ�����������൱���ܣ�����һЩ�ٱ��������̲�Ҫ��
�����ǵ��ˡ�
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "south"  : __DIR__"northgate1",
                "north"  : __DIR__"caodi3",
                "east"   : __DIR__"caodi1",
                "west"   : __DIR__"caodi2",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}