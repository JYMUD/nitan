#include <room.h>
inherit ROOM;

void create()
{
        set("short", "���ֲ���");
        set("long", @LONG
�����Ǿ���������������ߵ�һ�����У���ʯ�������ŵ��档��
�����߰������߲�̯��ˮ��̯�� С���Ŵ���ߺ���ţ����ǵİ��ն���
�������ÿ�������ʳ�ﹺ�أ� ����һ�ٶٿɿڵļ��ȡ�
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/caifan" : 1,
                "/d/beijing/npc/jumin1" : 2,
              "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}