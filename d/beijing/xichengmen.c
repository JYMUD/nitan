#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǿ��ǵ������ţ���ʵ��̵Ĺų�ǽ�߸������š���������
�����վ�ż�����������ϸ�ļ��������ÿ�춼������˾�������
���뾩�ǡ����������ţ�һ����ֱ�Ĵ�ٵ������������졣���ߵ�
�ٵ����������������������������ͨ�����ǵ���������֡�
LONG );
        set("exits", ([
                "east" : "/d/beijing/ximenkou",
                "west" : "/d/beijing/ximenwai",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2850);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}