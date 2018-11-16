// This program is a part of NT MudLIB

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
�����ǽ���֪�������Ŵ��á������ǡ��ྲ�������رܡ������ӣ�
ʮ����������ˢˢ��վ�ţ�����ˮ��������ӵ����ġ�֪���������ڰ�
̨������ر������㡣�����Ϸ���һ���ң���д�������������ĸ���
�֡�һ��ʦү������վ��֪��������󣬲�ʱ����Դ��˶��Ｘ�䡣
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"jzyamen",
                "south" : __DIR__"houyuan",
                "east"  : __DIR__"laofang",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
                __DIR__"npc/shiye" : 1,
                __DIR__"npc/ling"  : 1,
        ]));

        create_door("east", "����", "west", DOOR_CLOSED);
        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (! wizardp(me) && objectp(present("ling tuisi", environment(me))) &&
                dir == "east")
                return notify_fail("�躲�ֵ�ס���㣺�������η���\n");
        return ::valid_leave(me, dir);
}