// Room: /d/xiangyang/southgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "��ȸ����");
        set("long", @LONG
�����������ǵ��ϳ��ţ�ֻ�������Ϸ����š���ȸ�š��������֡�
���Ÿ����ɣ���Լ�������࣬�����ĳ�����������ȭͷ���С����
�����Ŷ���Լ���ɣ���Լÿ������ʱ���ͻ��ٱ����ء��������ɹ���
���ַ������ǣ�����������൱���ܣ�����һЩ�ٱ��������̲�Ҫ��
�����ǵ��ˡ�
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"   : __DIR__"caodi4",
                "west"   : __DIR__"caodi5",
                "south"  : __DIR__"caodi6",
                "north"  : __DIR__"southgate1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7820);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}