#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���������");
        set("long", @LONG
����վ�ھ��ݱ�������ſڣ����Կ������������Ʒ��Ĺٱ�����
�˵�Ѳ�ߣ���ʱ�ش����ź������ϰ����ǲ������ڴ˹ۿ��ģ������
�Ͽ��߿���
LONG );
        set("exits", ([
                "east" : __DIR__"nandajie2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}