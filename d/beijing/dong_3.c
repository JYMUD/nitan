#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�ض����");
        set("long", @LONG
�����Ǳ����ǵذ��ŵĶ��֡��ֵ�����������������֣�������
�����ﲻ����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ���
�����������ŵ��ӵ������Լ�������ˣ�ŵ���ͯ������һ����æ����
��ʢ�����󡣱����������ϱ��ǿ�������������֡�
LONG );
       set("exits", ([
                "north" : "/d/beijing/wenmiao",
                "south" : "/d/beijing/wang_9",
                "west" : "/d/beijing/dong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}